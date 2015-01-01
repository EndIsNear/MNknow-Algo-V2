#ifndef MYTREE_HPP
#define MYTREE_HPP

struct MyNode
{
    MyNode(int _key, Desk * _val) : key(_key), val(_val)
    {
        for(unsigned i = 0; i < DESK_WIDTH; ++i)
        {
            this->children[i] = NULL;
        }
    }
    ~MyNode()
    {
        delete this->val;
    }
    int key;
    Desk * val;
    MyNode * children[DESK_WIDTH];
};

class MyTree
{
public:
    MyTree(Desk * val)
    {
        this->root = new MyNode(0, val);
    }
    ~MyTree()
    {
        CleanUp(this->root);
    }

    //returns the right move
    unsigned GetNextMove(unsigned depth, bool maxPlayer)
    {
        //TODO: change hardcoded vals
        int res = this->AlphaBeta(depth, -1000, 1000, maxPlayer, this->root);
        for(unsigned i = 0; i < DESK_WIDTH; ++i)
        {
            if(this->root->children[i] != NULL && this->root->children[i]->key == res)
                return i;
        }
    }
private:
    MyNode * root;

    void CleanUp(MyNode * node)
    {
        if(!node)
            return;
        for(unsigned i = 0; i < DESK_WIDTH; ++i)
        {
            CleanUp(node->children[i]);
        }
        delete node;
    }

    bool Insert(int _key, unsigned moveN, MyNode * node)
    {
        Desk * tmp = new Desk(*(node->val));
        tmp->MakeMove(moveN);
        MyNode * tmpNode = new MyNode(0,tmp);
        node->children[moveN] = tmpNode;

        return true;
    }

    int AlphaBeta(unsigned depth, int alpha, int beta, bool maxPlayer, MyNode * node)
    {
        unsigned childrenCnt = 0;
        if(!depth)
        {
            return node->val->Calc();
        }
        else if(maxPlayer)
        {
            for(unsigned i = 0; i < DESK_WIDTH; ++i)
            {
                if(node->val->IsPossMove(i))
                {
                    Insert(0,i,node);
                    ++childrenCnt;
                    alpha = std::max(alpha, AlphaBeta(depth - 1, alpha, beta, !maxPlayer, node->children[i]));
                    if(alpha >= beta)
                    {
                        node->key = alpha;
                        return alpha;
                    }
                }
            }
            return alpha;
        }
        else
        {
            for(unsigned i = 0; i < DESK_WIDTH; ++i)
            {
                if(node->val->IsPossMove(i))
                {
                    Insert(0,i,node);
                    ++childrenCnt;
                    beta = std::min(beta, AlphaBeta(depth - 1, alpha, beta, !maxPlayer, node->children[i]));
                    if(alpha >= beta)
                    {
                        node->key = beta;
                        return beta;
                    }
                }
            }
            return beta;
        }

        //if the desk is full
        if(!childrenCnt)
        {
            return node->val->Calc();
        }
    }
};


#endif // MYTREE_HPP
