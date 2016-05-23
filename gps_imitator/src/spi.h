/*
 * spi.h
 *
 *  Created on: 24 мая 2016 г.
 *      Author: snork
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

// необходимо для использования C++ кода из Си
 #ifdef __cplusplus
 extern "C" {
 #endif

void spi_init();
uint8_t spi_sendbyte(uint8_t arg);
void spi_exchange(const void* data, int length, uint8_t* retval);

#ifdef __cplusplus
}
#endif


#endif /* SPI_H_ */
