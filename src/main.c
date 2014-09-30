#include <stdint.h>
#include "../lib/libpanos/src/gpio.h"
#include "../lib/libpanos/src/timer.h"
#include "../lib/libpanos/src/screen.h"

int main()
{
	panos_screen();

	// Set the function of pin 16 on 001, which means it's an output.
	panos_set_pin_output(16);
	// Set pin 16.
	panos_pin_set(16);

	// Endless loop to blink the led.
	while (1) {
		panos_pin_set(16);

		panos_wait_us(500000);

		panos_pin_clear(16);

		panos_wait_us(500000);
	}

	return 0;
}
