#include <stdint.h>
#include "panos/gpio.h"
#include "panos/timer.h"
#include "panos/screen.h"

#define SCREEN_WIDTH  1680
#define SCREEN_HEIGHT 1050

int main(void)
{
	int ret_val = panos_screen_initialize(SCREEN_WIDTH, SCREEN_HEIGHT, 24);

	uint32_t interval;
	if (ret_val == 0) { // Success
		interval = 100000;

		uint32_t stride = SCREEN_WIDTH * 3;

		uint8_t *buffer = panos_screen_framebuffer();
		for (uint32_t y = 0; y < SCREEN_HEIGHT; ++y) {
			
			for (uint32_t x = 0; x < SCREEN_WIDTH; ++x) {
				buffer[y * stride + x * 3 + 0] = 255;
				buffer[y * stride + x * 3 + 1] = x % 256;
				buffer[y * stride + x * 3 + 2] = y % 256;
			}
		}

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
