# `libpanos` #

This is the library providing an interface to the screen and GPIO pins of the Raspberry Pi.

## Address tables ##
**Mailbox**
`0x2000B880`
| Offset | Name   |
| ------ | ------ |
| 0x00   | READ   |
| 0x10   | PEAK   |
| 0x14   | SENDER |
| 0x18   | STATUS |
| 0x1C   | CONFIG |
| 0x20   | WRITE  |