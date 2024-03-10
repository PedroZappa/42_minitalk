---
theme: dracula
font:
sans: Fira Code
mono: Fira Code
serif: Fira Code
class: 'text-center'
# https://sli.dev/custom/highlighters.html
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
The last comment block of each slide will be treated as slide notes. It will be visible and editable in Presenter Mode along with the slide. [Read more in the docs](https://sli.dev/guide/syntax.html#notes)
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
layout: cover
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

* When executed, prints its **pid**;

* Listens for incoming **SIGUSR1** & **SIGUSR2** signals;

* Receives a **message** bit-by-bit:

* **Acknowledges** reception **by sending a signal** back to the client;

* Prints the **message** once it has been fully received;

* Handles multiple clients `in a row`.

<!--
Let's chat about Server side Features!
-->

---
layout: full
title: Client Features
---

# Client Features

* Takes two command-line arguments:
	* **pid** of the server;
	* **message** to be sent;

* Sends the **message** bit-by-bit to the server;
	* Communicates using only **SIGUSR1** & **SIGUSR2** signals;

<!--
Let's chat about client side Features!
-->

---
layout: cover
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

# Server-Client Diagram

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
layout: cover
class: '-left--5'
title: Client-Server Communication
---

# 3. 
# UNIX Signals

<!--
Them UNIX Sigals man!
-->

