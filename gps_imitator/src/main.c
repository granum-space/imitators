
#include "spi.h"
#include "gps.h"
#include <stdio.h>

int main()
{
	spi_init();
	GPS_Init();

	float * a, *b, *c;
	GPS_Read_Data(a, b, c);
	return 0;
}
