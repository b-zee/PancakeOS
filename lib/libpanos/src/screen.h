#include <stdint.h>

void panos_screen();
void panos_mailbox_write_wait();
void panos_mailbox_read_wait();
void panos_mailbox_write(uint32_t data, uint8_t channel);
uint32_t panos_mailbox_read(uint8_t channel);
