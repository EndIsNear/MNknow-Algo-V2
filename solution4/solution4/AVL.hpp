#ifndef AVL_HPP
#define AVL_HPP

#include <new>

template<typename K, typename V>
struct AVLNode
{
    AVLNode(K key, V& val, int height = 1)
    {
        this->key = key;
        this->val = val;
        this->pLeft = this->pRight = NULL;
        this->height = height;
    }
    K key;
    V val;
    unsigned height;
    AVLNode * pLeft, *pRight;
};

template<typename K, typename V>
class AVLTree
{
public:
    AVLTree()
    {
        this->root = NULL;
    }

    ~AVLTree()
    {
        CleanUp(this->root);
    }

    void Insert(K key, V& val)
    {
        this->root = Insert(key, val, this->root);
    }

    V * Find(K key)
    {
        AVLNode<K,V> * res = (Find(key, this->root));
        return res ? &(res->val) : NULL;
    }

    void Remove(K key)
    {
        this->root = Remove(key, this->root);
    }

private:
    AVLNode<K, V> * root;

    AVLNode<K, V> * Insert(K key, V& val, AVLNode<K, V> * node)
    {
        if (!node)
        {
            return new AVLNode<K, V>(key, val);
        }
        if (key < node->key)
        {
            node->pLeft = Insert(key, val, node->pLeft);
        }
        else
        {
            node->pRight = Insert(key, val, node->pRight);
        }

        return Balance(node);
    }

    AVLNode<K, V> * Find(K key, AVLNode<K, V> * node)
    {
        if (!node)
            return NULL;
        if (key == node->key)
            return node;
        else
        {
            return Find(key, key > node->key ? node->pRight : node->pLeft);
        }
    }

    AVLNode<K, V> * Remove(K key, AVLNode<K, V> * node)
    {
        if (!node) return 0;
        if (key < node->key)
            node->pLeft = Remove(key, node->pLeft);
        else if (key > node->key)
            node->pRight = Remove(key, node->pRight);
        else
        {
            AVLNode<K, V> * tmpL = node->pLeft;
            AVLNode<K, V> * tmpR = node->pRight;
            delete node;
            if (!tmpR)
                return tmpL;
            AVLNode<K, V> * min = FindMin(tmpR);
            min->pRight = RemoveMin(tmpR);
            min->pLeft = tmpL;
            return Balance(min);
        }
        return Balance(node);
    }

    //Helper funcs
    AVLNode<K, V> * Balance(AVLNode<K, V> * node)
    {
        CalcHeight(node);
        if (GetBalance(node) == 2)
        {
            if (GetBalance(node->pRight) < 0)
                node->pRight = RotateRight(node->pRight);
            return RotateLeft(node);
        }
        if (GetBalance(node) == -2)
        {
            if (GetBalance(node->pLeft) > 0)
                node->pLeft = RotateLeft(node->pLeft);
            return RotateRight(node);
        }
        return node;
    }

    AVLNode<K, V> * RotateRight(AVLNode<K, V> * node)
    {
        AVLNode<K, V> * tmp = node->pLeft;
        node->pLeft = tmp->pRight;
        tmp->pRight = node;
        CalcHeight(node);
        CalcHeight(tmp);
        return tmp;
    }

    AVLNode<K, V> * RotateLeft(AVLNode<K, V> * node)
    {
        AVLNode<K, V> * tmp = node->pRight;
        node->pRight = tmp->pLeft;
        tmp->pLeft = node;
        CalcHeight(node);
        CalcHeight(tmp);
        return tmp;
    }

    unsigned GetHeight(AVLNode<K, V> * node)
    {
        return node ? node->height : 0;
    }

    int GetBalance(AVLNode<K, V> * node)
    {
        return GetHeight(node->pRight) - GetHeight(node->pLeft);
    }

    void CalcHeight(AVLNode<K, V> * node)
    {
        unsigned hLeft = GetHeight(node->pLeft);
        unsigned hRight = GetHeight(node->pRight);
        node->height = (hLeft > hLeft ? hLeft : hRight) + 1;
    }

    AVLNode<K, V> * FindMin(AVLNode<K, V> * node)
    {
        return node->pLeft ? FindMin(node->pLeft) : node;
    }

    AVLNode<K, V> * RemoveMin(AVLNode<K, V> * node)
    {
        if (node->pLeft == 0)
            return node->pRight;
        node->pLeft = RemoveMin(node->pLeft);
        return Balance(node);
    }

    void CleanUp(AVLNode<K, V> *& node)
    {
        if (node != NULL)
        {
            CleanUp(node->pLeft);
            CleanUp(node->pRight);
            delete node;
        }
    }
};


#endif //AVL_HPP
