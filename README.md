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
    * [`ft_send_msg()`](#ft_send_msg)
  * [`ft_send.c` Helper Functions](#ft_sendc-helper-functions)
    * [`ft_send_char()` & `ft_send_int()`](#ft_send_char--ft_send_int)
    * [`ft_send_bit()`](#ft_send_bit)
  * [`ft_sigaction.c` Helper Functions](#ft_sigactionc-helper-functions)
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

___
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

The `client`, like the `server`, uses `sigaction()` to handle incoming UNIX signals, but sets it up slightly differently.

The `client` declares `sa` and:
* initializes `sa.sa_mask` with all signals excluded from the set using `sigemptyset()`;
* `sa.sa_handler` is set to the function `ft_client_sighandler()`;
* `sa.sa_flags` is set to `SA_RESTART`

Then the `sa` struct is passed into `ft_set_sigaction()` to set event handling for `SIGUSR1` and `SIGUSR2`.
```c
struct sigaction	sa;

sigemptyset(&sa.sa_mask);
sa.sa_handler = ft_client_sighandler;
sa.sa_flags = SA_RESTART;
ft_set_sigaction(&sa);
```

> The `client` event handler simply prints a `*` if the received signal is `SIGUSR1` or if it is `SIGUSR2` announces that the message has been successfully sent and exits the program.

The `client` then prints the `server`'s `pid` to `stdout` to which it is connects to and calls `ft_send_msg()`.
```c
ft_print_pid();
...
ft_send_msg(ft_atoi(argv[1]), argv[2]);
```
___
#### `ft_send_msg()`
```c
static void ft_send_msg(pid_t pid, char *msg);
```

This function creates a local variable `i`, initialized to 0, to keep track of the current index in the message being sent. 

But before it starts sending the actual message it must first send its length to the `server`. This is done bit by bit using the function `ft_send_int`.
```c
int	msglen;
...
msglen = ft_strlen(msg);
ft_send_int(pid, msglen);
```

Then it loops through the message and sends each character to the server bit by bit.
```c
ft_printf("\n%sSending Message%s\n", GRN, NC);
while (msg[i] != '\0')
	ft_send_char(pid, msg[i++]);
ft_printf("\n");
```

Then all there's left to do is to send a NULL terminator to the `server` and terminate the message:
```c
ft_send_char(pid, '\0');
```

___
### `ft_send.c` Helper Functions

To send `char`s and `int`s to the `server` I implemented two helper functions: `ft_send_char()` and `ft_send_int()`. 

___
#### `ft_send_char()` & `ft_send_int()`
```c
void	ft_send_int(pid_t pid, int num);
void	ft_send_char(pid_t pid, char c);
```

These two functions work in a similar way. They first initialize a `bitshift` integer variable with the size of the data type about to be sent:
```c
int		bitshift;

bitshift = ((sizeof(int) * 8) - 1);  // Prepare the server to receive 32 bits
...
bitshift = ((sizeof(char) * 8) - 1); // Prepare the server to receive 8 bits
```
> `bitshift` will be used to iterate through each bit of the data being sent from the most significant (`MSB`) to the least significant bit (`LSB`).

The `client` enters a loop running from `bitshift` to 0: 
* it breaks the `char`/`int` into its individual bits; 
* Each bit is passed as an argument to `ft_send_bit()` where it triggers the appropriate signal and is sent to the server;
* `bitshift` is decremented to move to the next bit;
```c
while (bitshift >= 0)
{
	bit = (num >> bitshift) & 1; // Get the current bit
	ft_send_bit(pid, bit, 1);    // Send the current bit
	--bitshift;                  // Move to the next bit
}
```
___
#### `ft_send_bit()`
```c
void	ft_send_bit(pid_t pid, char bit, char pause_flag)
```

`ft_send_bit()` sends information to the `server` bit by bit. It simply checks if the passed `bit` is 1 or 0 and sends the appropriate signal using `kill()`.

> Calling `kill()` within an expression in an `if` statement is a handy way to handle possible errors with our signal calls. In this case if the call to `kill()` fails the program writes an error message to `stderr` and exits.
```c
if (bit == 0)
{
	if (kill(pid, SIGUSR1) < 0)
		ft_perror_exit("kill() failed sending SIGUSR1\n");
}
else if (bit == 1)
{
	if (kill(pid, SIGUSR2) < 0)
		ft_perror_exit("kill() failed sending SIGUSR2\n");
}
```

If the `pause_flag` is set to 1, the `server` waits for the next data chunk to be sent.

> This function is called with `pause_flag = 1` when used in the context of `ft_send_char()` and `ft_send_int()`, so that for each bit sent the `client` waits for a confirmation signal from the `server` before it proceeds sending the data.
```c
if (pause_flag != 0)
	pause();
```
___
### `ft_sigaction.c` Helper Functions

This file contains the `sigaction` function that is used to set both the `server`'s event handler and the `client`'s event handlers for `SIGUSR1` and `SIGUSR2` signals:

> Once again, error handling is done using control expressions inside `if` statements.
```c
void	ft_set_sigaction(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
		ft_perror_exit("sigaction() failed to handle SIGUSR1");
	if (sigaction(SIGUSR2, sa, NULL) < 0)
		ft_perror_exit("sigaction() failed to handle SIGUSR2");
}
```


___

## Usage 🏁


___
## Testing 🧪


</div>
