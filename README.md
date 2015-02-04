# PancakeOS #

## Brief description ##

PancakeOS is an operating system that aims to provide a basic environment to communicate with components in the [Raspberry Pi](http://www.raspberrypi.org) like the screen and GPIO pins.


## Structure ##

`src/` contains the basic startup code to launch a `main` function in `main.c`. This `main` is similar to any entry point in C. `main.c` is able to invoke functions of libraries that are made to communicate with the GPIO pins and screen.
