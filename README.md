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
  * [Client Implementation](#client-implementation)
* [Usage 🏁](#usage-)
* [Testing 🧪](#testing-)

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

> Both functions listen for a user defined signal and change de default signal action associated to it, their main difference being that `sigaction()` employs a specialized struct to store extra information, giving the user finer control over signal actions.

The `server`'s **main()** function declares and initializes a `struct sigaction` variable called `sa`.
* It uses `sigemptyset()` to initialize the signal set `sa.sa_mask` with all signals excluded from the set;
* `sa.sa_sigaction` is set to the function `ft_server_sighandler()`;
* `sa.sa_flags` has the bits for `SA_SIGINFO` and `SA_RESTART` turned on;

The `sa` struct is then passed into `ft_set_sigaction()` to set event handling for `SIGUSR1` and `SIGUSR2` signals.
```c
struct sigaction	sa;

sigemptyset(&sa.sa_mask);
sa.sa_sigaction = ft_server_sighandler;
sa.sa_flags = SA_SIGINFO | SA_RESTART;
ft_set_sigaction(&sa);
```

> [!Note]
>
> * `SA_SIGINFO` : gives the user access to extended signal information; This flag makes `sigaction()` switch where it looks for the custom signal handler, changing it from the `sa.sa_handler` member to `sa.sa_sigaction`.
>
> * `SA_RESTART` : provides BSD compatible behaviour allowing certain system calls to be restartable across signals.


Prints the `server`'s' `pid` to `stdout` and enters an infinite loop, listening for a signal to catch.
```c
ft_print_pid();
while (1)
	pause();
```
___
#### `ft_server_sighandler()`
```c
static void	ft_server_sighandler(int sig, siginfo_t *info, void *context);
```

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
```c
static void	ft_strlen_received(t_protocol *server);
```

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
```c
static void	ft_print_msg(t_protocol *server, int *i, pid_t pid);
```

Once 8 bits have been received and the header information has already been transferred, the first layer of logic is triggered:
```c
if ((server->bits == 8) && server->received) { ... }
```
The received byte stored in `server.data` is copied to the `i`-th index of `server->msg`.

Then `i` is incremented to point to the next byte in memory where the next `char` or `Unicode` segment is gonna be stored.
```c
server->msg[*i] = server->data;
++(*i);
```

Notice that `server.bits` is reset to 0 after the `char` has been stored, in preparation to receive the next.
```c
server->bits = 0;
```

> [!Note]
>
> On Unicode ...

And so the `server` receives each byte of the message until the whole message has been received. The server knows that the received message has reached its end when the current `server.data` value is the NULL terminator.
```c
if (server->data == '\0') { ... }
```

The server then prints the message to `stdout` taking advantage of ANSI escape codes to color the ouptut.
```c
ft_printf("Message:\n%s%s%s\n", GRN, server->msg, NC);
```

> [!Note]
>
> In case you are curious and want to learn more about ANSI escape codes
check out
[ansi.h](https://github.com/PedroZappa/libft/blob/master/color_codes/ansi.h)
included in my [libft](https://github.com/PedroZappa/libft) repository!

And so the `server` receives each byte of the message. It knows the message has reached its end when the current `server.data` value is the NULL terminator.
```c
if (server->data == '\0') { ... }
```

The server then prints the message to `stdout` followed by the `server`'s
`pid`. Since we are done with the `server.msg`, we free the memory
space allocated to store it.
```c
ft_printf("Message:\n%s%s%s\n", GRN, server->msg, NC)
ft_print_pid();
free(server->msg);
```

Now all there is left to do is to prepare the server to receive the next
message.
```c
server->msg = NULL;
server->received = 0;
*i = 0;
```

Finally we send a bit back to the `client` to signify that the message
has been received.
```c
ft_send_bit(pid, 1, 0);
```

___
### Client Implementation


Before starting operations the [client](https://github.com/PedroZappa/42_minitalk/blob/main/src/client.c) must check if its input arguments are valid.

It first checks if `argc` is not equal to 3, if so the program will print an error to `stderr` and exit. Then checks if the `pid` of the server (`argv[1]`) is valid by test-calling `kill()` (with a zero instead of a signal identifier), if so the program will also print an error to `stderr` and exit.
```c
if (argc != 3)
	ft_perror_exit("Usage: ./client [PID] [message]\n");
else if (kill(ft_atoi(argv[1]), 0) < 0)
	ft_perror_exit("PID does not exist\n");
```

The `client`, like the `server`, uses `sigaction()` to handle incoming UNIX signals, but sets it up slghtly differently.



___

## Usage 🏁


___
## Testing 🧪


</div>
