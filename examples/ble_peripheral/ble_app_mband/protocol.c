#include "protocol.h"

uint32_t timestamp = 0;
uint8_t sensor_index = 0;
uint8_t sensor_delay = 10;

void fill_sensor_data(uint8_t* dest_data, int16_t* acc, uint16_t heart, int16_t GSR_f)
{
			dest_data[0] = PROTOCOL_HEADER;
			dest_data[1] = MODE_SENSOR;
			dest_data[2] = SENSOR_TYPE;
	
			dest_data[3] = (acc[0] >> 8) & 0xFF;
			dest_data[4] = acc[0] & 0xFF;
	
			dest_data[5] = (acc[1] >> 8) & 0xFF;
			dest_data[6] = acc[1] & 0xFF;
	
			dest_data[7] = (acc[2] >> 8) & 0xFF;
			dest_data[8] = acc[2] & 0xFF;
	
			dest_data[9] = heart & 0xFF;
	
			dest_data[10] = (GSR_f >> 8) & 0xFF;
			dest_data[11] = GSR_f & 0xFF;
			
			dest_data[12] = getCheckSum(dest_data, 0, 11, CHECKSUM_XOR);
			dest_data[13] = PROTOCOL_FOOTER;
}

void routine_timestamp_protocol(uint8_t *msg)
{
	if(msg[6] != getCheckSum(msg, 0, 5, CHECKSUM_XOR) || msg[7] != PROTOCOL_FOOTER)
		return;
	
	if(msg[2] == 0x00)
		timestamp = ((msg[3] << 16) & 0xFF0000) | ((msg[4] << 8) & 0xFF00) | (msg[5] & 0xFF);
	else if(msg[2] == 0x01)
		timestamp += ((msg[4] << 8) & 0xFF00) | (msg[5] & 0xFF);
	else if(msg[2] == 0x02)
		timestamp -= ((msg[4] << 8) & 0xFF00) | (msg[5] & 0xFF);
}

void routine_sensor_index_protocol(uint8_t *msg)
{
	if(msg[3] != getCheckSum(msg, 0, 2, CHECKSUM_XOR) || msg[4] != PROTOCOL_FOOTER)
		return;
	
	sensor_index = msg[2];
}

void routine_sensor_delay_time_protocol(uint8_t *msg)
{
		if(msg[4] != getCheckSum(msg, 0, 3, CHECKSUM_XOR) || msg[5] != PROTOCOL_FOOTER)
			return;
		
		sensor_delay = ((msg[2] << 8) & 0xFF00) | (msg[3] & 0xFF);
}

char getCheckSum(uint8_t *byte_data, int startIdx, int endidx, int method)
{
	char result = 0x00;
	
	for(int i=startIdx; i<=endidx; i++)
	{
		result ^= byte_data[i];
	}
	
	return result;
}


