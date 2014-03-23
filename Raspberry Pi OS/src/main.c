#define GPIO_GPFSEL1    1
#define GPIO_GPSET0     7
#define GPIO_GPCLR0     10

int main()
{
	volatile unsigned int* gpio = (unsigned int*)0x20200000;

	unsigned int counter;

	gpio[GPIO_GPFSEL1] |= (1 << 18);
	gpio[GPIO_GPSET0] = (1 << 16);


	gpio[GPIO_GPFSEL1] |= (1 << 18);

	while(1) {

		gpio[GPIO_GPSET0] = (1 << 16);

		for(counter = 0; counter < 500000; counter++);

		gpio[GPIO_GPCLR0] = (1 << 16);

		for(counter = 0; counter < 500000; counter++);

	}

	return 0;
}
