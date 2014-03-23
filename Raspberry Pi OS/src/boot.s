.section .init
.globl _start
_start:
	ldr     sp, =(128 * (1024 * 1024))
	sub     sp, sp, #0x4

	b       _rpi_startup
