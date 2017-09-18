#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "main.h"

#define CHECKSUM_SUM 0
#define CHECKSUM_XOR 1

#define PROTOCOL_HEADER (char)0xAA
#define PROTOCOL_FOOTER (char)0xFA

#define MODE_SENSOR 0x00
#define SENSOR_TYPE 0x61

char getCheckSum(uint8_t *byte_data, int startIdx, int endidx, int method);
void fill_sensor_data(uint8_t* dest_data, int16_t* acc, uint16_t heart, int16_t GSR);

void routine_timestamp_protocol(uint8_t *msg);
void routine_sensor_index_protocol(uint8_t *msg);
void routine_sensor_delay_time_protocol(uint8_t *msg);

#endif
