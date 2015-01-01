#ifndef DESK_H
#define DESK_H
#include <iostream>

class Desk
{
public:
    Desk(unsigned, unsigned);
    Desk(const Desk&);
    ~Desk();

    void Print(std::ostream&);
    bool IsPossMove(unsigned);
    char MakeMove(unsigned);
    bool CheckForWinner(unsigned, unsigned);
    int Calc();
private:
    char ** desk;
    unsigned width, height;
    bool isXonMove;
};

#endif // DESK_H
