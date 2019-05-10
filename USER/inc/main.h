/*
* http://www.cyberforum.ru/arm/thread2092120.html
* http://we.easyelectronics.ru/STM32/crc32-na-stm32-kak-na-kompe-ili-na-kompe-kak-na-stm32.html
*
* CRC result: 500606213, 0x1DD6A505
* CRC_32 polynomial:    0x4C11DB7
*                       0xEDB88320UL (mirror)
*
* %u    - uint32_t
* %d    - int
* %x    - hex
* %lu   - long int
* %u    - unsigned int
* UL    - unsigned long
* U     - unsigned int
*
*
* Example:  0x44414548 -> 0xD9E49D9A
*           0x0074E401 -> 0x7309BAAE
*           0x00000500 -> 0x61DC3F57
*           0x34363832 -> 0xA62C7754
*           ...
*                      -> 0x1dd6a505
*/

#include <stdio.h> 
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>
#include <sys/param.h>

// typedef ------------------------------------------------------------------------

typedef __uint32_t uint32_t;

// variables ----------------------------------------------------------------------

#define CRC32_POLY   0x04C11DB7
uint32_t custom_crc_table[256];
int byte_array[4];

// prototypes ---------------------------------------------------------------------

void write_file(uint32_t value);
uint32_t *load_data_from_file(const char *path_file, unsigned int *buf_size);
long int filesize_bytes( FILE *fp );

uint32_t custom_crc32(uint32_t *buffer, unsigned int length);
void generate_crc32_table(uint32_t poly);
void int_to_bytes(uint32_t i);
