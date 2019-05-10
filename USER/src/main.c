#include "../inc/main.h"


int main(int argc, char const *argv[])
{
    uint32_t buff_length;
    uint32_t *buff = load_data_from_file("./USER/crc.bin", &buff_length);

    generate_crc32_table(CRC32_POLY);
    printf("crc: 0x%x\n", custom_crc32(buff, buff_length));

    free(buff);
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

// crc operations -------------------------------------------------------

void int_to_bytes(uint32_t i)
{
    byte_array[0] = ((i >> 24) & 0xFF);
    byte_array[1] = ((i >> 16) & 0xFF);
    byte_array[2] = ((i >> 8) & 0xFF);
    byte_array[3] = (i & 0xFF);
}

void generate_crc32_table(uint32_t poly)
{
    uint32_t c;

    for (int i = 0; i < 256; i++)
    {
        c = i << 24;

        for (int j = 0; j < 8; j++)
        {
            if(c & 0x80000000){
                c = (c << 1) ^ poly;
            }else{
                c = c << 1;
            }
        }

        custom_crc_table[i] = c & 0xffffffff;
    }
    
}

uint32_t custom_crc32(uint32_t *buffer, unsigned int length)
{
    uint32_t crc = 0xffffffff;

    for (int i = 0; i < length; i++)
    {
        int_to_bytes(buffer[i]);

        for (int j = 0; j < 4; j++)
        {
            crc = ((crc << 8) & 0xffffffff) ^ custom_crc_table[(crc >> 24) ^ byte_array[j]];
        }
        
    }
    
    return crc;
}