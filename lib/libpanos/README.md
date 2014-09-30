# `libpanos` #

This is the library providing an interface to the screen and GPIO pins of the Raspberry Pi.

## Address tables ##

`0x2000B880` - Mailbox

|Offset	|Name		|
|----	|----		|
|0x00	|READ		|
|0x18	|STATUS		|
|0x20	|WRITE		|

`0x20200000` - GPIO

|Offset		|Name		|
|----		|----		|
|0x00		|GPFSEL0	|
|0x04		|GPFSEL1	|
|0x08		|GPFSEL2	|
|0x0C		|GPFSEL3	|
|0x10		|GPFSEL4	|
|0x14		|GPFSEL5	|
|			|			|
|0x1C		|GPSET0		|
|0x20		|GPSET1		|
|			|			|
|0x28		|GPCLR0		|
|0x2C		|GPCLR1		|