/*
 * gps.c
 *
 *  Created on: 23 мая 2016 г.
 *      Author: developer
 */

#include "spi.h"
#include <stdio.h>

void GPS_Init()
{

}

uint8_t GPS_Read_Data(float * latitude, float * longitude, float * height)
{
	char symbol;
	while(1)
	{
		symbol = (char)spi_sendbyte(255);
		printf("symbol=%c (%x)\n", symbol, (unsigned char)symbol);
	}
	return 0;
}

