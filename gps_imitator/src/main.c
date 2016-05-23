
#include "spi.h"
#include <stdio.h>

int main()
{
	spi_init();

	while(1)
	{
		uint8_t symbol = spi_sendbyte(0xFF);
		if (symbol != 0xFF)
		{
			printf("%c", *((char*)&symbol));
			fflush(stdout);
		}
	}
	return 0;
}
