# `libpanos` #

This is the library providing an interface to the screen and GPIO pins of the Raspberry Pi.

## Address tables ##

`0x2000B880` - Mailbox

|Offset	|Size(bits)	|Name		|Description															|
|:--:	|:--:		|----		|----																	|
|0x00	|32			|READ		|To receive data														|
|0x18	|32			|STATUS		|Bit 31 is clear when ready to write, bit 30 is clear when we can read	|
|0x20	|32			|WRITE		|To send data															|

`0x20200000` - GPIO

|Offset		|Size(bits)	|Name		|Description					|
|:--:		|:--:		|----		|----							|
|0x00		|32			|GPFSEL0	|Function select for pin 0 - 9	|
|0x04		|32			|GPFSEL1	|pin 10 - 19					|
|0x08		|32			|GPFSEL2	|pin 20 - 29					|
|0x0C		|32			|GPFSEL3	|pin 30 - 39					|
|0x10		|32			|GPFSEL4	|pin 40 - 49					|
|0x14		|32			|GPFSEL5	|pin 50 - 53					|
|			|			|			|								|
|0x1C		|32			|GPSET0		|Register to set pin 0 - 31		|
|0x20		|32			|GPSET1		|32 - 53						|
|			|			|			|								|
|0x28		|32			|GPCLR0		|Register to clear pin 0 - 31	|
|0x2C		|32			|GPCLR1		|32 - 53						|