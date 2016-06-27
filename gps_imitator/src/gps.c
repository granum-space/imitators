/*
 * gps.c
 *
 *  Created on: 23 мая 2016 г.
 *      Author: developer
 */

#include "spi.h"
#include <stdio.h>

enum {
	SEARCHING,
	WAITING_GP,
	WAITING_MES_T,
	COLLECTING_GGA,
	COLLECTING_GLL,
	COLLECTING_RMC

} gps_status;

char gps_buffer[100];
uint8_t gps_index = 0;

float latitude = 0.0f, longtitude = 0.0f, height = 0.0f;
enum {
	N = 0,
	S = 1
}lat_side;
enum {
	E = 0,
	W = 1
}long_side;

void GPS_Init()
{
	spi_init();
	gps_status = SEARCHING;
}

void parse_GGA();
void parse_GLL();
void parse_RMC();

uint8_t GPS_update(int cycles)
{
	char symbol;
	int i=0;
	for(i = 0;i<cycles;i++)
	{
		symbol = (char)spi_sendbyte(0xFF);
		//printf("symbol=%c (%x)\n", symbol, (unsigned char)symbol);
		switch(gps_status){
		case SEARCHING:
			if(symbol == '$') {
				gps_buffer[gps_index] = symbol;
				gps_index++;
				gps_status = WAITING_GP;
			}
			break;
		case WAITING_GP:
			gps_buffer[gps_index] = symbol;
			gps_index++;
			if(gps_index==3) {
				if(gps_buffer[1] == 'G') {
					if(gps_buffer[2] == 'P') {
						gps_status = WAITING_MES_T;
					}
					else {
						gps_status = SEARCHING;
						gps_index = 0;
					}
				}
				else {
					gps_status = SEARCHING;
					gps_index = 0;
				}
			}
			break;
		case WAITING_MES_T:
			gps_buffer[gps_index] = symbol;
			gps_index++;
			if(gps_index==6) {
				if(gps_buffer[3] == 'G') {
					if(gps_buffer[4] == 'G') {
						if(gps_buffer[5] == 'A') {
							printf("GGA found\n");
							gps_status = COLLECTING_GGA;
						}
						else {
							gps_status = SEARCHING;
							gps_index = 0;
						}
					}
					else {
						if(gps_buffer[4] == 'L') {
							if(gps_buffer[5] == 'L') {
								printf("GLL found\n");
								gps_status = COLLECTING_GLL;
							}
							else {
								gps_status = SEARCHING;
								gps_index = 0;
							}
						}
						else {
							gps_status = SEARCHING;
							gps_index = 0;
						}
					}
				}
				else {
					if(gps_buffer[3] == 'R') {
						if(gps_buffer[4] == 'M') {
							if(gps_buffer[5] == 'C') {
								printf("RMC found\n");
								gps_status = COLLECTING_RMC;
							}
							else {
								gps_status = SEARCHING;
								gps_index = 0;
							}
						}
						else {
							gps_status = SEARCHING;
							gps_index = 0;
						}
					}
					else {
						gps_status = SEARCHING;
						gps_index = 0;
					}
				}
			}
			break;
		case COLLECTING_GGA:
			if(symbol == '\n') {
				printf("End of GGA packet.\n");
				void parse_GGA();
				gps_index = 0;
				gps_status = SEARCHING;
			}
			break;
		case COLLECTING_GLL:
			if(symbol == '\n') {
				printf("End of GLL packet.\n");
				void parse_Gll();
				gps_index = 0;
				gps_status = SEARCHING;
			}
			break;
		case COLLECTING_RMC:
			if(symbol == '\n') {
				printf("End of RMC packet.\n");
				void parse_RMC();
				gps_index = 0;
				gps_status = SEARCHING;
			}
			break;
		}
	}
	return 0;
}

void parse_GGA() {

}

void parse_GLL() {

}

void parse_RMC() {

}
