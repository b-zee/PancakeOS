extern int __bss_start;
extern int __bss_end;

extern int main();

void _rpi_startup()
{

	int *bss = &__bss_start;
	int *bss_end = &__bss_end;

	while ( bss < bss_end ) {
		*bss++ = 0;
	}

	(void)main();

	while(1);

}
