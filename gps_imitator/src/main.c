
#include "spi.h"
#include "gps.h"
#include <stdio.h>

int main()
{
	spi_init();
	GPS_Init();
	GPS_update(65535);
	return 0;
}
