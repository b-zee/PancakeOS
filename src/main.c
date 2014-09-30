#include <stdint.h>
#include "../lib/libpanos/src/gpio.h"
#include "../lib/libpanos/src/timer.h"
#include "../lib/libpanos/src/screen.h"

int main()
{
	int ret_val;
	ret_val = panos_screen_initialize(640, 480, 24);

	uint32_t interval;
	if (ret_val == 0) { // Success
		interval = 100000;
	} else {            // Failure
		interval = 1000000;
	}

	panos_pin_function(16, FSEL_OUTPUT);
	panos_pin_set(16);

	while (1) {
		panos_pin_set(16);

		panos_wait_us(interval);

		panos_pin_clear(16);

		panos_wait_us(interval);
	}

	return 0;
}
