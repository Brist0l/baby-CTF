# Baby-CTF: Escape the Machine

A broken system begging for your help. Help it, or maybe not? That's upto you.
But beware, to help it you would need to endure extreme frustration.

* You don’t get source code.
* You don’t get documentation.
* You don’t get hand-holding.
* You don't get sanity.

What you get is,

* A system.
* A small one.
* A very flawed one.

and yes,
* A very breakable one.

![preview](https://github.com/Brist0l/baby-CTF/blob/main/imgs/1.png)

---

## Challenges

### 🧩 baby_1

The entry point.

This is where you:
- understand how the system behaves
- observe memory and execution
- and eventually… break it

Everything is visible.
Nothing is hidden.

If you still can’t break it… that’s on you.

---

### 🧩 baby_2

Now things get a bit more… interesting.

You’re no longer just poking memory.
You need to actually understand:
- how execution flows
- how instructions behave
- and how small changes affect the whole system

It’s still the same machine.
But now it won’t fall apart that easily.

---


## Build Your Own CTF

This is not just a challenge.

Underneath all of this is a **custom-built machine**:
- byte-addressable memory
- registers
- instruction pointer
- stack + control flow
- a minimal instruction set


This CTF isn’t just a one-off challenge. It runs on a small custom machine I built with its own memory, registers, instruction pointer, and a minimal ISA. The system is initialized using `initsys(System *s)` and the entire challenge is defined by writing instructions directly into memory. The ISA includes basic control flow (`JMP`, `CALL`, `RET`), data movement (`MOV`), comparison (`CMP`), input handling (`GETINP`), and flag checking (`GETFLG`). You can tweak the memory layout, change instructions, or build completely new challenges on top of the same system.


Everything you interact with is part of that system.

You can:
- modify the machine
- change instructions
- design your own challenges
- break your own rules

---
## Objective

Your goal is simple (not easy):

* Retrieve the flag

---

## ⚠️ Important

* Try not looking at the source code for maximum challenge and fun
* Everything you need is inside the system itself

![roast](https://github.com/Brist0l/baby-CTF/blob/main/imgs/2.png)

---

## Running the Challenge

Run directly:
```
./baby_1
```
```
./baby_2
```

or compile using make:


``` make baby1```
```make baby2```


and then run them.



## Flag Format


braun{...}
