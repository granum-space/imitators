/*
 * fake_spi.c
 *
 *  Created on: 24 мая 2016 г.
 *      Author: snork
 */


#include <stddef.h>
#include <stdint.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>

#include "spi.h"

#define FAKE_DATA_PATH "fake_gps_data.txt"

struct FakeGpsState
{
	typedef enum
	{
		STATE_IN_PAUSE,
		STATE_IN_MESSAGE,
	} State;

	size_t pause_left;
	std::ifstream gps_data_stream;
	State state;
};

FakeGpsState state;


static size_t get_pause()
{
	const int max_pause = 10;
	const int min_pause = 1;
	return min_pause + (rand() % (int)(max_pause - min_pause + 1));
}


void spi_init(void)
{
	srand(time(NULL));
	std::cout << "Начинаем инициализацию ненастоящего SPI" << std::endl;
	state.gps_data_stream.open("./src/fake_gps_data.txt", std::ios::in);
	state.pause_left = get_pause();
	state.state = FakeGpsState::STATE_IN_PAUSE;
}


uint8_t spi_sendbyte(uint8_t arg)
{
	switch (state.state)
	{
	case FakeGpsState::STATE_IN_PAUSE:
	in_pause:
		if (state.pause_left == 0)
		{
			state.state = FakeGpsState::STATE_IN_MESSAGE;
			goto in_message;
		}
		else
		{
			state.pause_left--;
		}
		break;

	case FakeGpsState::STATE_IN_MESSAGE:
	in_message:
		std::ifstream::char_type next = state.gps_data_stream.get();
		if (next == std::ifstream::traits_type::eof())
		{
			state.gps_data_stream.close();
			state.gps_data_stream.clear();
			state.gps_data_stream.open(FAKE_DATA_PATH, std::ios::in);
			state.pause_left = get_pause();
			state.state = FakeGpsState::STATE_IN_PAUSE;
			goto in_pause;
		}
		else if (next == '\n')
		{
			state.pause_left = get_pause();
			state.state = FakeGpsState::STATE_IN_PAUSE;
			return next;
		}
		else
		{
			return next;
		}

		break;
	};

	return 0xFF;
}


void spi_exchange(const void* data, int length, uint8_t* retval)
{
	for (int i = 0; i < length; i++)
	{
		retval[i] = spi_sendbyte(*((const uint8_t*)data+i));
	}

}
