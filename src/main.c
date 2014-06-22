#define GPIO_ADDRESS	(unsigned int *)0x20200000

/**
 * Registers to define the operation of the GPIO pins.
 * 3 bits per pin to define the operation. When the 3 bits
 * are 000, the pin is an input, when 001 an output.
 */
#define GPIO_GPFSEL0 	0	// GPIO pin 0 - 9
#define GPIO_GPFSEL1	1	// GPIO pin 10 - 19
#define GPIO_GPFSEL2	2	// GPIO pin 20 - 29
#define GPIO_GPFSEL3	3	// GPIO pin 30 - 39
#define GPIO_GPFSEL4	4	// GPIO pin 40 - 49
#define GPIO_GPFSEL5	5	// GPIO pin 50 - 53

/**
 * Registers with which you can set pins with.
 * When you set a 1 on the bit, the pin will be set.
 * Zeros are ignored, for clearing you need to use
 * the GPCLR registers.
 */
#define GPIO_GPSET0		7	// GPIO pin 0 - 31
#define GPIO_GPSET1		8	// GPIO pin 32 - 53

/**
 * These registers do the opposite of GPSET registers.
 * They clear the pins.
 */
#define GPIO_GPCLR0		10
#define GPIO_GPCLR1		11

int main()
{

	// Variable to approach registers more easily.
	unsigned int *gpio = GPIO_ADDRESS;

	// Set the function of pin 16 on 001, which means it's an output.
	gpio[GPIO_GPFSEL1] |= (1 << 18);
	// Set pin 16.
	gpio[GPIO_GPSET0] = (1 << 16);

	// A counter to lose some time. Volatile because we don't want
	// the compiler to optimise it (remove it).
	volatile unsigned int counter;

	// Endless loop to blink the led.
	while (1) {

		gpio[GPIO_GPSET0] = (1 << 16);

		for(counter = 0; counter < 500000; counter++);

		gpio[GPIO_GPCLR0] = (1 << 16);

		for(counter = 0; counter < 500000; counter++);

	}

	return 0;

}
