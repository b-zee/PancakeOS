#include "gpio.h"

// Base address of GPIO registers
#define GPIO_ADDRESS	(unsigned int *)0x20200000

/**
 * Registers to define the operation of the GPIO pins.
 * 3 bits per pin to define the operation. When the 3 bits
 * are 000, the pin is an input, when 001 an output.
 * GPFSEL0: pin 0 - 9
 * GPFSEL1: pin 10 - 19
 * GPFSEL2: pin 20 - 29
 * GPFSEL3: pin 30 - 39
 * GPFSEL4: pin 40 - 49
 * GPFSEL5: pin 50 - 53
 */
#define GPFSEL_ADDRESS	GPIO_ADDRESS + 0

/**
 * Registers with which you can set pins with.
 * When you set a 1 on the bit, the pin will be set.
 * Zeros are ignored, for clearing you need to use
 * the GPCLR registers.
 * GPSET0: pin 0 - 31
 * GPSET1: pin 32 - 53
 */
#define GPSET_ADDRESS	GPFSEL_ADDRESS + 7

/**
 * These registers do the opposite of GPSET registers.
 * They clear the pins.
 * GPCLR0: pin 0 - 31
 * GPCLR1: pin 32 - 53
 */
#define GPCLR_ADDRESS	GPFSEL_ADDRESS + 10

void panos_pin_function(uint8_t pin, uint8_t function)
{
	// Clear the function bits, then overwrite function
	*(GPFSEL_ADDRESS + (pin / 10)) &= (0x7 << ((pin % 10) * 3));
	*(GPFSEL_ADDRESS + (pin / 10)) |= (function << ((pin % 10) * 3));
}

void panos_pin_set(uint8_t pin)
{
	*(GPSET_ADDRESS + (pin / 32)) = (1 << (pin % 32));
}

void panos_pin_clear(uint8_t pin)
{
	*(GPCLR_ADDRESS + (pin / 32)) = (1 << (pin % 32));
}

