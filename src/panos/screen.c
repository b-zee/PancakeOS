#include "screen.h"

#include "error.h"
#include "uart.h"

#define MAIL_ADDRESS        (unsigned int *)0x2000B880
#define MAIL_READ_ADDRESS   MAIL_ADDRESS + 0x00
#define MAIL_STATUS_ADDRESS MAIL_ADDRESS + 0x18
#define MAIL_WRITE_ADDRESS  MAIL_ADDRESS + 0x20

static void panos_mailbox_wait_write();
static void panos_mailbox_wait_read();
static void panos_mailbox_write(uint8_t channel, uint32_t data);
static uint32_t panos_mailbox_read(uint8_t channel);

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

struct MAILBOX {
	volatile uint32_t read;         // 0x00
	volatile uint32_t padding[3];   // 0x04
	volatile uint32_t peak;         // 0x10
	volatile uint32_t sender;       // 0x14
	volatile uint32_t status;	    // 0x18
	volatile uint32_t config;       // 0x1C
	volatile uint32_t write;        // 0x20
};

static struct FRAME_BUFFER  panos_fb __attribute__ ((aligned (16))) = {0};
static struct MAILBOX      *panos_mb                                = (struct MAILBOX*)MAIL_ADDRESS;

int panos_screen_initialize(uint16_t width, uint16_t height, uint8_t depth)
{
	panos_uart_init();

	panos_fb.width          = (uint32_t)width;
	panos_fb.height         = (uint32_t)height;
	panos_fb.virtual_width  = (uint32_t)width;
	panos_fb.virtual_height = (uint32_t)height;
	panos_fb.pitch          = 0;
	panos_fb.depth          = (uint32_t)depth;
	panos_fb.x_offset       = 0;
	panos_fb.y_offset       = 0;
	panos_fb.pointer        = 0;
	panos_fb.size           = 0;

	panos_mailbox_write(0x1, (uint32_t)&panos_fb | 0x40000000);
	//MailboxWrite((uint32_t)&panos_fb | 0x40000000, 0x1);

	uint32_t data = panos_mailbox_read(0x1);
	//uint32_t data = MailboxRead(0x1);

	if (data != 0 || panos_fb.pointer == 0) {
		return PANOS_ERROR;
	}

	//panos_uart_int((int)panos_fb.size, 10);

	return PANOS_SUCCES;
}

uint8_t *panos_screen_framebuffer()
{
	return (uint8_t *)panos_fb.pointer;
}

// Static functions
void panos_mailbox_wait_write()
{
	while ((panos_mb->status & 0x80000000) != 0) {
		// ...
	}
}
void panos_mailbox_wait_read()
{
	while ((panos_mb->status & 0x40000000) != 0) {
		// ...
	}
}

void panos_mailbox_write(uint8_t channel, uint32_t data)
{
	panos_mailbox_wait_write();

	panos_mb->write = data + (uint32_t)channel;
}

uint32_t panos_mailbox_read(uint8_t channel)
{
	uint32_t data;
	do {
		panos_mailbox_wait_read();

		data = panos_mb->read;
	} while ((data & 0x0000000F) != (uint32_t)channel);

	return data & 0xFFFFFFF0;
}
