# `libpanos` #

This is the library providing an interface to the screen and GPIO pins of the Raspberry Pi.

## Address tables ##

`0x2000B880` - Mailbox

|Offset	|Name		|Description															|
|----	|----		|----																	|
|0x00	|READ		|To receive data														|
|0x18	|STATUS		|Bit 31 is clear when ready to write, bit 30 is clear when we can read	|
|0x20	|WRITE		|To send data															|

`0x20200000` - GPIO

|Offset		|Name		|Description					|
|----		|----		|----							|
|0x00		|GPFSEL0	|Function select for pin 0 - 9	|
|0x04		|GPFSEL1	|pin 10 - 19					|
|0x08		|GPFSEL2	|pin 20 - 29					|
|0x0C		|GPFSEL3	|pin 30 - 39					|
|0x10		|GPFSEL4	|pin 40 - 49					|
|0x14		|GPFSEL5	|pin 50 - 53					|
|			|			|								|
|0x1C		|GPSET0		|Register to set pin 0 - 31		|
|0x20		|GPSET1		|32 - 53						|
|			|			|								|
|0x28		|GPCLR0		|Register to clear pin 0 - 31	|
|0x2C		|GPCLR1		|32 - 53						|