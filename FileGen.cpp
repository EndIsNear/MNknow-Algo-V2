#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

#define BUFFER_SIZE 1024 * 1024

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("Error!");
        return 0;
    }
    unsigned long long resSize, *buff;
    buff = new unsigned long long[BUFFER_SIZE];
    FILE * output = fopen(argv[1], "w");
    if(!output || !buff)
    {
        printf("Error!");
        return 0;
    }
    resSize = argc > 2 ? atoi(argv[2]) : 1;


    for(unsigned mb = 0; mb < resSize; ++mb)
    {
        for(unsigned i = 0; i < BUFFER_SIZE; ++i)
        {
            buff[i] = rand() * rand();
        }
        fwrite(buff, sizeof(unsigned long long), BUFFER_SIZE, output);
    }

    delete[] buff;
    fclose(output);
    return 0;
}
