#include "screen.h"

static void panos_mailbox_write_wait();
static void panos_mailbox_read_wait();
static void panos_mailbox_write(uint8_t channel, uint32_t data);
static void panos_mailbox_read(uint8_t channel, uint32_t *data);

#include "error.h"

#define MAILBOX_ADDRESS		(unsigned int *)0x2000B880

#define MAIL_READ_ADDRESS	MAILBOX_ADDRESS + 0x00
#define MAIL_STATUS_ADDRESS	MAILBOX_ADDRESS + 0x18
#define MAIL_WRITE_ADDRESS	MAILBOX_ADDRESS + 0x20

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

int panos_screen_initialize(uint16_t width, uint16_t height, uint8_t depth)
{
	static struct FRAME_BUFFER panos_fb __attribute__ ((aligned (16))) = {0};

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

	panos_mailbox_write(0x1, (uint32_t)&panos_fb);

	uint32_t data;
	panos_mailbox_read(0x1, &data);

	if (data != 0) {
		return PANOS_ERROR;
	}

	return PANOS_SUCCES;
}

// Static functions
void panos_mailbox_write_wait()
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
	} while ((*data & 0x0000000F) != (uint32_t)channel);

	*data &= 0xFFFFFFF0;
}
