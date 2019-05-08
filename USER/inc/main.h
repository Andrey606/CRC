/*
* CRC result: 500606213, 0x1DD6A505
* CRC_32 polynom: 0x4C11DB7
*
* %u    - uint32_t
* %d    - int
* %x    - hex
* %lu   - %long int
*/

#include <stdio.h> 
#include <stdlib.h>

typedef __uint32_t uint32_t;

void write_file(uint32_t value);
uint32_t calculate_crc_32(uint32_t *buffer, uint32_t length);
uint32_t *load_data_from_file(const char *file);
long int filesize_bytes( FILE *fp );