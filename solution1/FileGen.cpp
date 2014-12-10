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
    unsigned long long resSizeInMb, *buff;
    buff = new unsigned long long[BUFFER_SIZE];
    FILE * output = fopen(argv[1], "w");
    if(!output || !buff)
    {
        printf("Error!");
        return 0;
    }
    resSizeInMb = argc > 2 ? atoi(argv[2]) : 1024;

    unsigned sizeInLLUs = BUFFER_SIZE/sizeof(unsigned long long);

    for(unsigned mb = 0; mb < resSizeInMb; ++mb)
    {
        for(unsigned i = 0; i < sizeInLLUs; ++i)
        {
            buff[i] = rand() * rand();
        }
        fwrite(buff, sizeof(unsigned long long), sizeInLLUs, output);
    }

    delete[] buff;
    fclose(output);
    return 0;
}
