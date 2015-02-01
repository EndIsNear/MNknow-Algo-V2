
#ifndef SPLAY_HPP
#define SPLAY_HPP

#include <new>

template<typename K, typename V>
struct SplayNode
{
    SplayNode()
    {
        this->pLeft = this->pRight = NULL;
    }
    SplayNode(K key, V& val)
    {
        this->key = key;
        this->val = val;
        this->pLeft = this->pRight = NULL;
    }
    K key;
    V val;
    SplayNode * pLeft, * pRight;
};

template<typename K, typename V>
class Splay
{
public:

    Splay()
    {
        this->root = NULL;
    }

    ~Splay()
    {
        CleanUp(this->root);
    }

    void Insert(K key, V& val)
    {
        this->root = Insert(key, val, this->root);
        this->root = SplayIt(key, this->root);
    }

    V * Find(K key)
    {
        this->root = this->SplayIt(key, this->root);
        return &(root->val);
    }

    void Remove(K key)
    {
        this->root = Remove(key, this->root);
    }

private:

    SplayNode<K, V> * root;

    SplayNode<K, V> * Insert(K key, V& val, SplayNode<K, V> * node)
    {
        if (!node)
        {
            return new SplayNode<K, V>(key, val);
        }
        if (key < node->key)
        {
            node->pLeft = Insert(key, val, node->pLeft);
        }
        else
        {
            node->pRight = Insert(key, val, node->pRight);
        }
        return node;
    }

    SplayNode<K, V> * SplayIt(K key, SplayNode<K, V> * node)
    {
        if (!node)
            return NULL;
        
        SplayNode<K, V> header;
        SplayNode<K, V> * LeftTreeMax = &header;
        SplayNode<K, V> * RightTreeMin = &header;

        while (1)
        {
            if (key < node->key)
            {
                if (!node->pLeft)
                    break;
                if (key < node->pLeft->key)
                {
                    node = RotateLeft(node);

                    if (!node->pLeft)
                        break;
                }
                RightTreeMin->pLeft = node;
                RightTreeMin = RightTreeMin->pLeft;
                node = node->pLeft;
                RightTreeMin->pLeft = NULL;
            }
            else if (key > node->key)
            {
                if (!node->pRight)
                    break;
                if (key > node->pRight->key)
                {
                    node = RotateRight(node);

                    if (!node->pRight)
                        break;
                }
                LeftTreeMax->pRight = node;
                LeftTreeMax = LeftTreeMax->pRight;
                node = node->pRight;
                LeftTreeMax->pRight = NULL;
            }
            else
                break;
        }
        LeftTreeMax->pRight = node->pLeft;
        RightTreeMin->pLeft = node->pRight;
        node->pLeft = header.pRight;
        node->pRight = header.pLeft;

        return node;
    }

	//Helper funcs
	SplayNode<K, V> * Remove(K key, SplayNode<K, V> * node)
    {
        if (!node) return 0;
        if (key < node->key)
            node->pLeft = Remove(key, node->pLeft);
        else if (key > node->key)
            node->pRight = Remove(key, node->pRight);
        else
        {
            SplayNode<K, V> * tmpL = node->pLeft;
            SplayNode<K, V> * tmpR = node->pRight;
            delete node;
            if (!tmpR)
                return tmpL;
            SplayNode<K, V> * min = FindMin(tmpR);
            min->pRight = RemoveMin(tmpR);
            min->pLeft = tmpL;
            return min;
        }
        return node;
    }

    SplayNode<K, V> * RotateLeft(SplayNode<K, V> * node)
    {
        SplayNode<K, V> * tmp = node->pLeft;
        node->pLeft = tmp->pRight;
        tmp->pRight = node;
        return tmp;
    }

    SplayNode<K, V> * RotateRight(SplayNode<K, V> * node)
    {
        SplayNode<K, V> * tmp = node->pRight;
        node->pRight = tmp->pLeft;
        tmp->pLeft = node;
        return tmp;
    }

    SplayNode<K, V> * FindMin(SplayNode<K, V> * node)
    {
        while (node->pLeft)
        {
            node = node->pLeft;
        }
        return node;
    }

    SplayNode<K, V> * RemoveMin(SplayNode<K, V> * node)
    {
        if (node->pLeft == 0)
            return node->pRight;
        node->pLeft = RemoveMin(node->pLeft);
        return node;
    }

    void CleanUp(SplayNode<K, V> *& node)
    {
        if (node != NULL)
        {
            CleanUp(node->pLeft);
            CleanUp(node->pRight);
            delete node;
        }
    }
};

#endif //SPLAY_HPP