<a name="readme-top"></a>
<div align="center">

# minitalk

> A minimalistic implementation of a small data exchange program using UNIX signals. 

<p>
    <img src="https://img.shields.io/badge/score-%20%2F%20100-success?style=for-the-badge" />
    <img src="https://img.shields.io/github/repo-size/PedroZappa/42_minitalk?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/PedroZappa/42_minitalk?style=for-the-badge&logo=" />
    <img src="https://img.shields.io/github/languages/top/PedroZappa/42_minitalk?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/PedroZappa/42_minitalk?style=for-the-badge" />
</p>

___

<h3>Table o'Contents</h3>

</div>

<!-- mtoc-start -->

* [About 📌](#about-)
  * [Mandatory Features](#mandatory-features)
  * [Bonus Features](#bonus-features)
* [Implementation 📜](#implementation-)
  * [Server Implementation](#server-implementation)
    * [`ft_server_sighandler()`](#ft_server_sighandler)
    * [`ft_strlen_received()`](#ft_strlen_received)
    * [`ft_print_msg()`](#ft_print_msg)
  * [Mandatory Client Implementation](#mandatory-client-implementation)
* [Usage 🏁](#usage-)

<!-- mtoc-end -->

___

## About 📌

The goal of this project is to develop a `client`-`server` communication program using UNIX signals only.

### Mandatory Features

The mandatory implementation must behave as follows:

* First the `server` must be started, which will generate a `pid` and print it to `stdout`.
* The `client` should accept two parameters:
	* The `pid` of the `server`;
	* The `message` to be sent;
* The `client` must send the `message` passed in as a parameter to the `server`.
* Upon receiving the `message` the `server` must print it to `stdout` almost instantly.
* The `server` must be able to receive `message`s from several different clients **in a row** without the need for a restart. (Note that Linux systems do NOT queue signals when a signal of the same type is already pending).
* `client`-`server` communication must be done using `SIGUSR1` and `SIGUSR2` signals only.

### Bonus Features

* The `server` acknowledges receiving a message by sending back a signal to the `client`.
* Support Unicode characters.

___

## Implementation 📜

For this project I chose to implement both mandatory and bonus features together. The `server` and `client` can be found in the `server.c` and `client.c` files inside the `src` folder plus two additional files `ft_sigaction.c` and `ft_send.c` containing helper functions.

### Server Implementation

To implement the [server](https://github.com/PedroZappa/42_minitalk/blob/main/src/server.c)'s signal handling functionality I used `sigaction()` over `signal()`. This is because `signal()` is deprecated due to its varying behaviour across UNIX versions, making it a non-portable option.

Both functions listen for a user defined signal and change de default signal action associated to it, their main difference being that `sigaction()` employs a specialized struct to store information, giving the user finer control over signal actions.

The `server`'s **main()** function declares and initializes a `struct sigaction` variable called `sa`. `sa.sa_sigaction` is set to the function `ft_server_sighandler()`, and `sa.sa_flags` has the bits for `SA_SIGINFO` and `SA_RESTART` turned on.

> [!Note]
>
> `SA_SIGINFO` gives the user access to extended signal information; This flag makes `sigaction()` switch where it looks for the custom signal handler, changing it from the `sa.sa_handler` member to `sa.sa_sigaction`.
>
> `SA_RESTART` provides BSD compatible behaviour allowing certain system calls to be restartable across signals.

```c
struct sigaction	sa;

sa.sa_handler = ft_server_sighandler;
sa.sa_flags = SA_SIGINFO | SA_RESTART;
```

The `sa` struct is then passed into `ft_set_sigaction()` to set event handling for `SIGUSR1` and `SIGUSR2` signals.

Prints the `server`'s' `pid` to `stdout` and enters an infinite loop, listening for a signal to catch.
```c
while (1)
	pause();
```
___
#### `ft_server_sighandler()`

Any time either, a `SIGUSR1` or a `SIGUSR2` signal is received, the `ft_server_sighandler()` function is called. All its local variables are static, therefore automatically initialized to 0.

For the sake of simplicity one of these variables is a custom data type `t_protocol` which holds all the data the server needs to perform its operations.
```c
typedef struct s_protocol
{
	int  bits;     // Number of bits received
	int  data;     // Received data (One integer and a sequence of chars)
	int  received; // Flag indicating if "header" data has been received
	char *msg;     // Received message
}	t_protocol;
```

The server signal handler waits for 100 microseconds before it starts receiving data. It first receives an integer as "header information" specifying the length in bytes of the data about to be transferred, then come the actual bits of the message.

To store the data according to the data type being received the following bitwise operations and conditionals are employed:
```c
if ((sig == SIGUSR2) && !server.received)
	server.data |= 1 << (((sizeof(int) * 8) - 1) - server.bits);
else if ((sig == SIGUSR2) && server.received)
	server.data |= 1 << (((sizeof(char) * 8) - 1) - server.bits);
```

The bitwise operators `|` (OR) and `<<` (Left-Shift) are used together to set the received bits in the proper place in memory. The conditional statements make sure that the first 32 bits of the message are saved in a space that fits an `int`, specifying the length of the incoming message. After this `int` is received the `server` starts storing the following inbound bits into `char` sized chunks of memory.

This operation only happens when a `SIGUSR2` is received. Any time a `SIGUSR1` is caught, the server simply acknowledges it by printing a `*` and keeps listening for further signals.

> [!Note]
>
> On the server side, `SIGUSR1` and `SIGUSR2` are therefore used to signify 0 and 1 respectively.

___
#### `ft_strlen_received()`

Once the `int` has been received the conditions for the triggering of the code block inside `ft_strlen_received()` are met:
```c
if ((server->bits == (sizeof(int) * 8)) && !server->received) { ... }
```

This function first sets the `server.received` flag to 1, signifying that the header data has been received. It then continues receiving the message bit by bit until every `char` in the message has been transferred successfully.

The server prints the length of the message to `stdout`, then takes this value plus 1 (to account for the NULL terminator) and allocates memory for a message with that many bytes.
```c
server->msg = ft_calloc((server->data + 1), sizeof(char));
if (!server->msg)
	ft_perror_exit("ft_calloc() failed\n");
```

The memory space for the message is then NULL terminated, and the `server->bits` are reset to 0 to prepare the server to receive the bits of the message.
```c
server->msg[server->data] = '\0';
server->bits = 0;
```

___
#### `ft_print_msg()`

Once 8 bits have been received the first layer of logic is triggered. 
```c
if ((server->bits == 8) && server->received) { ... }
```
The received byte stored in `server.data` is copied to the `i`-th index of `server->msg`. The `i` variable is incremented to point to the next byte in memory where the next byte is gonna be stored.
```c
server->msg[*i] = server->data;
++(*i);
```  


and the `server->bits` are reset to 0 to prepare the server to receive the next byte.



___

### Mandatory Client Implementation


___

## Usage 🏁

</div>
