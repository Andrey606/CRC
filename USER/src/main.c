
#include "../inc/main.h"


int main(int argc, char const *argv[])
{

    return 0;
}

void write_file(uint32_t value)
{
    FILE *file;

    if((file=fopen("./USER/crc.txt", "a+"))==NULL) 
    {
        printf ("Cannot open file.\n");
        exit(1);
    }else{
        printf ("Open file successful.\n");
    }

    fprintf(file, "%08x", value);

    printf ("Файл закрыт\n");

    fclose(file); 
}