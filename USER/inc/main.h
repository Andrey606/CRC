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
*           0x0074E401 -> 0xF55A75A0
*           0x00000500 -> 0x973DE075
*           0x34363832 -> 0x244E2C4C
*           ...
*                      -> 0x98A92CAC
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

const uint32_t CRC_result = 0x1DD6A505;

#define CRC32_POLY   0x04C11DB7
#define CRC32_POLY_R 0xEDB88320

static uint32_t crc32_table[256];
static uint32_t crc32r_table[256];

// prototypes ---------------------------------------------------------------------

void write_file(uint32_t value);
uint32_t calculate_crc(uint32_t *buffer, unsigned int length);
uint32_t *load_data_from_file(const char *path_file, unsigned int *buf_size);
long int filesize_bytes( FILE *fp );

static void crc32_init(void);
uint32_t crc32_byte(uint32_t init_crc, uint8_t *buf, int len);
uint32_t crc32_stm32(uint32_t init_crc, uint32_t *buf, int len);

uint32_t crc32(uint32_t crc, const void *buf, size_t size);