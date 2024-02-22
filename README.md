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

For the mandatory implementation, `server` and `client` are implemented in `server.c` and `client.c` files inside the `src` folder.

### Server Implementation

To implement the [server](https://github.com/PedroZappa/42_minitalk/blob/main/src/server.c)'s signal handling functionality I chose to use `sigaction()` over `signal()`. This is because `signal()` is deprecated due to its varying behaviour across UNIX versions, making it a non-portable option. Both functions listen for a user defined signal and change de default signal action associated to it. The main difference between them is that `sigaction()` employs a specialized struct to store more information, giving the user finer control over signals.

The `server`'s **main()** function declares and initializes a `struct sigaction` variable called `sa`. `sa_sigaction` is set to the function `ft_server_sighandler()`, and `sa_flags` is set to the bits for `SA_SIGINFO` and `SA_RESTART` turned on.

> [!Note]
>
> `SA_SIGINFO` gives the user access to extended signal information; `sigaction()` switches from using `sa_handler` to `sa_sigaction`.
>
> `SA_RESTART` provides BSD compatible behaviour allowing certain system calls to be restartable across signals.

```c
struct sigaction	sa;

sa.sa_handler = ft_server_sighandler;
sa.sa_flags = SA_SIGINFO | SA_RESTART;
```

The `sa` struct is then passed into `t_set_sigaction()` to set event handling for `SIGUSR1` and `SIGUSR2` signals.

Prints the `server`'s' `pid` to `stdout` and enters an infinite loop, listening for a signal to catch.
```c
while (1)
	pause();
```
___
#### `ft_server_sighandler()`

Any time either, a `SIGUSR1` or a `SIGUSR2` signal is received, the `ft_server_sighandler()` function is called. All its local variables are static, therefore automatically initialized to 0;

It waits for 100 microseconds before starting to operate. It first receives and integer representing the length of the message, then the actual bits of the message follow. To assemble the received data the following bitwise operations are used:
```c
if ((sig == SIGUSR2) && !server.received)
	server.data |= 1 << (((sizeof(int) * 8) - 1) - server.bits);
else if ((sig == SIGUSR2) && server.received)
	server.data |= 1 << (((sizeof(char) * 8) - 1) - server.bits);
```

The bitwise operations | (OR) and << (Left-Shift) are used together to set the received bits in the proper place in memory. This operation only happens when a `SIGUSR2` is received. Any time a `SIGUSR1` is caught, the server acknowledges it and keeps listening for further signals.


___

### Mandatory Client Implementation


___

## Usage 🏁

</div>
