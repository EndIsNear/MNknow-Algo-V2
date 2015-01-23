#ifndef B_TREE
#define B_TREE

#include <new>

template <typename K, typename V>
struct BTreeNode
{
	BTreeNode(K key, V& val)
	{
		this->key = key;
		this->val = val;
		this->pLeft = this->pRight = NULL;
	}

	K key;
	V val;
	BTreeNode * pLeft;
	BTreeNode * pRight;
};

template <typename K, typename V>
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

	bool Insert(K key, V& val)
	{
		if (IsEmpty())
		{
			this->root = new (std::nothrow) BTreeNode<K,V>(key, val);
			return this->root ? true : false;
		}

		return Insert(key, val, this->root);
	}

	V * Find(K key)
	{
		if (IsEmpty())
			return NULL;
		BTreeNode<K,V> * parrent = NULL;
		return &((Find(key, this->root, parrent))->val);
	}

	V * Remove(K key)
	{
		return this->Remove(key, this->root);
	}

private:
	bool Insert(K key, V& val, BTreeNode<K,V> * node)
	{
		if (key > node->key)
		{
			if (node->pRight)
			{
				return Insert(key, val, node->pRight);
			}
			else
			{
				node->pRight = new (std::nothrow) BTreeNode<K,V>(key, val);
				return node->pRight ? true : false;
			}
		}
		else if (key < node->key)
		{
			if (node->pLeft)
			{
				return Insert(key, val, node->pLeft);
			}
			else
			{
				node->pLeft = new (std::nothrow) BTreeNode<K,V>(key, val);
				return node->pLeft ? true : false;
			}
		}
		else
		{
			node->val = val;
			return true;
		}
	}

	BTreeNode<K, V> * Find(K key, BTreeNode<K, V> * node, BTreeNode<K, V> * &parrent)
	{
		if (!node)
			return NULL;
		if (key == node->key)
			return node;
		else
		{
			parrent = node;
			return Find(key, key > node->key ? node->pRight : node->pLeft, node);
		}
	}

	V * Remove(K key, BTreeNode<K,V> * tree)
	{
		if (!tree)
			return NULL;

		BTreeNode<K,V> * parrent = NULL;
		BTreeNode<K,V> * nodeForDel = Find(key, this->root, parrent);
		if (!nodeForDel)
			return NULL;

		//two children
		if (nodeForDel->pLeft && nodeForDel->pRight)
		{
			BTreeNode<K,V> * tmp = this->FindMin(nodeForDel->pRight);
			nodeForDel->val = tmp->val;
			nodeForDel->key = tmp->key;
			return this->Remove(tmp->key, tmp->pLeft);
		}

		//0 or 1 child
		else
		{
			BTreeNode<K,V> ** ptrForChange = NULL;
			if (nodeForDel == this->root)
				ptrForChange = &this->root;
			else
				ptrForChange = parrent->val >= nodeForDel->val ? &parrent->pLeft : &parrent->pRight;
			*ptrForChange = nodeForDel->pLeft ? nodeForDel->pLeft : nodeForDel->pRight;
			delete nodeForDel;
		}

		return NULL;
	}

	bool IsEmpty()
	{
		return !root;
	}

	void CleanUp(BTreeNode<K,V> * node)
	{
		if (node != NULL)
		{
			CleanUp(node->pLeft);
			CleanUp(node->pRight);
			delete node;
		}
	}

	BTreeNode<K,V> * FindMin(BTreeNode<K,V> * node)
	{
		while (node->pLeft)
		{
			node = node->pLeft;
		}
		return node;
	}

	BTreeNode<K,V> * root;
};

#endif //B_TREE
