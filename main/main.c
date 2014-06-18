#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>	// int32_t

#define BYTES_PER_ROW 4

char *byte_to_binary(const unsigned char byte)
{
	static char bits[9] = {'\0'};

	for (int i = 0; i < 8; ++i) {
		bits[i] = ((byte >> i) & 1) + '0';
	}

	return bits;
}

void bin_dump(const void *addr, size_t bytes)
{
	
	// The buffer containing BYTES_PER_ROW chars per line
	char buffer[BYTES_PER_ROW + 1];
	const unsigned char *const ptr = addr;

	// Loop untill we passed all bytes we wanted to print.
	for (size_t i = 0; i < bytes;) {

		printf("0x%08X  ", ptr + i);

		// Loop over a maximum of BYTES_PER_ROW bytes. Save char byte in buffer and print byte in hex.
		size_t index;
		for (index = 0; index < BYTES_PER_ROW && i < bytes; ++i, ++index) {

			buffer[index] = (ptr[i] < 0x20 || ptr[i] > 0x7E) ? '.' : ptr[i];

			printf("%s ", byte_to_binary(*ptr + i));

		}

		buffer[index] = '\0';

		// Add some padding to align every row even when not BYTES_PER_ROW bytes have been printed.
		while (index++ < BYTES_PER_ROW) {
			printf("         ", buffer);
		}

		printf(" %s\n", buffer);

	}

}

void hex_dump(const void *addr, size_t bytes)
{

	// The buffer containing a char representation
	char buffer[BYTES_PER_ROW + 1];
	const unsigned char *const ptr = (unsigned char *)addr;

	// Loop untill we passed all bytes we wanted to print.
	size_t i = 0;
	while (i < bytes) {

		printf("0x%08X  ", ptr + i);

		// Loop over a maximum of BYTES_PER_ROW bytes. Save char byte in buffer and print byte in hex.
		size_t index;
		for (index = 0; index < BYTES_PER_ROW && i < bytes; ++i, ++index) {

			buffer[index] = (ptr[i] < 0x20 || ptr[i] > 0x7E) ? '.' : ptr[i];

			printf("%02X ", (int)ptr[i]);

		}

		buffer[index] = '\0';

		// Add some padding to align every row even when not BYTES_PER_ROW bytes have been printed.
		while (index++ < BYTES_PER_ROW) {
			printf("   ", buffer);
		}

		printf(" %s\n", buffer);

	}

}

int main(/*int argc, char **argv*/)
{

	union pixel
	{
		struct rgba
		{
			unsigned char a,b,g,r;
		} c;
		uint32_t rgba;
	};

	union pixel *myPixel = malloc(sizeof(*myPixel));

	myPixel->c.r = 0x01;
	myPixel->c.g = 0x02;
	myPixel->c.b = 0x04;
	myPixel->c.a = 0x08;

	myPixel->rgba = 0x01020408;

	bin_dump(myPixel, sizeof(*myPixel));
	hex_dump(myPixel, sizeof(*myPixel));

	printf("%d\n", myPixel->c.r);

	return 0;

}
