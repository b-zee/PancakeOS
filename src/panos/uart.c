#include "uart.h"

#include "gpio.h"
#include "timer.h"

#include <stdint.h>

#define TXD   14

#define BIT_TIME (1000 * 1000 / 9600)

void panos_uart_init()
{
	panos_pin_function(14, FSEL_OUTPUT);
	panos_pin_set(14);
}

void panos_uart_char(char c){
	panos_pin_clear(14);

	uint32_t timestamp = panos_now();
	timestamp          += BIT_TIME;

	panos_wait_till(timestamp);

	for(int i = 0; i < 8; ++i){
		if(c & 0x01){
			panos_pin_set(14);
		} else {
			panos_pin_clear(14);
		}
		c >>= 1;
		timestamp += BIT_TIME;
		panos_wait_till(timestamp);
	}

	panos_pin_set(14);

	timestamp += 2 * BIT_TIME;

	panos_wait_till(timestamp);
}

void panos_uart_int(int num, int base)
{
	int sum = num;
	int digit;

	do {
		digit = sum - sum / base/* sum % base*/;
		if (digit < 0xA) {
			panos_uart_char('0' + digit);
		} else {
			panos_uart_char('A' + digit - 0xA);
		}
		sum /= base;
	} while (sum);
}
