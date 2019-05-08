#include "../inc/main.h"


int main(int argc, char const *argv[])
{
    unsigned int buffer_length = 0;
    uint32_t *buffer = load_data_from_file("./USER/crc.bin", &buffer_length);

    uint32_t crc = calculate_crc_32(buffer, buffer_length);
    printf("crc: %u\n", crc);
    printf("crc: 0x%x\n", crc);

    free(buffer);
    return 0;
}


void write_file(uint32_t value)
{
    FILE *file;


    if((file=fopen("./USER/crc.bin", "a+"))==NULL) 
    {
        printf ("ERROR: Cannot open file.\n");
        exit(1);
    }else{
        printf ("open file successfully.\n");
    }

    fwrite(&value, sizeof(uint32_t), 1, file);

    printf ("Файл закрыт\n");

    fclose(file); 
}

uint32_t *load_data_from_file(const char *path_file, unsigned int *buf_size)
{
    uint32_t *buffer;
    uint32_t value;

    // open the file
    FILE *file;
    if((file=fopen(path_file, "r"))==NULL) 
    {
        printf ("ERROR: Cannot open file.\n");
        exit(1);
    }else{
        printf ("open file successfully.\n");
    }

    // count number of values
    *buf_size = filesize_bytes(file); // file size in bytes
    *buf_size = *buf_size / 4;
    printf("%u items were found.\n", *buf_size);

    // allocate memory for the array
    buffer = (uint32_t *) calloc(*buf_size, sizeof(uint32_t));
    if(buffer == NULL)
    {
        printf("ERROR: not enough memory.\n");
        exit(1);
    }else{
        printf("buffer was created.\n");
    }

    // rewind file to reread
    rewind(file);

    // write file values to array 
    fread(buffer, sizeof(uint32_t), *buf_size, file);

    printf("The buffer has been filled successfully.\n");

    // close the file
    fclose(file); 

    return buffer;
}

long int filesize_bytes( FILE *fp )
{
    long int save_pos, size_of_file;

    save_pos = ftell( fp );
    fseek( fp, 0L, SEEK_END );
    size_of_file = ftell( fp );
    fseek( fp, save_pos, SEEK_SET );
    return( size_of_file );
}

uint32_t calculate_crc_32(uint32_t *buffer, unsigned int length)
{
    uint32_t crc = 0xFFFFFFFF;
    unsigned int i;
 
    while (length--)
    {
        crc ^= *buffer++;
 
        for (i = 0; i < 32; i++)
            crc = crc & 0x80000000 ? (crc << 1) ^ CRC_32_polynomial : crc << 1;
 
    } 
 
    crc ^= 0xFFFFFFFF;
    return crc;
}