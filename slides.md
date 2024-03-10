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
  class="absolute -bottom-20 -right-1 w-50 opacity-80"
  src="/img/42porto.svg"
  alt="42 logo"
/>

<!--
Project headline
-->

---
layout: two-cols
class: '-top--15 -left--5'
title: Hello whirl
---

# Hello Whirl!
## I am Pedro Ribeiro

42 Student
___

> Rank : 2
>
> Grade : Learner
___

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
title: Server Features
---

# Server Features

<v-clicks>

- When executed, prints its **pid**;

- Listens for incoming **SIGUSR1** & **SIGUSR2** signals;

- Receives a **message** bit-by-bit:

- **Acknowledges** reception **by sending a signal** back to the client;

- Prints the **message** once it has been fully received;

- Handles multiple clients `in a row`.

</v-clicks>

<!--
Let's chat about Server side Features!
-->

---
layout: full
title: Client Features
---

# Client Features

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
title: UNIX Signals
---

<h1 style="text-align: center">But what is a Signal?</h1>

<v-clicks>

* A Signal is a reporter of **events**;


When a process receives a Signal:

* It is interrupted;

* A default **Signal Action** is triggered;

Signals are useful tools for **Interprocess Communication** (IPC).

</v-clicks>

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
title: Events generate Signals
---

<h2 style="text-align: center">Events generate Signals</h2>

<br><br>

<div class="grid grid-cols-3 gap-4">
  <div v-click>
    <h3>Error Events</h3>
	<p>The program did an invalid operation and cannot continue execution.</p>
	<p>Not All errors generate signals!</p>
  </div>
  <div v-click>
    <h3>External Events</h3>
    <p>Generally related to I/O or other processes.</p>
	<p><bold>Includes</bold>:</p>
	<ul>
		<li>Arrival of input.</li>
		<li>Expiration of timer.</li>
		<li>Termination of a child process.</li>
	</ul>
  </div> 
  <div v-click>
	<h3>Explicit Events</h3>
	<p>Means the use of a library function like kill() whose purpose is to generate a signal</p>
  </div>
</div>

<!--
There are 3 kinds of signal generating events
-->

---
layout: two-cols
title: Synchronous & Asynchronous Signals
---

<h1 style="text-align: center">Synchronous Signals</h1>

<br>

<v-clicks>

* Relate to a specific event and are delivered during that event (unless blocked).

* Most **Errors** and **Explicit Requests** generate **Synchronous Signals**.

</v-clicks>

<v-after>

<br>

Note:
> Certain hardware errors are not 100% synchronous arriving a couple of instructions later.

</v-after>

::right::

<h1 style="text-align: center">Asynchronous Signals</h1>

<br>
	
<v-clicks>

* Generated by events outside the control of the receiving process.

* Their arrival is unpredictable.

</v-clicks>

<br>

<v-click>

**External Events** and **Explicit Requests** applying to some other process generate **Asynchronous Signals**.

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

* However, if that signal type is being blocked, it may remain pending indefinitely.

> When that signal type is unblocked it will be delivered immediately.

</v-click>

<br>

<v-click>

When a signal is delivered, the specified **Signal Action** is taken;

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

> (except for **SIGKILL** & **SIGSTOP**) 

</v-click>

<!--

-->

---
layout: full
title: How About SIGUSR1 & SIGUSR2?
---

<h1 style="text-align: center">SIGUSR1 & SIGUSR2</h1>

How About SIGUSR1 & SIGUSR2?

<!--

-->
