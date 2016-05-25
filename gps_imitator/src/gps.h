#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>

void GPS_Init();
uint8_t GPS_Read_Data(float * latitude, float * longitude, float * height);



#endif /* GPS_H_ */
