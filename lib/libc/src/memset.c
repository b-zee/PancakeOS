#include <string.h>

void *memset(void *dst, int c, size_t n)
{

	unsigned char *ptr = dst;

	while(n--) {
		*ptr++ = (unsigned char)c;
	}

	return dst;

}
