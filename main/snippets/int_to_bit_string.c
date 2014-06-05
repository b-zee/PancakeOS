#include <cstring>

char *int_to_bit_string(unsigned int value) {
	char *string = new char[sizeof(unsigned int) * 8 + 1];
	memset(string, '0', sizeof(unsigned int) * 8 + 1);

	unsigned int index = sizeof(unsigned int) * 8;
	string[index] = '\0';

	do { string[--index] += (value & 1); } while(value >>= 1);

	return string;
}
