#ifndef B_TREE
#define B_TREE

#include <cstdlib>

template <typename T>
struct BTreeNode
{
	BTreeNode(T _val)
	{
		this->val = _val;
		this->pLeft = this->pRight = NULL;
	}

	T val;
	BTreeNode * pLeft;
	BTreeNode * pRight;
};

template <typename T>
class BinaryTree
{
public:
	BinaryTree()
	{
		this->root = NULL;
	}

	~BinaryTree()
	{
		CleanUp(this->root);
	}

	bool Insert(T& val)
	{
		if (IsEmpty())
		{
			this->root = new (std::nothrow) BTreeNode<T>(val);
			return this->root ? true : false;
		}

		return Insert(val, this->root);
	}

	BTreeNode<T> * Find(T& val)
	{
		if (IsEmpty)
			return NULL;
		BTreeNode<T> * parrent = NULL;
		Find(T& val, this->root, useless);
	}

	bool Remove(T& val)
	{
		return this->Remove(val, this->root);
	}

private:
	bool Insert(T& val, BTreeNode<T> * node)
	{
		if (val >= node->val)
		{
			if (node->pRight)
			{
				return Insert(val, node->pRight);
			}
			else
			{
				node->pRight = new (std::nothrow) BTreeNode<T>(val);
				return node->pRight ? true : false;
			}
		}
		else
		{
			if (node->pLeft)
			{
				return Insert(val, node->pLeft);
			}
			else
			{
				node->pLeft = new (std::nothrow) BTreeNode<T>(val);
				return node->pLeft ? true : false;
			}
		}
	}



	BTreeNode<T> * Find(T& val, BTreeNode<T> * node, BTreeNode<T> * &parrent)
	{
		if (!node)
			return NULL;
		if (val == node->val)
			return node;
		else
		{
			parrent = node;
			return Find(val, val > node->val ? node->pRight : node->pLeft, node);
		}
	}

	bool IsEmpty()
	{
		return !root;
	}

	void CleanUp(BTreeNode<T> * node)
	{
		if (node != NULL)
		{
			CleanUp(node->pLeft);
			CleanUp(node->pRight);
			delete node;
		}
	}

	bool Remove(T& val, BTreeNode<T> * tree)
	{
		if (!tree)
			return false;

		BTreeNode<T> * parrent = NULL;
		BTreeNode<T> * nodeForDel = Find(val, this->root, parrent);
		if (!nodeForDel)
			return false;

		//two children
		if (nodeForDel->pLeft && nodeForDel->pRight)
		{
			BTreeNode<T> * tmp = this->FindMin(nodeForDel->pRight);
			nodeForDel->val = tmp->val;
			this->Remove(tmp->val, tmp);
		}

		//0 or 1 child
		else
		{
			BTreeNode<T> ** ptrForChange = NULL;
			if (nodeForDel == this->root)
				ptrForChange = &this->root;
			else
				ptrForChange = parrent->val >= nodeForDel->val ? &parrent->pLeft : &parrent->pRight;
			*ptrForChange = nodeForDel->pLeft ? nodeForDel->pLeft : nodeForDel->pRight;
			delete nodeForDel;
		}

		return true;
	}

	BTreeNode<T> * FindMin(BTreeNode<T> * node)
	{
		while (node->pLeft)
		{
			node = node->pLeft;
		}
		return node;
	}

	BTreeNode<T> * root;
};

#endif //B_TREE
