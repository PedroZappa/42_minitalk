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
  * [Mandatory Implementation](#mandatory-implementation)
  * [Server Implementation](#server-implementation)
  * [Mandatory Client Implementation](#mandatory-client-implementation)
* [Usage 🏁](#usage-)

<!-- mtoc-end -->

<div align="left">

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

### Mandatory Implementation

For the mandatory implementation, `server` and `client` are implemented in `server.c` and `client.c` files inside the `src` folder.

### Server Implementation

The server is a very simple program. It prints it's `pid` to `stdout` and waits for a `SIGUSR1` or `SIGUSR2` signal.

To implement the [server](https://github.com/PedroZappa/42_minitalk/blob/main/src/server.c)'s signal handling functionality I chose to use `sigaction()` over `signal()`. This is because `signal()` is deprecated due to its varying behaviour across UNIX versions, making it a non-portable option. Both functions listen for a user defined signal and change de default signal action associated to it. The main difference between them is that `sigaction()` employs a specialized struct to store more information, giving the user finer control over signals.

The `server`'s **main()** function declares and initializes a `struct sigaction` variable called `sa`. `sa_handler` is set to the function `ft_server_sighandler()`, and `sa_flags` is set to the bits for `SA_SIGINFO` and `SA_RESTART` turned on.

> [!Note]
> `SA_SIGINFO` gives the user access to extended signal information;
> `SA_RESTART` provides BSD compatible behaviour allowing certain system calls to be restartable across signals.
```c
struct sigaction	sa;

sa.sa_handler = ft_btoc;
sa.sa_flags = 0;
```

The function then it prints the `pid` of the `server` to `stdout` with colored output.
The `sigaction()` function is called for `SIGUSR1` and `SIGUSR2` signals, setting up a custom signal catching function, `ft_btoc`.

Then the process enters an infinite loop, waiting for a signal. We put the process to sleep until a signal is received invoking a signal-catching function that handles it.
```c
sigaction(SIGUSR1, &sa, NULL);
sigaction(SIGUSR2, &sa, NULL);
while (1)
	pause();
```

Any time either, a `SIGUSR1` or a `SIGUSR2` signal is received, the `ft_btoc` function is called. It prints a message byte by byte to `stdout`, sent bit by bit from a `client`.

If the signal is `SIGUSR1`, the function writes a 0, else if the signal is `SIGUSR2`, writes a 1 into an array `byte` for storing the bits of a byte representing a ASCII/Unicode character. The `byte` is a static variable so that the bits accumulate from one function call to another. Once 8 bits have been received, the `ft_btoc` function prints the `byte` to `stdout` and resets the `bit` counter to 0 to prepare for the next incoming sequence of bits.
```c
static void	ft_btoc(int sig)
{
	static int	bit;
	static int	byte[8];

	if (sig == SIGUSR1)
		byte[bit++] = 0;
	else
		byte[bit++] = 1;
	if (bit == 8)
	{
		ft_print_byte(byte);
		bit = 0;
	}
}
```

The character value is printed by `ft_print_byte()`, called by `ft_btoc` once all the bits have been received. It receives a pointer to an array of ints. With the aid of an iterator and an accumulator we convert the bit representation to a decimal value, then print it to `stdout`.
```c
static void	ft_print_byte(int *byte)
{
	int				i;
	unsigned char	to_print;

	i = 7;
	to_print = 0;
	while (i >= 0)
		to_print = to_print * 2 + byte[i--];
	ft_printf("%c", to_print);
}
```

### Mandatory Client Implementation


___

## Usage 🏁

</div>
