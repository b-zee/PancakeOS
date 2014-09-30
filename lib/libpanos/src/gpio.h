#ifndef PANOS_GPIO_H
#define PANOS_GPIO_H

/**
 * @author		Benno Zeeman
 * @brief		Functions to control GPIO pins
 * @copyright	The MIT License (MIT)
 * @date		2014
 * @version		1.0
 * @todo
 * 		Function to get value of pin
 * 
 * These functions are used to set the function of
 * pins. And to set and clear output pins.
 */

#include <stdint.h>

#define FSEL_INPUT	0x0	// 000
#define FSEL_OUTPUT	0x1	// 001
#define FSEL_ALT0	0x4	// 100
#define FSEL_ALT1	0x5	// 101
#define FSEL_ALT2	0x6	// 110
#define FSEL_ALT3	0x7	// 111
#define FSEL_ALT4	0x3	// 011
#define FSEL_ALT5	0x2	// 010

void panos_pin_function(uint8_t pin, uint8_t function);
void panos_pin_set(uint8_t pin);
void panos_pin_clear(uint8_t pin);

#endif
