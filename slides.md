---
# try also 'default' to start simple
theme: dracula
# random image from a curated Unsplash collection by Anthony
# like them? see https://unsplash.com/collections/94734566/slidev
# background: https://cover.sli.dev
# apply any unocss classes to the current slide
class: 'text-center'
# https://sli.dev/custom/highlighters.html
highlighter: shiki
# some information about the slides, markdown enabled
info: |
  ## minitalk
  A minimalistic implementation of a small data exchange program using UNIX signals. 

  Learn more at [PedroZappa : minitalk](https://github.com/PedroZappa/42_minitalk)
transition: slide-left
title: minitalk
mdc: true
---

# minitalk

A minimalistic implementation of a small data exchange program using UNIX signals 

<div class="pt-12">
  <span @click="$slidev.nav.next" class="px-2 py-1 rounded cursor-pointer" hover="bg-white bg-opacity-10">
    Press Space for next page <carbon:arrow-right class="inline"/>
  </span>
</div>

<img
  class="absolute -top-35 -right-1 w-80 opacity-80"
  src="/img/42porto.svg"
  alt=""
/>

<!--
The last comment block of each slide will be treated as slide notes. It will be visible and editable in Presenter Mode along with the slide. [Read more in the docs](https://sli.dev/guide/syntax.html#notes)
-->

