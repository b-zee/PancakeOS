#include "screen.h"

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

static struct FRAME_BUFFER panos_fb __attribute__ ((aligned (16))) = {0};

void panos_screen()
{
	panos_fb.width			= 640;
	panos_fb.height			= 480;
	panos_fb.virtual_width	= 640;
	panos_fb.virtual_height	= 480;
    panos_fb.pitch			= 0;
	panos_fb.depth			= 16;
    panos_fb.x_offset		= 0;
    panos_fb.y_offset		= 0;
    panos_fb.pointer		= 0;
    panos_fb.size			= 0;


	do {
		panos_mailbox_write((uint32_t)&panos_fb, 0x1);
	} while (panos_mailbox_read(0x1) != 0);

	while (panos_fb.pointer == 0);

}
/*void panos_mailbox_write_wait()
{
	// Loop while MAIL_FULL
	while ((*(MAIL_STATUS_ADDRESS) & 0x80000000) != 0);
}
void panos_mailbox_read_wait()
{
	// Loop while MAIL_EMPTY
	while ((*(MAIL_STATUS_ADDRESS) & 0x40000000) != 0);
}*/

/*void panos_mailbox_write(uint8_t channel, uint32_t data)
{
	panos_mailbox_write_wait();

	*(MAIL_WRITE_ADDRESS)	= data | (uint32_t)channel;
}
uint32_t panos_mailbox_read(uint8_t channel)
{
	uint32_t frame;
	do {
		panos_mailbox_read_wait();

		frame = *(MAIL_READ_ADDRESS);
	} while ((frame & 0x0000000F) != (uint32_t)channel);

	return frame & 0xFFFFFFF0;
}*/
