#include <stdio.h>
#include <sys/statvfs.h>
#include <algorithm>
#include <vector>

#define FILE_BUFF_SIZE 4096
#define BUFFER_SIZE 1024 * 1024 * 64

class ULLbuffFile
{
public:
    ULLbuffFile(FILE * _file)
    {
        this->file = _file;
        this->buffSize = FILE_BUFF_SIZE/sizeof(unsigned long long);
        this->buff = new unsigned long long[this->buffSize];
        this->elements = 0;
        this->nextIdx = 0;
    };
    ~ULLbuffFile()
    {
        delete[] this->buff;
    }
    bool getNext(unsigned long long& result)
    {
        if(elements - nextIdx <= 1)
        {
            this->readNewBlock();
            if(!this->elements)
            {
                result = 0;
                return false;
            }
        }
        result = buff[nextIdx++];
    }
    void readNewBlock()
    {
        this->elements = fread(this->buff, sizeof(unsigned long long), this->buffSize, this->file);
        nextIdx = 0;
    }

private:
    FILE * file;
    unsigned long long * buff;
    unsigned buffSize, elements, nextIdx;
};

void mergeTwoFiles(FILE * leftFile, FILE * rightFile, FILE * result)
{
    unsigned long long leftInt, rightInt;
    ULLbuffFile left(leftFile), right(rightFile);
    bool bLeft = left.getNext(leftInt), bRight = right.getNext(rightInt);
    while(bLeft && bRight)
    {
        if(leftInt <= rightInt)
        {
            fwrite(&leftInt, sizeof(leftInt), 1, result);
            bLeft = left.getNext(leftInt);
        }
        else
        {
            fwrite(&rightInt, sizeof(rightInt), 1, result);
            bRight = right.getNext(rightInt);
        }
    }
    while(bLeft)
    {
        fwrite(&leftInt, sizeof(leftInt), 1, result);
        bLeft = left.getNext(leftInt);
    }
    while(bRight)
    {
        fwrite(&rightInt, sizeof(rightInt), 1, result);
        bRight = right.getNext(rightInt);
    }
}

//memory size in LLUs
bool HDDsort(FILE * fileForSort, char * destName, unsigned long memorySize, unsigned long long * memory)
{
    std::vector<unsigned> tmpFiles;
    unsigned read = fread(memory, sizeof(unsigned long long), memorySize, fileForSort);
    unsigned filesCnt;
    char tmpName[16];
    for(filesCnt = 0; read; ++filesCnt)
    {
        std::sort(memory,memory + memorySize);
        char tmpName[16];
        sprintf(tmpName, "tmpfile%u", filesCnt);
        FILE * tmpFile = fopen(tmpName, "w");
        tmpFiles.push_back(filesCnt);
        if(!tmpFile)
        {
            printf("Error!");
            return false;
        }
        fwrite(memory, sizeof(unsigned long long), read, tmpFile);
        fclose(tmpFile);
        read = fread(memory, sizeof(unsigned long long), memorySize, fileForSort);
    }
    fclose(fileForSort);

    char leftName[16];
    char rightName[16];
    while(tmpFiles.size() > 1)
    {
        sprintf(leftName, "tmpfile%u", tmpFiles[0]);
        FILE * left     = fopen(leftName, "r");
        sprintf(rightName, "tmpfile%u", tmpFiles[1]);
        FILE * right    = fopen(rightName, "r");
        if(tmpFiles.size() > 2)
            sprintf(tmpName, "tmpfile%u", filesCnt);
        else //last merge
            sprintf(tmpName, destName, filesCnt);
        FILE * merged   = fopen(tmpName, "w");
        tmpFiles.push_back(filesCnt);
        if(!left || !right || !merged)
        {
            return false;
        }
        mergeTwoFiles(left, right, merged);
        fclose(left);
        fclose(right);
        fclose(merged);
        printf("%s    %s\n", leftName, rightName);
        remove(leftName);
        remove(rightName);
        filesCnt++;
        tmpFiles.erase (tmpFiles.begin(),tmpFiles.begin()+2);
    }
}

int main(int argc, char * argv[])
{
    if(argc < 1)
    {
        printf("Error!");
        return 0;
    }

    FILE * fileForSort = fopen(argv[1], "r");
    if(!fileForSort)
    {
        printf("Error!");
        return 0;
    }
    unsigned long memsize = BUFFER_SIZE/sizeof(unsigned long long);
    unsigned long long * mem = new unsigned long long[memsize];
    if(!mem)
    {
        printf("Error!");
        return 0;
    }
    HDDsort(fileForSort, argv[1], memsize, mem);
    delete[] mem;
    return 0;
}
