#include <stdio.h>

#define BUFFER_SIZE 1024 * 1024

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Error!\n");
    }

    unsigned long long * buff;
    buff = new unsigned long long[BUFFER_SIZE];
    if(!buff)
    {
        printf("Error!\n");
        return 0;
    }

    for(int i = 1; i < argc; ++i)
    {
        bool isSorted = true;
        unsigned long long readed, lastReaded = 0;
        printf("Start %s\n", argv[i]);
        FILE * input = fopen(argv[i], "r");
        if(!input)
        {
            printf("Can't open %s", argv[i]);
            continue;
        }

        do
        {
            readed = fread(buff, sizeof(unsigned long long), BUFFER_SIZE, input);
            if(lastReaded > buff[0])
                isSorted = false;
            for(unsigned long long j = 0; isSorted && readed && (j < readed - 1); ++j)
            {
                isSorted = buff[j] < buff[j + 1] ? true : false;
            }
            lastReaded = buff[readed];
        }
        while(readed && isSorted);

        if(isSorted)
            printf("%s is sorted!\n", argv[i]);
        else
            printf("%s isn't sorted!\n", argv[i]);
        fclose(input);
    }
    delete[] buff;
    return 0;
}
