# PancakeOS

## Brief description

PancakeOS is an operating system that aims to provide a basic environment to communicate with components in the Raspberry Pi like the screen and GPIO pins.


## Structure

`src/` contains the basic startup code to launch a `main` function in `main.c`. This `main` is similar to any entry point in C. `main.c` is able to invoke functions of libraries that are made to communicate with the GPIO pins and screen.

### Libraries

The most important library that plays a key role in this project is `libpanos`. This library provides an interface to the screen, GPIO pins, and possibly more.

A library that's also available, but not needed at the moment, is the `libc`. It should be updated when the project progresses and more and more system calls are made available. I.e. `memset`, `strlen`, etc.