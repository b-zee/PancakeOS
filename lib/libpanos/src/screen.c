#include "screen.h"
#include "error.h"

//void panos_mailbox_write_wait();
//void panos_mailbox_read_wait();
void panos_mailbox_write(uint32_t data, uint8_t channel);
uint32_t panos_mailbox_read(uint8_t channel);

#define MAIL_ADDRESS		(unsigned int *)0x2000B880
#define MAIL_READ_ADDRESS	MAIL_ADDRESS + 0x00
#define MAIL_STATUS_ADDRESS	MAIL_ADDRESS + 0x18
#define MAIL_WRITE_ADDRESS	MAIL_ADDRESS + 0x20

struct FRAME_BUFFER {
    volatile uint32_t width;
    volatile uint32_t height;
    volatile uint32_t virtual_width;
    volatile uint32_t virtual_height;
    volatile uint32_t pitch;
    volatile uint32_t depth;
    volatile uint32_t x_offset;
    volatile uint32_t y_offset;
    volatile uint32_t pointer;
    volatile uint32_t size;
};

static struct FRAME_BUFFER panos_fb __attribute__ ((aligned (16))) = {0};

int panos_screen_initialize(uint16_t width, uint16_t height, uint8_t depth)
{
	panos_fb.width			= (uint32_t)width;
	panos_fb.height			= (uint32_t)height;
	panos_fb.virtual_width	= (uint32_t)width;
	panos_fb.virtual_height	= (uint32_t)height;
    panos_fb.pitch			= 0;
	panos_fb.depth			= (uint32_t)depth;
    panos_fb.x_offset		= 0;
    panos_fb.y_offset		= 0;
    panos_fb.pointer		= 0;
    panos_fb.size			= 0;

	panos_mailbox_write((uint32_t)&panos_fb | 0x40000000, 0x1);

	uint32_t data = panos_mailbox_read(0x1);

	if (data != 0 || panos_fb.pointer == 0) {
		return PANOS_ERROR;
	}

	return PANOS_SUCCES;
}

// Static functions
/*void panos_mailbox_write_wait()
{
	// Loop while MAIL_FULL
	while ((*(MAIL_STATUS_ADDRESS) & 0x80000000) != 0);
}
void panos_mailbox_read_wait()
{
	// Loop while MAIL_EMPTY
	while ((*(MAIL_STATUS_ADDRESS) & 0x40000000) != 0);
}

void panos_mailbox_write(uint8_t channel, uint32_t data)
{
	panos_mailbox_write_wait();

	*(MAIL_WRITE_ADDRESS) = (uint32_t)channel | data;
}

void panos_mailbox_read(uint8_t channel, uint32_t *data)
{
	do {
		panos_mailbox_read_wait();

		*data = *(MAIL_READ_ADDRESS);
	} while (((*data) & 0x0000000F) != (uint32_t)channel);

	*data &= 0xFFFFFFF0;
}*/
