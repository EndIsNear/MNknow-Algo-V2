#include <iostream>

#define DESK_WIDTH 7
#define DESK_HEIGHT 6
#define TREE_DEPTH 7


#include "Desk.h"
#include "MyTree.hpp"



int main ()
{
    bool exit = false;
    int nextMove;
    char res;
    Desk playDesk(DESK_WIDTH, DESK_HEIGHT);

    while(!exit)
    {
        do
        {
            std::cout << "Enter move:" << std::endl;
            std::cin >> nextMove;
        }while(nextMove < 1 || nextMove > 7 || !playDesk.IsPossMove(--nextMove));
        //nextMove--;
        res = playDesk.MakeMove(nextMove);
        playDesk.Print(std::cout);
        if(res != ' ')
        {
            std::cout <<"You won the game!" << std::endl;
            exit = true;
        }
        if(!exit)
        {
            MyTree alphaBeta(new Desk(playDesk));
            nextMove = alphaBeta.GetNextMove(TREE_DEPTH, true);
            playDesk.MakeMove(nextMove);
            playDesk.Print(std::cout);
            if(res != ' ')
            {
                std::cout <<"Computer won the game!" << std::endl;
                exit = true;
            }
        }
    }

    return 0;
}
