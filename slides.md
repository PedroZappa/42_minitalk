---
theme: dracula
font:
  sans: Fira Code
  mono: Fira Code
  serif: Fira Code
class: 'text-center'
highlighter: shiki
colorSchema: dark
info: minitalk :A minimalistic implementation of a small data exchange program using UNIX signals. 
transition: slide-left
title: minitalk
author: passunca
mdc: true
---

# minitalk

A minimalistic implementation of a small data exchange program using UNIX signals 

<div class="pt-12">
  <span @click="$slidev.nav.next"
		class="px-2 py-1 rounded cursor-pointer"
		hover="bg-white bg-opacity-10"
  >
    <carbon:arrow-right class="inline"/>
  </span>
</div>

<img
  class="absolute -bottom-18 -right--5 w-50 opacity-80"
  src="/img/42porto.svg"
  alt="42 logo"
/>

<!--
Project headline
-->

---
layout: two-cols
class: '-top--15 -left--5'
transition: slide-up
title: Hello Whirl
---

# Hello Whirl!
## I am Pedro Ribeiro

`42 Student`

___

> Rank : 2
>
> Grade : Learner
___
<br>

**42_Intra** : @passunca

**GitHub** : @PedroZappa

::right::

<img
  class="w-100 opacity-80 -bottom--60 border-3"
  border="rounded"
  src="/img/PZ_DBG.JPG"
  alt="Pedro Ribeiro Photo"
/>

<!--
Introduce yourself!
-->

---
layout: section
class: '-left--5'
title: Project Requirements
---

# 1.
# Project Requirements

<!--
Here come them Reqs!
-->

---
layout: full
class: '-top--5'
transition: slide-up
title: Server Features
---

# Server Features

<br>

<v-clicks>

- When executed, prints its **pid**;

- Handles incoming **SIGUSR1** & **SIGUSR2** signals;

- Receives a **message** bit-by-bit:

- **Acknowledges** reception by <span class="color-red">sending a signal back</span> to the client;

- Prints the **message** once it has been fully received;

- Handles multiple clients `in a row`.

</v-clicks>

<!--
Let's chat about Server side Features!
-->

---
layout: full
class: '-top--5'
title: Client Features
---

# Client Features

<br>

<v-clicks>

* Takes two command-line arguments:
	* **pid** of the server;
	* **message** to be sent;

* Sends the **message** bit-by-bit to the server;
	* Communicates using only **SIGUSR1** & **SIGUSR2** signals;

</v-clicks>

<!--
Let's chat about client side Features!
-->

---
layout: section
class: '-left--5'
title: Client-Server Communication
---

# 2.
# Client-Server Communication

<!--
How does Client-Server Communication work?
-->

---
layout: center
transition: slide-up
title: Server-Client Diagram
---

<h1 style="text-align: center">Server-Client Diagram</h1>

<img
	class="w-200"
	border="rounded-lg"
	src="/img/server-client-diagram.png"
	alt="Server-Client Diagram"
/>

<!--
Here's a Server-Client Diagram!

We can't send a message directly as a string.
-->

---
layout: section
class: '-left--5'
title: Client-Server Communication
---

# 3.
# UNIX Signals

<!--
Them UNIX Sigals man!
-->

---
layout: full
transition: slide-down
title: UNIX Signals
---

<h1 style="text-align: center">But what is a Signal?</h1>

<v-clicks>

* A Signal is a reporter of **events**;


When a process receives a Signal:

* It is interrupted;

* A default **Signal Action** is triggered;

</v-clicks>

<br>

<v-click>

Signals are useful tools for `Interprocess Communication` (IPC).

</v-click>

<!--
Let's go deeper into Signals!
-->

---
layout: full
title: UNIX Signals Table
---

<h2 style="text-align: center">Each Signal is defined by an Integer and a Macro</h2>

| Signal Macro | Signal Number | Default Action | Description |
| --- | --- | --- | --- |
| **SIGHUP** | 1 | Term | Hang-up or death of the controlling process detected. |
| **SIGINT** | 2 | Term | Triggered when the user  sends an interrupt by pressing `<Ctrl-c>`. |
| **SIGTRAP** | 5 | Core | Trace/breakpoint trap. |
| **SIGFPE** | 8 | Core | Floating Point Exception, an arithmetic Error. |
| **SIGKILL** | 9 | Term | Terminating signal, **Cannot be caught or ignored**. |
| **SIGSEGV** | 11 | Core | Segmentation fault, invalid memory address access. |

<!--
Let's go deeper into Signals!

SIGHUP - Some daemons interpret this as "re-read your configuration file".

SIGFPE - Ex. Divide by Zero

SIGKILL - When a process receives this signal it quits immediately without doing any cleanup.

-->

---
layout: full
transition: slide-up
title: Events generate Signals
---

<h2 style="text-align: center">Events generate Signals</h2>

<br><br>

<div class="grid grid-cols-3 gap-4">
  <div>
    <h3 v-click="1">Error Events</h3>
	<p v-click="2">
		The program did an <span class="color-yellow">invalid operation</span> and cannot continue execution.
	</p>
	<p v-click="3">
		Not All errors generate signals!
	</p>
  </div>
  <div>
    <h3 v-click="1">External Events</h3>
    <p v-click="4">
		Generally related to <span class="color-yellow">I/O</span> or other processes.
	</p>
	<p v-click="5"><bold>Includes</bold>:</p>
	<ul v-click="5">
		<li>Arrival of input.</li>
		<li>Expiration of timer.</li>
		<li>Termination of a child process.</li>
	</ul>
  </div>
  <div v-click>
	<h3 v-click="1">Explicit Events</h3>
	<p v-click="6">
		Means the use of a library function like <span class="color-yellow">kill()</span> whose purpose is to generate a signal.
	</p>
  </div>
</div>

<!--
There are 3 kinds of signal generating events
-->

---
layout: two-cols
class: '-top--5'
transition: slide-up
title: Synchronous & Asynchronous Signals
---

<h1 style="text-align: center">Synchronous Signals</h1>

<br>

<v-clicks>

* Relate to specific events and are delivered during that event (unless blocked).

* Most **Errors** and **Explicit Requests** generate **Synchronous Signals**.

</v-clicks>

<v-click>

<br>

> Certain hardware errors are not 100% synchronous arriving a couple of instructions later.

</v-click>

::right::

<h1 style="text-align: center">Asynchronous Signals</h1>

<br>

<v-clicks>

* Generated by **events outside** the control of the receiving process.

* Their arrival is unpredictable.

</v-clicks>

<br>

<v-click>

## **External Events** and **Explicit Requests** applying to some other process generate **Asynchronous Signals**.

</v-click>

<!--

-->

---
layout: full
title: Delivering Signals
---

<h1 style="text-align: center">Delivering Signals</h1>

<v-click>

* When generated, a **Signal** becomes **pending** for a short period of time before it is delivered to a process.

</v-click>

<br>

<v-click>

* However, if that signal type is being <span class="color-red">blocked</span>, it may remain pending indefinitely.

> When that signal type is unblocked it will be delivered immediately.

</v-click>

<v-click>

When a signal is <span class="color-green">delivered</span>, the specified **Signal Action** is taken;

</v-click>

<br>

<v-click>

<h3>For most signals the program either:</h3>

</v-click>

<v-clicks>

* Ignores the signal;

* Uses a specified a handler function;

* Or uses the default **Signal Action** for that signal type.

</v-clicks>

<v-click>

> (except for **SIGKILL** & **SIGSTOP**: they cannot be handled or ignored 😨)

</v-click>

<!--

-->

---
layout: full
transition: slide-up
title: How About SIGUSR1 & SIGUSR2?
---

<h1 style="text-align: center">SIGUSR1 & SIGUSR2</h1>

<v-clicks>

* Can be used to indicate a desired **user-defined condition**.

* Their default **Signal Action** is to terminate the process;

</v-clicks>

<!--
SIGUSR1 & SIGUSR2 can mean anything.
-->

---
layout: two-cols-header
class: '-top-12'
title: minitalk protocol
---

<h1 style="text-align: center">minitalk Protocol</h1>

<v-click>

**SIGUSR1** and **SIGUSR2** are used to communicate between **Server** and **Client**.

___

</v-click>

<v-click>


<br>

### As a **communication protocol**, I defined:

</v-click>

::left::

<v-clicks>

For the `Server`:

</v-clicks>

<v-clicks>

* **SIGUSR1** means 0,

* and **SIGUSR2** means 1.

</v-clicks>

::right::

<v-clicks>

For the `Client`,

</v-clicks>

<v-clicks>

* **SIGUSR1** signals that a bit was received;
	> `0` or `1`

* and **SIGUSR2** signals the end of message was received.
	> `\0`

</v-clicks>

<!--

-->
---
layout: section
class: '-left--5'
title: Implementation
---

# 3.
# Implementation

<!--
Let's get into the implementation of minitalk.
-->

---
layout: quote
class: '-top-12'
transition: slide-up
title: t_protocol data type
---

<h1 style="text-align: center">t_protocol Data Type</h1>

<br>

<v-click>

* Stores all the data the **server** needs to perform its operations.

</v-click>

<br>

<div v-click="2">

```c {all|all|3|4|5|6|all}
typedef struct s_protocol
{
	int  bits;     // Number of bits received
	int  data;     // Received data
	int  received; // Flag indicating if "header" data has been received
	char *msg;     // Received message
}	t_protocol;
```

</div>

<!--
For the sake of simplicity the program uses a custom data type t_protocol which holds all the data the server needs to perform its operations:

bits : keeps track of the current byte being received.

will be set either to 32 or 8, if receiving an int or a char respectively.

data : To store all incoming bits.
received :
msg :
-->

---
layout: two-cols
class: 'pa-5'
title: Server
---

<h1 style="text-align: center">Server</h1>

<br>

```c {all|3,5-7|8|9|10-11}
int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = ft_server_sighandler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	ft_set_sigaction(&sa);
	ft_print_pid();
	while (1)
		pause();
}
```

::right::

<div v-click="1">

* Declares and initializes **sa** of type `struct sigaction`;

</div>

<div v-click="2">

* Setup **Signal Handling**:

</div>
<br>

<div v-click="2">

```c
void	ft_set_sigaction(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
		ft_perror_exit(
			"sigaction() failed to handle SIGUSR1");
	if (sigaction(SIGUSR2, sa, NULL) < 0)
		ft_perror_exit(
			"sigaction() failed to handle SIGUSR2");
}
```
</div>
<br>

<div v-click="3">

* Prints the **PID** to **stdout**;

</div>
<div v-click="4">

* Enters <span class=color-blue>infinite loop</span>, waiting for a signal to catch;

</div>

<!--
sa.sa_mask : specifies a mask of signals that should be ignored; We use sigemptyset() to initialize a signal set sa.sa_mask with all signals excluded from the set;

sa.sa_sigaction is set to the function ft_server_sighandler();

sa.sa_flags flag set has the bits for SA_SIGINFO and SA_RESTART turned on;
-->

---
layout: two-cols
class: 'pa-5'
transition: slide-down
title: Client
---

```c {all|5-9|3,10-12|13|15-16|18|19}
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		ft_perror_exit(
			"Usage: ./client [PID] [message]\n");
	else if (kill(ft_atoi(argv[1]), 0) < 0)
		ft_perror_exit("PID does not exist\n");
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_client_sighandler;
	sa.sa_flags = SA_RESTART;
	ft_set_sigaction(&sa);
	ft_sep_color('0', '=', 28, GRN);
	ft_printf("Sending to Server\n%sPID: %d%s\n",
		   YEL, ft_atoi(argv[1]), NC);
	ft_sep_color('0', '=', 28, GRN);
	ft_send_msg(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
```

::right::

<h1 style="text-align: center">Client</h1>
<br>

<div v-click="1">

* Checks if <span class="color-red">input arguments</span> are valid;

</div>
<div v-click="2">

* Declare and initializes **sa** of type `struct sigaction`;

</div>
<div v-click="3">

* Setup <span class="color-blue">Signal Handling</span>;

</div>
<div v-click="4">

* Prints the **PID** of the server to **stdout**;

</div>
<div v-click="5">

* Sends the **message** to the server bit-by-bit;

</div>
<div v-click="6">

* Terminates the program successfully;

</div>
<!--
0 :

1 :

2 :

3 : Pretty much the same as in the server, but instead setting its our signal handler;

4 :

5 :

6 :
-->

---
layout: two-cols
class: 'pa-5'
transition: slide-up
title: ft_client_sighandler()
---
<br>
<br>
<br>
<br>

```c {all|3-4|5-12}
static void	ft_client_sighandler(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("%s*%s", YEL, NC);
	else if (sig == SIGUSR2)
	{
		ft_printf("\n");
		ft_sep_color('0', '=', 28, GRN);
		ft_printf("Message successfully sent!\n");
		ft_sep_color('0', '=', 28, GRN);
		exit(EXIT_SUCCESS);
	}
}

```
::right::

<h1 style="text-align: center">ft_client_sighandler()</h1>
<br>
<br>
<br>

<div v-click="1">

* **SIGUSR1** from server:
> bit successfully received;

</div>
<div v-click="2">

* **SIGUSR2** from server:
> message successfully received;

</div>

<!--

-->

---
layout: default
class: 'pr-50 pl-50'
transition: slide-up
title: Client into ft_send_msg()
---

<h1 style="text-align: center">Sending the Message to the Server</h1>

```c {18}
/* Client */
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
		ft_perror_exit(
			"Usage: ./client [PID] [message]\n");
	else if (kill(ft_atoi(argv[1]), 0) < 0)
		ft_perror_exit("PID does not exist\n");
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_client_sighandler;
	sa.sa_flags = SA_RESTART;
	ft_set_sigaction(&sa);
	ft_sep_color('0', '=', 28, GRN);
	ft_printf("Sending to Server\n%sPID: %d%s\n", YEL, ft_atoi(argv[1]), NC);
	ft_sep_color('0', '=', 28, GRN);
	ft_send_msg(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
```

<!--

-->

---
layout: two-cols
class: 'pa-3'
title: ft_send_msg()
---
```c {all|5,9|10-11|14-15|18,20}
/* Client */
static void	ft_send_msg(pid_t pid, char *msg)
{
	int		i;
	int		msglen;

	i = 0;
	{
		msglen = ft_strlen(msg);
		ft_printf("%sOutbound msg's length = %d%s\n",
			CYN, msglen, NC);
		ft_send_int(pid, msglen);
		ft_printf("\n%sSending Message%s\n", GRN, NC);
		while (msg[i] != '\0')
			ft_send_char(pid, msg[i++]);
		ft_printf("\n");
		ft_sep_color('0', '=', 28, GRN);
		ft_printf("%sSending NULL Terminator\n", MAG, NC);
		ft_sep_color('0', '=', 28, GRN);
		ft_send_char(pid, '\0');
	}
}
```

::right::

<h1 style="text-align: center">ft_send_msg()</h1>

<br>

<div v-click="1">

* Take the message <span class="color-green">length</span>;

</div>
<div v-click="2">

* Print the message <span class="color-green">length</span> to **stdout**;

</div>
<div v-click="3">

* Send message <span class="color-blue">char by char</span> to the server;

</div>
<div v-click="4">

* Send <span class="color-red">NULL Terminator</span>

</div>

<!--
0 : ft_send_msg()

1 : Server PID | Message

2 : Take Message Length

3 : Send Message Length as an 32-bit integer bit-by-bit

4 : Send Message chars bit-by- bit

5 : Send NULL Terminator

-->

---
layout: two-cols
class: 'pa-5'
transition: slide-down
title: Client sending Int
---
<br>
<br>

```c {all|4,7|7|7|5,10|11|12|8-13}
/* Client */
void	ft_send_int(pid_t pid, int num)
{
	int		bitshift;
	char	bit;

	bitshift = ((sizeof(int) * 8) - 1);
	while (bitshift >= 0)
	{
		bit = (num >> bitshift) & 1;
		ft_send_bit(pid, bit, 1);
		--bitshift;
	}
}
```
<br>
<div v-click="3" style="text-align: center">

```c
42
00101010
MSB ----- LSB

```
</div>

::right::

<h1 style="text-align: center">Sending an Int</h1>
<br>

<ul>
	<li v-click="1">Declare & initialize <span class="color-red">bitshift</span> with the size of the <span class="color-green">binary representation of an integer</span>.</li>
	<li v-click="2">Loop while <span class="color-red">bitshift</span> is larger than 0.</li>
	<p v-click="3" class="text-center"><span class="color-red">bitshift</span> is used to iterate the incoming data from the <span class="color-yellow">Most Significant Bit</span> (MSB) to the <span class="color-yellow">Least Significant Bit</span> (LSB)</p>
	<li v-click="4">Isolate the current <span class="color-blue">bit</span>.</li>
	<li v-click="5">Send the <span class="color-blue">bit</span> to the server.</li>
	<li v-click="6">Decrement <span class="color-red">bitshift</span>.</li>
	<li v-click="7">Repeat until the LSB <span class="color-blue">bit</span> has been sent.</li>
</ul>
<!--
0 :

1 : Bitshift

2 : Loop

3 : MSB & LSB

4 : Get bit

5 : Send bit

6 : Decrement bitshift

7 : Loop till LSB is sent

Effectively moving from left to right through the bits being sent
-->

---
layout: two-cols
class: 'pa-5'
title: Client sending char bits
---
<br>
<br>

```c {all|all|4,7|8-13}
/* Client */
void	ft_send_char(pid_t pid, char c)
{
	int		bitshift;
	char	bit;

	bitshift = ((sizeof(char) * 8) - 1);
	while (bitshift >= 0)
	{
		bit = (c >> bitshift) & 1;
		ft_send_bit(pid, bit, 1);
		--bitshift;
	}
}
```

::right::

<h1 style="text-align: center">Sending Chars</h1>
<br>

<div v-click="1">

Most of the logic is the same as what can be found in <span class="color-yellow">ft_send_int()</span>.

</div>

<div v-click="2">

* Except that <span class="color-red">bitshift</span> is initialized with the size of the <span class="color-green">binary representation of a char</span>.

</div>

<div v-click="3">

* Repeats until the LSB <span class="color-blue">bit</span> has been sent.

</div>



<!--
0 :

1 :

2 :

3 :

-->

---
layout: two-cols
class: 'pa-5'
transition: slide-up
title: Sending bits
---
<br>
<br>

```c {all|5|7-9|11|13-15|17-18}
/* Client */
void	ft_send_bit(pid_t pid, char bit,
				 char pause_flag)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) < 0)
			ft_perror_exit(
				"kill() failed sending SIGUSR1\n");
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) < 0)
			ft_perror_exit(
				"kill() failed sending SIGUSR2\n");
	}
	if (pause_flag != 0)
		pause();
}
```

::right::

<h1 style="text-align: center">Sending a bit to Server</h1>
<br>

<ul>
	<li v-click="1">
		If <span class="color-blue">bit</span> is 0 :
	</li>
	<p v-click="2" style="text-align: center">
		Send <span class="color-yellow">SIGUSR1</span>.
	</p>
	<li v-click="3">
		Else if <span class="color-blue">bit</span> is 1 :
	</li>
	<p v-click="4" style="text-align: center">
		Send <span class="color-yellow">SIGUSR2</span>.
	</p>
	<li v-click="5">
		If <span class="color-red">pause_flag</span> is set to 1, the server pauses waiting for the next data chunk to arrive.
	</li>
</ul>


<!--
0 :

1 :

2 :

3 :

-->

---
layout: two-cols
class: 'pa-3 -top-5'
transition: slide-left
title: ft_server_sighandler()
---

<br>

```c {all|1-2|4-5|7|9-10}
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	static t_protocol	server;
	static int			i;

	usleep(PAUSE);
	(void)context;
	if (!server.bits)
		server.data = 0;
	if ((sig == SIGUSR2) && !server.received)
		server.data |= 1 <<
			(((sizeof(int) * 8) - 1) - server.bits);
	else if ((sig == SIGUSR2) && server.received)
		server.data |= 1 <<
			(((sizeof(char) * 8) - 1) - server.bits);
	++server.bits;
	ft_strlen_received(&server);
	ft_print_msg(&server, &i, info->si_pid);
	ft_send_bit(info->si_pid, 0, 0);
}
```
::right::

<h1 style="text-align: center">ft_server_sighandler()</h1>
<br>
<br>
<br>
<ul>
	<li v-click="1">
		Our handler follows a <span class="color-green">standard prototype</span>;
	</li>
	<li v-click="2">
		All local variables are <span class="color-pink">static</span>, therefore automatically initialized to 0;
	</li>
	<li v-click="3">
		Waits for <span class="color-yellow">PAUSE</span> microseconds;
	</li>
	<li v-click="4">
		If <span class="color-red">server.bits</span> is 0, set/reset <span class="color-red">server.data</span> to 0;
	</li>

</ul>

<!--
0 :

1 : Handler Prototype

sig : The number of the signal that caused invocation of the handler.

info : A pointer to a siginfo_t, which is a structure containing further information about  the
	  signal, as described below.

ucontext : Commonly, the  handler  function doesn't make any use of the third argument.

2 :

3  : usleep is used to avoid scrambling the signals

4 :

5 :
-->

---
layout: two-cols
class: 'pa-3 -top-5'
transition: slide-up
title: ft_server_sighandler() Receiving Data
---
<br>

```c {11-13|17|18}
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	static t_protocol	server;
	static int			i;

	usleep(PAUSE);
	(void)context;
	if (!server.bits)
		server.data = 0;
	if ((sig == SIGUSR2) && !server.received)
		server.data |= 1 <<
			(((sizeof(int) * 8) - 1) - server.bits);
	else if ((sig == SIGUSR2) && server.received)
		server.data |= 1 <<
			(((sizeof(char) * 8) - 1) - server.bits);
	++server.bits;
	ft_strlen_received(&server);
	ft_print_msg(&server, &i, info->si_pid);
	ft_send_bit(info->si_pid, 0, 0);
}
```
::right::

<h1 style="text-align: center">Receiving Data</h1>

<ul>
	<li>
		First the server expects an <span class="color-green">int</span> as <span class="color-pink">Header Information</span>, the <span class="color-blue">length</span> of the message;
	</li>
	<li v-click="1">
		Every time a <span class="color-yellow">SIGUSR1</span> or <span class="color-yellow">SIGUSR2</span> is caught, <span class="color-red">server.bits</span> is incremented;
	</li>
	<li v-click="2">
		After all the <span class="color-blue">bits</span> of the <span class="color-green">int</span> have been received, the conditions to trigger <span class="color-yellow">ft_strlen_received()</span> code block are reached;
	</li>
</ul>

<!--
0 :

1 :

2 :

3 :

4 :

5 :
-->

---
layout: two-cols
class: 'pa-3 -top-5'
transition: slide-down
title: ft_strlen_received()
---
<br>

```c {all|4-5|7|9|11-12|13-14|15|16}
/* Server */
static void	ft_strlen_received(t_protocol *server)
{
	if ((server->bits == (sizeof(int) * 8)) &&
		!server->received)
	{
		server->received = 1;
		ft_printf("%sMessage Length : %s", YEL, NC);
		ft_putnbr(server->data);
		ft_printf("\n");
		server->msg = ft_calloc((server->data + 1),
						  sizeof(char));
		if (!server->msg)
			ft_perror_exit("ft_calloc() failed\n");
		server->msg[server->data] = '\0';
		server->bits = 0;
	}
}
```
::right::

<h1 style="text-align: center">ft_strlen_received()</h1>

<ul>
	<li v-click="1">
		When data the size of an <span class="color-green">int</span> is received, and the <span class="color-purple">Header Information</span> is yet to be registered;
	</li>
	<li v-click="2">
		Sets header data received <span class="color-pink">flag</span> to true;
	</li>
	<li v-click="3">
		Prints the <span class="color-blue">length</span> of the message to the console;
	</li>
	<li v-click="4">
		<span class="color-red">Allocates memory</span> for the message;
	</li>
	<li v-click="5">
		Protects against <span class="color-yellow">ft_calloc()</span> failure.
	</li>
	<li v-click="6">
		The message is <span class="color-gray">NULL</span> terminated;
	</li>
	<li v-click="7">
		<span class="color-yellow">server->bits</span> is reset to 0 to prepare the server to received the message <span class="color-blue">bits</span>;
	</li>
</ul>

<!--
0 :

1 :

2 :

3 :

4 :

5 :
-->

---
layout: two-cols
class: 'pa-3 -top-5'
title: ft_server_sighandler() Data Received
---
<br>

```c {19|20}
/* Server */
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	static t_protocol	server;
	static int			i;

	usleep(PAUSE);
	(void)context;
	if (!server.bits)
		server.data = 0;
	if ((sig == SIGUSR2) && !server.received)
		server.data |= 1 <<
			(((sizeof(int) * 8) - 1) - server.bits);
	else if ((sig == SIGUSR2) && server.received)
		server.data |= 1 <<
			(((sizeof(char) * 8) - 1) - server.bits);
	++server.bits;
	ft_strlen_received(&server);
	ft_print_msg(&server, &i, info->si_pid);
	ft_send_bit(info->si_pid, 0, 0);
}
```
::right::

<h1 style="text-align: center">Receiving Data</h1>


* First the server expects an <span class="color-green">int</span> as <span class="color-purple">Header Information</span>, the length of the message;

* Every time a <span class="color-yellow">SIGUSR1</span> or <span class="color-yellow">SIGUSR2</span> is caught, <span class="color-red">server.bits</span> is incremented;

* After all the <span class="color-blue">bits</span> of the <span class="color-green">int</span> have been received, the conditions to trigger <span class="color-yellow">ft_strlen_received()</span> code block are reached;

<div v-click="1">

* The server then proceeds to accumulate the incoming <span class="color-green">chars</span>;

</div>
<div v-click="2">

When the message is <span class="color-red">fully received</span> it is printed;

</div>

<!--
0 :

1 :

2 :

3 :

4 :

5 :
-->
---
layout: two-cols
class: 'pa-3 -top-5'
transition: slide-up
title: ft_print_msg()
---
<br>

```c {all|4|6|7}
static void	ft_print_msg(t_protocol *server,
						 int *i, pid_t pid)
{
	if ((server->bits == 8) && server->received)
	{
		server->msg[*i] = server->data;
		++(*i);
		if (server->data == '\0')
		{
			ft_printf("[%sMessage bytes received!%s]\n",
				MAG, NC);
			ft_printf("Message:\n%s%s%s\n",
				GRN, server->msg, NC);
			ft_print_pid();
			free(server->msg);
			server->msg = NULL;
			server->received = 0;
			*i = 0;
			ft_send_bit(pid, 1, 0);
		}
		server->bits = 0;
	}
}
```
::right::

<h1 style="text-align: center">ft_print_msg()</h1>

<ul>
	<p v-click="1">
		Once 8 <span class="color-blue">bits</span> have been received, and the <span class="color-pink">Header Information</span> has already been received:
	</p>
	<li v-click="2">
		The <span class="color-pink">byte</span> is stored in <span class="color-yellow">server->msg[i]</span>;
	</li>
	<li v-click="3">
		Then <span class="color-green">i</span> is incremented so that when indexed <span class="color-yellow">server->msg[i]</span> points to the next byte in memory;
	</li>
</ul>

<!--
0 :

1 :

2 :

3 :

4 :

5 :
-->
---
layout: two-cols
class: 'pa-3 -top-5'
transition: slide-right
title: Message Received
---
<br>

```c {7|9-12|13|14-15|16|17|18}
static void	ft_print_msg(t_protocol *server,
						 int *i, pid_t pid)
{
	if ((server->bits == 8) && server->received)
	{
		server->msg[*i] = server->data;
		++(*i);
		if (server->data == '\0')
		{
			ft_printf("[%sMessage bytes received!%s]\n",
				MAG, NC);
			ft_printf("Message:\n%s%s%s\n",
				GRN, server->msg, NC);
			ft_print_pid();
			free(server->msg);
			server->msg = NULL;
			server->received = 0;
			*i = 0;
			ft_send_bit(pid, 1, 0);
		}
		server->bits = 0;
	}
}
```
::right::

<h1 style="text-align: center">Message Received</h1>

<ul>
	<p>
		When the <span class="color-pink">byte</span> received is the <span class="color-gray">NULL</span> terminator:
	</p>
	<li v-click="1">
		Prints the message to the console.
	</li>
	<li v-click="2">
		Re-Prints the server <span class="color-yellow">pid</span> to the console.
	</li>
	<li v-click="3">
		Frees <span class="color-yellow">server->msg</span> and sets it to NULL.
	</li>
	<li v-click="4">
		<span class="color-purple">Header Information</span> received flag is set to false;
	</li>
	<li v-click="5">
		<span class="color-green">i</span> reset to 0;
	</li>
	<li v-click="6">
		<span class="color-yellow">SIGUSR2</span> is sent to the server, signaling the end of the transmission of data;
	</li>
</ul>

<!--
0 :

1 :

2 :

3 :

4 :

5 :
-->

---
layout: two-cols
class: 'pa-3 -top-5'
transition: slide-up
title: ft_server_sighandler() Data Received
---
<br>

```c {19|20}
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	static t_protocol	server;
	static int			i;

	usleep(PAUSE);
	(void)context;
	if (!server.bits)
		server.data = 0;
	if ((sig == SIGUSR2) && !server.received)
		server.data |= 1 <<
			(((sizeof(int) * 8) - 1) - server.bits);
	else if ((sig == SIGUSR2) && server.received)
		server.data |= 1 <<
			(((sizeof(char) * 8) - 1) - server.bits);
	++server.bits;
	ft_strlen_received(&server);
	ft_print_msg(&server, &i, info->si_pid);
	ft_send_bit(info->si_pid, 0, 0);
}
```
::right::

<h1 style="text-align: center">Receiving Data</h1>

<ul>
	<li>
		First the server expects an <span class="color-green">int</span> as <span class="color-purple">Header Information</span>, the length of the message;
	</li>
	<li>
		Every time a <span class="color-yellow">SIGUSR1</span> or <span class="color-yellow">SIGUSR2</span> is caught, <span class="color-red">server.bits</span> is incremented;
	</li>
	<li>
		After all the <span class="color-blue">bits</span> of the <span class="color-green">int</span> have been received, the conditions to trigger <span class="color-yellow">ft_strlen_received()</span> code block are reached;
	</li>
	<li>
		The server then proceeds to accumulate the incoming <span class="color-blue">bits</span>; when the message is fully received it is printed;
	</li>
</ul>
<div v-click="1">

* The server sends a <span class="color-yellow">SIGUSR1</span> to the client;

> (bit received)

</div>

<!--
0 :

1 :

2 :

3 :

4 :

5 :
-->

---
layout: section
class: '-left--5'
transition: slide-up
title: Demonstration
---

# 4.
# Demonstration


<!--
Eye candy baby!
-->

---
layout: fact
transition: slide-right
title: Demonstration
---

<video controls autoplay>
	<source src="/video/minitalk-demo.mp4" 
		type="video/mp4" />
</video>

<!--
Enjoy 🥰
-->

---
layout : full
transition: slide-up
title : References
---

<h1 style="text-align: center">References</h1>

* [sigaction(2)](https://man7.org/linux/man-pages/man2/sigaction.2.html)

* [signal(2)](https://man7.org/linux/man-pages/man2/signal.2.html)

* [signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)

* [Standard Signals (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Standard-Signals.html)
* [Miscellaneous Signals (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Miscellaneous-Signals.html)
* [Signaling Another Process (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Signaling-Another-Process.html)

* [Understanding minitalk - saeby/lfabbian](https://42-cursus.gitbook.io/guide/rank-02/minitalk/understand-minitalk)


<!--

-->

---
layout : two-cols
transition: slide-left
title : Tech Stack
---

<h1 style="text-align: center">Tech Stack</h1>

<br>

## <span class="color-green">Project Tooling</span>

<br>

**LANG**= C

**SCRIPTS**= bash

**BUILD**= make

**DEBUG**= gdb

**MEMCHECK**= valgrind

**VERSION_CTL**= git

::right::

## <span class="color-green">Dev Env</span>

**SHELL**= zsh

**PROMPT**= starship

**EDITOR**= neovim

**MULTIPLX**= tmux 

**TERM**= kitty

**WM**= i3wm

<br>

## <span class="color-green">Presentation</span>

**TOOL**= slidev

**SCREENREC**= simplescreenrecorder



<!--

-->

---
layout : full
transition: view-transition
title : Credits
---

<h1 style="text-align: center">Credits</h1>


* [SlidesCarnival](https://www.slidescarnival.com/) for slides inspiration; 

* `tchow-so` for the incredible intro picture;

---
layout : end
title : end
---

<h1 style="text-align: center">This was <span class="color-red">minitalk</span>!</h1>

> by passunca

A minimalistic implementation of a small data exchange program using UNIX signals. 

<br>
<img
  class="absolute -bottom-18 -right--5 w-50 opacity-80"
  src="/img/42porto.svg"
  alt="42 logo"
/>
<h2 style="text-align: center">Thank you!</h2>
