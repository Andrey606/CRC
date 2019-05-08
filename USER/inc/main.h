/*
* CRC result: 500606213, 0x1DD6A505
* CRC_32 polynomial: 0x4C11DB7
*
* %u    - uint32_t
* %d    - int
* %x    - hex
* %lu   - long int
* %u    - unsigned int
*
*/

#include <stdio.h> 
#include <stdlib.h>

typedef __uint32_t uint32_t;

const uint32_t CRC_32_polynomial = 0x04C11DB7;

void write_file(uint32_t value);
uint32_t calculate_crc_32(uint32_t *buffer, unsigned int length);
uint32_t *load_data_from_file(const char *file, unsigned int *buf_size);
long int filesize_bytes( FILE *fp );