#include "Desk.h"

const int evaluationTable[7][6] = {{3, 4, 5, 5, 4, 3},
                                    {4, 6, 8, 8, 6, 4},
                                    {5, 8, 11 ,11 ,8 ,5 },
                                    {7, 10, 13, 13, 10, 7},
                                    {5, 8, 11 ,11 ,8 ,5 },
                                    {4, 6, 8, 8, 6, 4},
                                    {3, 4, 5, 5, 4, 3}};

Desk::Desk(unsigned _width, unsigned _height) : width(_width), height(_height)
{
    this->desk = new char * [this->width];
    for(unsigned i = 0; i < this->width; ++i)
    {
        this->desk[i] = new char[this->height];
        for(unsigned j = 0; j < this->height; ++j)
        {
            this->desk[i][j] = ' ';
        }
    }
    this->isXonMove = true;
}

Desk::Desk(const Desk& from)
{
    this->width = from.width;
    this->height = from.height;

    this->desk = new char * [this->width];
    for(unsigned i = 0; i < this->width; ++i)
    {
        this->desk[i] = new char[this->height];
        for(unsigned j = 0; j < this->height; ++j)
        {
            this->desk[i][j] = from.desk[i][j];
        }
    }
}

Desk::~Desk()
{
    for(unsigned i = 0; i < this->width; ++i)
    {
        delete[] this->desk[i];
    }
    delete[] this->desk;
}

bool Desk::IsPossMove(unsigned row)
{
    return this->desk[row][0] == ' ';
}

char Desk::MakeMove(unsigned col)//return char of the winner if someone wins
{
    unsigned i;
    for(i = this->height - 1; i >= 0; --i)
    {
        if(this->desk[col][i] == ' ')
        {
            this->desk[col][i] = this->isXonMove ? 'X' : 'O';
            break;
        }
    }
    if(this->CheckForWinner(col, i))
    {
        return this->isXonMove ? 'X' : 'O';
    }

    this->isXonMove = !this->isXonMove;
    return ' ';
}

bool Desk::CheckForWinner(unsigned ver, unsigned hor)
{
    //horizontal
    for(int i = -3; i < 3; ++i)
    {
        if(((int)ver + i >= 0) && ((int)ver + i + 3 < this->width))
        {
            bool isEqual = this->desk[ver + i][hor] != ' ';
            for(int j = 1; j < 4 && isEqual; ++j)
            {
                isEqual = desk[ver + i][hor] == desk[ver + i + j][hor];
            }
            if(isEqual)
                return true;
        }
    }

    //vertical
    for(int i = -3; i < 3; ++i)
    {
        if(((int)hor + i >= 0) && ((int)hor + i + 3 < this->height))
        {
            bool isEqual = this->desk[ver][hor + i] != ' ';
            for(int j = 1; j < 4 && isEqual; ++j)
            {
                isEqual = desk[ver][hor + i] == desk[ver][hor + i + j];
            }
            if(isEqual)
                return true;
        }
    }

    //1st diagonal
    for(int i = -3; i < 3; ++i)
    {
        if(((int)hor + i >= 0) && ((int)hor + i + 3 < this->height)
            && ((int)ver + i >= 0) && ((int)ver + i + 3 < this->width))
        {
            bool isEqual = this->desk[ver + i][hor + i] != ' ';
            for(int j = 1; j < 4 && isEqual; ++j)
            {
                isEqual = desk[ver + i][hor + i] == desk[ver + i + j][hor + i + j];
            }
            if(isEqual)
                return true;
        }
    }

    //2nd diagonal
    for(int i = -3; i < 3; ++i)
    {
        if(((int)hor - i >= 0) && ((int)hor - i - 3 < this->height)
            && ((int)ver + i >= 0) && ((int)ver + i + 3 < this->width))
        {
            bool isEqual = this->desk[ver + i][hor - i] != ' ';
            for(int j = 1; j < 4 && isEqual; ++j)
            {
                isEqual = desk[ver + i][hor - i] == desk[ver + i + j][hor - i - j];
            }
            if(isEqual)
                return true;
        }
    }

    return false;
}

int Desk::Calc()
{
    int res = 0;
    for(unsigned i = 0; i < this->width; ++i)
    {
        for(unsigned j = 0; j < this->height; ++j)
        {
            if(this->desk[i][j] == 'O')
            {
                res += evaluationTable[i][j];
            }
            else if(this->desk[i][j] == 'X')
            {
                res -= evaluationTable[i][j];
            }
        }
    }
    return res;
}

void Desk::Print(std::ostream& out)
{
    for(unsigned i = 0; i < this->width; ++i)
    {
        std::cout << "=";
    }
    std::cout << std::endl;

    for(unsigned i = 0; i < this->height; ++i)
    {
        for(unsigned j = 0; j < this->width; ++j)
        {
            std::cout << this->desk[j][i];
        }
        std::cout << std::endl;
    }

    for(unsigned i = 0; i < this->width; ++i)
    {
        std::cout << "=";
    }
    std::cout << std::endl;
}
