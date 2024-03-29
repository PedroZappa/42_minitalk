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
0: Today I'm gonna be.presenting ..

But before we start, let me introduce myself.


-->

---
layout: two-cols
class: '-top--15'
transition: slide-up
title: Hello Whirl
---

# Hello Whirl!
## I am Pedro Ribeiro

`42 Student` && `Musician`

<br>

___

> Rank : 2
>
> Grade : Learner
___
<br>

<div class="text-left">
<span class="color-orange">42 Intra</span> : @passunca

<span class="color-orange">Github</span> : @PedroZappa
</div>

::right::

<img
  class="w-110 pa-2 opacity-80 rounded-3xl border-4 border-purple"
  border="rounded"
  src="/img/PZ_DBG.JPG"
  alt="Pedro Ribeiro Photo"
/>

<!--
Introduce yourself!

Before I started to learn to code my first passion was music. 

I studied Electric bass performance in the US and worked as a full-time musician with musicians from all around the world.

In music, in a band setting, it is all about playing for the team.

As a wise musician once told me: "A band is as good as its worst team player."

Or rather, as music is a language,

"A band is as good as its worst communicator"

Which brings us to the subject of the minitalk project : 

Data Communication using signals.


-->

---
layout: section
class: '-left--5'
title: Project Requirements
---

# <span class="color-green">1.</span>
# Project Requirements

<!--
Here come them Reqs!
-->

---
layout: full
---

<h1 class="text-center pt-20 pb-10">minitalk</h1>

<p class="text-center">
A minimalistic implementation of a small data exchange program using UNIX signals.
</p>
<br>
<div class="grid grid-cols-2">
	<div v-click="1" class="note">
		<h2 v-click="1" class="text-center mt-10"><span class="color-green">Server</span></h2>
		<p v-click="1" class="text-center">Receives a message.</p>
	</div>
	<div v-click="2" class="note">
		<h2 v-click="2" class="text-center mt-10"><span class="color-green">Client</span></h2>
		<p v-click="2" class="text-center">Sends a message.</p>
	</div>
</div>

<style>
h1 {
  font-size: 3.5rem;
  padding-bottom: 2rem;
}

h2 {
  font-size: 2.5rem;
  padding-bottom: 1rem;
}
.note {
	@apply border-2 border-green rounded-3xl p-5 w-80 ml-15
}
</style>

<!--
0 : minitalk : elevator pitch

**Audience Interaction** : Who here has already validated their minitalk project?

... You're definitely not forth-Kickoffers, otherwise you'd be doing some serious speedrunning time-travelling biz!If that were the case you'd have to tell me all about it :)

1 : Server

2 : Client
-->

---
layout: full
class: '-top--5'
transition: slide-up
title: Server Features
---

<div class="text-center">
	<h1>Server Features</h1>
</div>

<br>

<div class="ml-35 mt-7">
	<li v-click="1">
		When executed, prints its <span class="color-yellow">PID</span>;
	</li>
	<li v-click="2">
		Handles incoming <span class="color-yellow">SIGUSR1</span> & <span class="color-yellow">SIGUSR2</span> signals;
	</li>
	<li v-click="3">
		Receives a <span class="color-blue">message</span> bit-by-bit:
	</li>
	<li v-click="4">
		<span class="color-pink">Acknowledges</span> receiving a bit by <span class="color-red">sending a signal back</span> to the <span class="color-orange">client</span>;
	</li>
	<li v-click="5">
		Prints the <span class="color-blue">message</span> once it has been fully received;
	</li>
	<li v-click="6">
		Handles multiple <span class="color-orange">clients</span> <span class="color-green">in a row</span>.
	</li>
</div>

<style>
li {
  padding-bottom: 1rem;
}
</style>

<!--
Let's chat about Server side Features!

0: Print PID

1: Handle SIGUSR1 & SIGUSR2

2: Receive message bit-by-bit

3: Acknowledge receiving a bit

4: Print message once it has been fully received

5: Handle multiple clients in a row
-->

---
layout: full
class: '-top--5'
title: Client Features
---

<div class="text-center">
	<h1>Client Features</h1>
</div>

<br>

<div class="ml-35 mt-7">
	<p v-click="1">
		Takes two <span class="color-green">command-line arguments</span>:
	</p>
	<li v-click="2">
		<span class="color-yellow">pid</span> of the <span class="color-orange">server</span>;
	</li>
	<li v-click="3">
		<span class="color-blue">message</span> to be sent;
	</li>
	<br>
	<p v-click="4">
		Sends the <span class="color-blue">message</span> bit-by-bit to the <span class="color-orange">server</span>;
	</p>
	<li v-click="5">
		Communicating using only <span class="color-yellow">SIGUSR1</span> & <span class="color-yellow">SIGUSR2</span> signals;
	</li>
</div>

<!--
Let's chat about client side Features!

1 : Take two command-line arguments

2 : pid of the server

3 : message to be sent

4 : Sends message bit-by-bit

5 : Communicating using only SIGUSR1 & SIGUSR2
-->

---
layout: section
class: '-left--5'
title: Client-Server Communication
---

# <span class="color-green">2.</span>
# Client-Server Communication

<!--
How does Client-Server Communication work?
-->

---
layout: center
transition: slide-up
title: Server-Client Diagram
---

<h1 style="text-align: center"><span class="color-orange">Server</span>-<span class="color-orange">Client</span> Diagram</h1>

<img
	class="w-200"
	border="rounded-lg"
	src="/img/server-client-diagram.png"
	alt="Server-Client Diagram"
/>

<!--
Here's a Server-Client Diagram!

We can't send a message directly as a string.

First, the computer must interpret the string as a sequence of ASCII.

>>> Kickoffers, during your piscine how was your first encounter with the ASCII table? A shock? A match made in chromium? Firefox... whatever

To be able to send the data string using only SIGUSR1 & SIGUSR2, we must convert each char in the string to its binary representation. 


-->

---
layout: section
class: '-left--5'
title: Client-Server Communication
---

# <span class="color-green">3.</span>
# UNIX Signals

<!--
Them UNIX Signals man!

So, what are these things they call UNIX signals?

-->

---
layout: full
transition: slide-down
title: UNIX Signals
---

<h1 style="text-align: center">But what is a <span class="color-green">Signal</span>?</h1>

<div v-click="1" class="note">
	<h2 v-click="1">A signal is a reporter of <span class="color-pink">events</span>.</h2>
	<br>
	<p v-click="2">
		When a process receives a <span class="color-green">Signal</span>:
	</p>
	<li v-click="2">
		The <span class="color-yellow">process</span> is <span class="color-red">interrupted</span>.
	</li>
	<li v-click="3">
		A default <span class="color-pink">Signal Action</span> is triggered.
	</li>
	<br>
	<hr v-click="3">
	<p v-click="4">
		<span class="color-green">Signal</span> are useful tools for <span class="color-orange">Interprocess Communication</span> (IPC).
	</p>
</div>

<style>
h1 {
	@apply text-5xl text-center
}
.note {
	@apply flex-col border-2 border-blue rounded-3xl w-140 pa-5 ml-35 mt-15
}
</style>

<!--
Let's go deeper into Signals!

1 : Definining Signal

2 : When a signal is received by a process....

3 : Default signal Action

4 : Interprocess Communication



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
| **SIGKILL** | 9 | Term | Terminating signal, <span class="color-red">Cannot be caught or ignored</span>. |
| **SIGSEGV** | 11 | Core | Segmentation fault, invalid memory address access. |

<!--
Let's go deeper into Signals!

SIGHUP - Some daemons interpret this as "re-read your configuration file".

SIGFPE - Ex. Divide by Zero

SIGKILL - When a process receives this signal it quits immediately without doing any cleanup.

-->

---
layout: full
class: '-top--5'
title: Signals VHS
---

<video controls loop>
	<source src="/video/signals.mp4"
		type="video/mp4" />
</video>

<!--
Signals in the terminal


you can find a full lis of all the available signals in the man page, as they say
RTFM, Read The Friendly Manual :)
-->

---
layout: full
transition: slide-up
title: Events generate Signals
---

<h2 class="text-center mt-5">Events generate <span class="color-green">Signals</span></h2>

<br>
<br>

<div class="grid grid-cols-3 gap-4">
  <section v-click="1">
    <h3 v-click="1">Error Events</h3>
	<p v-click="2">
		The program did an <span class="color-red">invalid operation</span> and cannot continue execution.
	</p>
	<hr v-click="3">
			<br>
	<p v-click="3" class="color-yellow text-center">
		Not All errors generate <span class="color-green">Signals</span>!
	</p>
  </section>
  <section v-click="1">
    <h3 v-click="1">External Events</h3>
    <p v-click="4">
		Generally related to <span class="color-yellow">I/O</span> or other processes.
	</p>
	<hr v-click="4">
	<p v-click="5" class="color-cyan">Includes:</p>
	<ul v-click="5">
		<li>Arrival of input.</li>
		<li>Expiration of timer.</li>
		<li>Termination of a child process.</li>
	</ul>
  </section>
  <section v-click="1">
	<h3 v-click="1">Explicit Events</h3>
	<p v-click="6">
		Means the use of a library function like <span class="color-yellow">kill()</span> whose purpose is to generate a <span class="color-green">signal</span>.
	</p>
  </section>
</div>

<style>
section {
	@apply border-2 border-green rounded-3xl p-5
}
</style>

<!--
There are 3 kinds of signal generating events

# Error Events 

2 : Invalid Op and cannot go on

# External Events

4 : Related I/O and other processes
i
# Explicit Events 

6 : That include using functions  like kill() or what I just demoed with htop.

-->

---
layout: two-cols
class: '-top--5'
transition: slide-up
title: Synchronous & Asynchronous Signals
---

<h1 style="text-align: center">Synchronous Signals</h1>

<br>
<hr>
<br>

<div>
	<li v-click="1">
		Relate to specific <span class="color-pink">events</span> and are delivered during that event (unless blocked).
	</li>
	<li v-click="2">
		Most <span class="color-red">Errors</span> and <span class="color-green">Explicit Requests</span> generate <span class="color-purple">Synchronous Signals</span>.
	</li>
	<p v-click="3" class="text-sm color-yellow note">
		Certain <span class="color-red">hardware errors</span> are not 100% synchronous arriving a couple of instructions later.
	</p>
</div>

::right::

<h1 style="text-align: center">Asynchronous Signals</h1>
<br>
<hr>
<br>

<div>
	<li v-click="4">
		Generated by <span class="color-yellow">events outside</span> the control of the receiving process.
	</li>
	<li v-click="5">
		Their arrival is <span class="color-red">unpredictable</span>.
	</li>
	<li v-click="6">
		<span class="color-green">External Events</span> and <span class="color-green">Explicit Requests</span> applied to some other process generate <span class="color-purple">Asynchronous Signals</span>.
	</li>
</div>

<style>
.note {
	@apply border-2 border-green rounded-3xl p-5 w-100
}
</style>

<!--

-->

---
layout: two-cols
title: Delivering Signals
---

<br>
<br>
<h1 style="text-align: center">Delivering Signals</h1>
<br>

<div class="mr-7">
	<li v-click="1">
		When generated, a <span class="color-orange">Signal</span> becomes <span class="color-yellow">pending</span> for a short period of time before it is <span class="color-green">delivered</span> to a process.
	</li>
	<li v-click="2">
		However, if that <span class="color-blue">signal type</span> is being <span class="color-red">blocked</span>, it may remain <span class="color-yellow">pending</span> indefinitely.
	</li>
	<br>
	<hr v-click="2">
	<p v-click="3">
		When a signal type is <span class="color-red">unblocked</span> it will be <span class="color-green">delivered</span> immediately.
	</p>
</div>
<br>

::right::

<br><br><br>

<div v-click="4" class="note">
	<h4 v-click="4"><span class="color-green">For most signals</span> a program either:</h4>
	<li v-click="5">
		Ignores the <span class="color-orange">Signal</span>.
	</li>
	<li v-click="6">
		Executes a user-specified <span class="color-blue">Signal Handler</span>.
	</li>
	<li v-click="7">
		Executes the default <span class="color-pink">Signal Action</span>.
	</li>
	<br>
	<hr v-click="8">
	<div class="grid grid-cols-1 text-sm ml-5">
		<p v-click="8" class="color-yellow">
			( except for <span class="color-red">SIGKILL</span> & <span class="color-red">SIGSTOP</span>, they cannot be handled or ignored 😨 )
		</p>
	</div>
</div>
<br>
<br>

<style>
.note {
	@apply border-2 border-green rounded-3xl w-100 pa-5
}
</style>

<!--
How are signals delivered?

1 : Pending before delivery

2 : 

3 :

## 4 : for most signals

5 :

6 :

7 :

8 :

-->

---
layout: full
transition: slide-up
title: How About SIGUSR1 & SIGUSR2?
---

<br>
<h1>SIGUSR1 & SIGUSR2</h1>

<div v-click="1" class="note">
	<ul class="text-xl">
	  <li v-click="1">
		Can be used to indicate a desired <span class="color-yellow">user-defined condition</span>.
	  </li>
	  <li v-click="2">
		Their default <span class="color-pink">Signal Action</span> is to terminate the process;
	  </li>
	</ul>
</div>

<style>
h1 {
	@apply text-5xl text-center
}
.note {
	@apply border-2 border-green rounded-3xl w-150 pa-5 ml-30 mt-20
}
</style>

<!--
So what is SIGUSR1 & SIGUSR2?

SIGUSR1 & SIGUSR2 can mean anything.

1 : Indicate user-defined condition;

2 : by default they terminate the process;
-->

---
layout: two-cols-header
class: '-top-12'
title: minitalk protocol
---

<h1 class="text-center"><span class="color-green">minitalk</span> Protocol</h1>

<div v-click="1" class="text-center">
	<p class="py-1 text-lg">
		<span class="color-blue">SIGUSR1</span> and <span class="color-blue">SIGUSR2</span> are used to communicate between <span class="color-orange">Server</span> and <span class="color-orange">Client</span>.
	</p>
	<hr>
</div>

::left::

<div v-click="2" class="note">
	<h3 v-click="2">
		For the <span class="color-green">Server</span>:
	</h3>
	<li v-click="3">
		<span class="color-blue">SIGUSR1</span> means 0,
	</li>
	<li v-click="4">
		<span class="color-blue">SIGUSR2</span> means 1.
	</li>
</div>

::right::

<div v-click="5" class="note">
	<h3 v-click="5">
		For the <span class="color-green">Client</span>:
	</h3>
	<li v-click="6">
		<span class="color-blue">SIGUSR1</span> signals that <span class="color-yellow">a bit</span> was successfully received.
	</li>
	<li v-click="7">
		<span class="color-blue">SIGUSR2</span> signals that the <span class="color-red">end of message</span> was received, transmission is over.
	</li>
</div>

<style>
h1 {
	@apply text-5xl text-center
}
.note {
	@apply flex-col border-2 border-green rounded-3xl w-80 pa-5 ml-10
}
</style>

<!--
minitalk protocol consists of two signals 

1 : These signals are interpreted by the **server** and the **client**

## 2 : Server

3 :

4 :

## 5 : Client

6 : bit received

7 : end of message

-->
---
layout: section
class: '-left--5'
title: Implementation
---

# <span class="color-green">3.</span>
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

<h1 style="text-align: center"><span class="color-green">t_protocol</span> Data Type</h1>

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

3 : bits : keeps track of the current byte being received.

will be set either to 32 or 8, if receiving an int or a char respectively.

4 : data : To store all incoming bits.

5 : received : flag indicating if "header" data has been received

6 : msg : To store the message
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

# 0 : sigaction

The subject allows us to use signal and sigaction. 

I chose to use sigaction for portability and flexibility reasons.

# 1 : setting up sigaction

For the sake of being brief I am gonna leave out most of the details about how sigaction works. 

Suffice if to say that it allows us to set up a signal handler.

Its also worth noting that it is the setting of SA_SIGINFO that allows our program to access extended signal related information by setting sa.sa_sigaction to a handler function (with a special prototype that we will see in just a moment)

# 2 : Setting up handling

This function is used to handle SIGUSR1 and SIGUSR2 for both server and client.

sigaction() retruns 0 on success and -1 on error.

A shorthand error handling technique is used here to exit the program in case of an error.


# 3 : Printing PID

Print the PID of the current process to stdout.

# 4 : Entering infinite loop

... more on pause() later ;)

>>> I like keeping to prefix all my custom functions with `ft_`, you know, to keep that "42 State of Code" ;)
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

<br>
<h2 v-click="7" class="text-center">
	Let's take a closer look at how the <span class="color-orange">client</span>'s' <span class="color-green">signal handling</span> is implemented:
</h2>
<div class="pt-5 text-center">
  <span @click="$slidev.nav.next"
		class="px-2 py-1 rounded cursor-pointer"
		hover="bg-white bg-opacity-10"
  >
    <carbon:arrow-right class="inline"/>
  </span>
</div>
<!--
0 : client code overview

1 : Checks if input arguments are valid

2 : Declares and initializes sa

3 : Pretty much the same as in the server, but instead setting its our signal handler;

4 : Prints PID

5 : Sends message to the server

6 : Terminates the program

7 : Let's take a closer look at how the signal handler is implemented
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
Client signal Handling

1 : SIGUSR1

When the client receives a **SIGUSR1** signal, it prints a *****.

2 : SIGUSR2

When the client receives a **SIGUSR2** signal, it prints a success message and exits successfully.

-->

---
layout: default
class: 'pr-50 pl-50'
transition: slide-up
title: Client into ft_send_msg()
---

<h1 style="text-align: center">Sending the Message to the Server</h1>

```c {all|18}
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
0 : Now, back to the client's main function.

1 : Now everything is ready for the client to send the message to the server.

Let's take a look

-->

---
layout: two-cols
class: 'pa-3'
title: ft_send_msg()
---
```c {all|5,9|10-11|12|14-15|18,20|12}
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

* Send message <span class="color-green">length</span> bit-by-bit to the <span class="color-orange">server</span>;

</div>
<div v-click="4">

* Send message <span class="color-blue">char by char</span> to the <span class="color-orange">server</span>;

</div>
<div v-click="5">

* Send <span class="color-gray">NULL Terminator</span>;

</div>
<br>
<hr v-click="6">
<div v-click="6">

<br>
<h2 class="text-center">
	Let's take a closer look at how the <span class="color-green">data is sent</span>:
</h2>
<div class="pt-5 text-center">
  <span @click="$slidev.nav.next"
		class="px-2 py-1 rounded cursor-pointer"
		hover="bg-white bg-opacity-10"
  >
    <carbon:arrow-right class="inline"/>
  </span>
</div>

</div>

<!--
0 : Take the message's length

1 : Print the message's length

2 : Take Message Length

3 : Send Message Length

4 : Send Message char by char

5 : Send NULL Terminator

-->

---
layout: two-cols
class: 'pa-5'
transition: slide-down
title: Client sending Int
---


<h1 style="text-align: center">Sending an Int</h1>


```c {all|4,7|8|7-8,12|5,10|11|12|8-13}
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

<br>
<br>
<div>
	<li v-click="1">Declare & initialize <span class="color-red">bitshift</span> with the size of the <span class="color-green">binary representation of an integer</span>.</li>
	<li v-click="2">Loop while <span class="color-red">bitshift</span> is larger than 0.</li>
	<br>
	<div v-click="3" class="note">
		<p v-click="3" class="text-center"><span class="color-red">bitshift</span> is used to iterate the incoming data from the <span class="color-yellow">Most Significant Bit</span> (MSB) to the <span class="color-yellow">Least Significant Bit</span> (LSB)</p>
	</div>
	<br>
	<li v-click="4">Isolate the current <span class="color-blue">bit</span>.</li>
	<li v-click="5">Send the <span class="color-blue">bit</span> to the server.</li>
	<li v-click="6">Decrement <span class="color-red">bitshift</span>.</li>
	<li v-click="7">Repeat until the LSB <span class="color-blue">bit</span> has been sent.</li>
</div>

<style>
.note {
	@apply flex-col border-2 border-green rounded-3xl w-95 px-2 mx-5
}
</style>

<!--
0 : Let's see how the client handles sending an int to the server

1 : Bitshift

2 : Loop

But how do we use this bitshift device?

3 : MSB & LSB

4 : Get bit

5 : Send bit

6 : Decrement bitshift

7 : Loop till LSB is sent

Effectively moving from left to right through the bits being sent


>>> Now that we've seen how an int let's quickly see how sending a char works
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

<div v-click="1" class="note">

Most of the logic is the same as what can be found in <span class="color-yellow">ft_send_int()</span>.

</div>
<br>
<div v-click="2">

* Except that <span class="color-red">bitshift</span> is initialized with the size of the <span class="color-green">binary representation of a char</span>.

</div>

<div v-click="3">

* Repeats until the LSB <span class="color-blue">bit</span> has been sent.

</div>

<style>
.note {
	@apply flex-col border-2 border-green rounded-3xl w-95 px-5 mx-5
}
</style>

<!--
0 : Sending a char is very similar to sending an int

1 : ...

2 : Loop until every bit is isolated and sent to the server

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
		If <span class="color-red">pause_flag</span> is set to 1, the <span class="color-orange">client</span> pauses waiting for the next signal to arrive;
	</li>
</ul>


<!--
# 0 :  Intro

Now let's get atomic, bit-onic? Hhgg ..

# 1 : If bit = 0

# 2 : Send SIGUSR1

We call kill() in a similar fashion as we called sigaction(), 

We are error handling with a conditional statement;

# 3 : If bit = 1

# 4 : Send SIGUSR2

We do the same function call but calling it with SIGUSR2 instead;

# 5 : Pause Flag

This function is used both in the client and the server.

This flag is set to 1 when used in the client inside **ft_send_int** and **ft_send_char** functions sending bits;

It is set to 0 in the server when acknowledging the receipt of a signal;

>>> **pause()** causes the calling process (or thread) to sleep until a signal is delivered that either terminates the process or causes the invocation of a signal-catching function. (Quote taken straight from the friendly **man**)

The client goes to sleep listening to a signal to catch, in the server this is not necessary.

-->

---
layout: two-cols
class: 'pa-3 -top-5'
transition: slide-left
title: ft_server_sighandler()
---

<br><br>

```c {all|1-2|4-5|7|8|9-10}
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	static t_protocol	server;
	static int			i;

	usleep(PAUSE);
	(void)context;
	if (!server.bits)
		server.data = 0;
	...
}
```
::right::

<h1 style="text-align: center">ft_server_sighandler()</h1>
<br><br>
<ul>
	<li v-click="1">
		Follows a <span class="color-blue">standard prototype</span>;
	</li>
	<li v-click="2">
		<span class="color-yellow">server</span> and <span class="color-yellow">i</span> are <span class="color-pink">static</span>, initialized to <span class="color-red">0</span>;
	</li>
	<li v-click="3">
		Waits for <span class="color-green">PAUSE</span> microseconds;
	</li>
	<li v-click="4">
		We cast <span class="color-purple">context</span> to <span class="color-gray">void *</span> to suppress compiler warnings;
	</li>
	<p v-click="5">
		If <span class="color-purple">server.bits</span> is 0, set/reset <span class="color-purple">server.data</span> to 0;
	</p>
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
<br>
<br>

```c {5-7|11|12}
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	...
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
<br>
<br>
<ul>
	<li>
		First the <span class="color-orange">server</span> expects an <span class="color-green">int</span> as <span class="color-pink">Header Information</span>, the <span class="color-blue">length</span> of the message;
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
	<p v-click="1">
		When data the size of an <span class="color-green">int</span> is received, and the <span class="color-pink">Header Information</span> is yet to be registered:
	</p>
	<li v-click="2">
		Sets header data received <span class="color-yellow">flag</span> to true;
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

3 : Using a ft_putnbr

4 :

5 :
-->

---
layout: two-cols
class: 'pa-3 -top-5'
title: ft_server_sighandler() Data Received
---
<br>

```c {13|9-11,14}
/* Server */
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	...
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

<div style="opacity: 0.5">

* First the server expects an <span class="color-green">int</span> as <span class="color-purple">Header Information</span>, the length of the message;

* Every time a <span class="color-yellow">SIGUSR1</span> or <span class="color-yellow">SIGUSR2</span> is caught, <span class="color-red">server.bits</span> is incremented;

* After all the <span class="color-blue">bits</span> of the <span class="color-green">int</span> have been received, the conditions to trigger <span class="color-yellow">ft_strlen_received()</span> code block are reached;

</div>

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

```c {all|4|6|7|6-7,21}
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
<br>
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
	<p v-click="4" class="note">
		The <span class="color-green">server</span> receives each char of the message until the <span class="color-gray">NULL</span> terminator is received.
	</p>
</ul>

<style>
.note {
	@apply flex-col border-2 border-green rounded-3xl w-95 pa-5 mx-5
}
</style>

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

```c {8|10-13|14|15-16|17|18|19}
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

<br>
<ul>
	<p class="color-green text-xl">
		When the <span class="color-pink">byte</span> received is the <span class="color-gray">NULL</span> terminator:
	</p>
	<br>
	<li v-click="1">
		Prints the <span class="color-blue">message</span> to the console.
	</li>
	<li v-click="2">
		Re-prints the server <span class="color-yellow">pid</span>.
	</li>
	<li v-click="3">
		Frees <span class="color-yellow">server->msg</span> and sets it to <span class="color-gray">NULL</span>.
	</li>
	<li v-click="4">
		<span class="color-purple">Header Information</span> received flag is set to false;
	</li>
	<li v-click="5">
		<span class="color-green">i</span> reset to 0;
	</li>
	<li v-click="6">
		<span class="color-yellow">SIGUSR2</span> is sent to the <span class="color-orange">server</span>, signaling the end of the transmission of data;
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
<br>
<br>

```c {13|14}
static void	ft_server_sighandler(int sig,
								 siginfo_t *info, void *context)
{
	...
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
<br>
<ul style="opacity: 0.5">
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

# <span class="color-green">4.</span>
# Demonstration


<!--
Eye candy baby!
-->

---
layout: fact
transition: slide-right
title: Demonstration
---

<video controls>
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

<h1 style="text-align: center" class="pb-7">References</h1>
<div class="text-center border-4 border-green rounded-3xl w-1/2" style="margin: 0 auto">

[signal(2)](https://man7.org/linux/man-pages/man2/signal.2.html)

[signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)

[sigaction(2)](https://man7.org/linux/man-pages/man2/sigaction.2.html)

[Standard Signals (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Standard-Signals.html)

[Miscellaneous Signals (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Miscellaneous-Signals.html)

[Signaling Another Process (The GNU C Library)](https://www.gnu.org/software/libc/manual/html_node/Signaling-Another-Process.html)

[Understanding minitalk - saeby/lfabbian](https://42-cursus.gitbook.io/guide/rank-02/minitalk/understand-minitalk)

[Sending and Intercepting a Signal in C : Code(quoi)](https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/)

</div>

<!--

-->

---
layout : section
image: /img/tools-man.png
backgroundSize: 85%
class: '-top-8'
transition: slide-left
title : Tools man!
---

<br>
<img
  class="w-200 ma-5 pa-2 opacity-80 rounded-3xl border-4 border-yellow"
  src="/img/tools-man.png"
  alt="42 logo"
/>

<h5 class="absolute bottom-1 right-30 opacity-80">
	<u style="text-decoration: underline wavy green"><span class="color-pink">Vulfmon</span> - James Jamerson Used One Finger</u> 👆
</h5>

<!--

-->

---
layout : full
transition: slide-down
title : Tech Stack
---

<h1 style="text-align: center">Tech Stack</h1>
<br>
<div class="grid grid-cols-3 grid-content-center w-220">
	<div>
		<h3><span class="color-green ma-5">Project Tooling</span></h3>
		<br>
		<p>
			<span class="color-purple">LANG</span>="<span class="color-yellow">C</span>"
		</p>
		<p>
			<span class="color-purple">SCRIPTS</span>="<span class="color-yellow">bash</span>"
		</p>
		<p>
			<span class="color-purple">BUILD</span>="<span class="color-yellow">make</span>"
		</p>
		<p>
			<span class="color-purple">DEBUG</span>="<span class="color-yellow">gdb</span>"
		</p>
		<p>
			<span class="color-purple">MEMCHECK</span>="<span class="color-yellow">valgrind</span>"
		</p>
		<p>
			<span class="color-purple">VERSION_CTL</span>="<span class="color-yellow">git</span>"
		</p>
	</div>
	<div>
		<h3><span class="color-green ma-5">Dev Env</span></h3>
		<br>
		<p>
			<span class="color-purple">SHELL</span>="<span class="color-yellow">zsh</span>"
		</p>
		<p>
			<span class="color-purple">PROMPT</span>="<span class="color-yellow">starship</span>"
		</p>
		<p>
			<span class="color-purple">EDITOR</span>="<span class="color-yellow">neovim</span>"
		</p>
		<p>
			<span class="color-purple">MULTIPLXR</span>="<span class="color-yellow">tmux</span>"
		</p>
		<p>
			<span class="color-purple">TERM</span>="<span class="color-yellow">kitty</span>"
		</p>
		<p>
			<span class="color-purple">WM</span>="<span class="color-yellow">i3wm</span>"
		</p>
	</div>
	<div>
		<h3><span class="color-green ma-5">Presentation</span></h3>
		<br>
		<p>
			<span class="color-purple">TOOL</span>="<span class="color-yellow">slidev</span>"
		</p>
		<p>
			<span class="color-purple">SCREENREC</span>="<span class="color-yellow">simplescreenrecorder</span>"
		</p>
		<p>
			<span class="color-purple">TERMREC</span>="<span class="color-yellow">vhs</span>"
		</p>
		<p>
			<span class="color-purple">CONVERT</span>="<span class="color-yellow">ffmpeg</span>"
		</p>
	</div>
</div>

<style>
h2 {
	font-size: 1;
}
</style>
<!--

-->

---
layout : full
transition: fade
title : Credits
---

<br>
<h1 style="text-align: center">Credits</h1>
<br><br>

<div class="text-center border-4 border-green rounded-3xl w-1/2" style="margin: 0 auto">

[SlidesCarnival](https://www.slidescarnival.com/) for slides inspiration;

<span class="color-green">tchow-so</span> for the incredible intro picture;

</div>

---
layout : end
class: 'height:100%'
title : end
---

<h1 style="text-align: center">This was <span class="color-red">minitalk</span>!</h1>

> by passunca

A minimalistic implementation of a small data exchange program using UNIX signals. 

<br>
<img
  class="absolute -top--90 -left--30 w-40 opacity-50 rounded-3xl"
  src="/img/PZ_DBG.JPG"
  alt="42 logo"
/>
<img
  class="absolute -bottom-5 -right--30 w-50 opacity-80"
  src="/img/42porto.svg"
  alt="42 logo"
/>
<h2 style="text-align: center">Thank you!</h2>
