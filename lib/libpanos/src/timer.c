#include "timer.h"

#define SYSTIMER_ADDRESS    (unsigned int *)0x20003000

struct SYS_TIMER {
	volatile uint32_t CS;
	volatile uint32_t CLO;
	volatile uint32_t CHI;
	volatile uint32_t C0;
	volatile uint32_t C1;
	volatile uint32_t C2;
	volatile uint32_t C3;
};

void panos_wait_us(uint32_t us)
{
	struct SYS_TIMER* system_timer = (struct SYS_TIMER*)SYSTIMER_ADDRESS;

	volatile uint32_t current_time = system_timer->CLO;

	while (system_timer->CLO - current_time < us);
}
