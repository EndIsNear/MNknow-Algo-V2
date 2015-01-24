#ifndef SKIP_LIST
#define SKIP_LIST

#include <time.h>

#define MAX_SKIP_LIST_HEIGHT 32

template <typename K, typename V>
struct SListNode 
{
	SListNode(K _key, V& _val, unsigned _height = MAX_SKIP_LIST_HEIGHT) : key(_key), val(_val), height(_height)
	{
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
		{
			level[i] =  NULL;
		}
	}
	K key;
	V val;
	SListNode<K, V> * level[MAX_SKIP_LIST_HEIGHT];
	unsigned height;
};



template <typename K, typename V>
class SkipList
{
public:
	SkipList(K _minKey,K _maxKey)
	{
		V tmp = V();
		this->pHead = new SListNode<K,V>(_minKey, tmp);
		this->pTail = new SListNode<K,V>(_maxKey, tmp);
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
		{
			this->pHead->level[i] = this->pTail;
			this->pTail->level[i] = NULL;
		}
		srand((unsigned)time(NULL));
	}
	~SkipList()
	{
		SListNode<K,V> * it = this->pHead, * tmp;
		while (it)
		{
			tmp = it;
			it = it->level[0];
			delete tmp;
		}
	}

	bool Insert(K key, V& val)
	{
		SListNode<K,V> * it = this->pHead;
		SListNode<K, V> * forUpdate[MAX_SKIP_LIST_HEIGHT];
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
			forUpdate[i] = this->pHead;

		for (int i = MAX_SKIP_LIST_HEIGHT - 1; i >= 0; --i)
		{
			while (it->level[i]->key < key)
				it = it->level[i];

			forUpdate[i] = it;
		}


		unsigned tmpHeight = this->GetHeight();
		SListNode<K, V> * tmp = new (std::nothrow) SListNode<K,V>(key, val, tmpHeight);
		if (!tmp)
			return false;

		for (unsigned i = 0; i < tmpHeight; ++i)
		{
			tmp->level[i] = forUpdate[i]->level[i];
			forUpdate[i]->level[i] = tmp;
		}
//		std::cout << "Inserted " << val << " with height " << tmpHeight << std::endl;
		return true;
	}
	
	V * Find(K key)
	{
		if (this->IsEmpty())
			return NULL;

		SListNode<K,V> * it = this->pHead;
		for (int i = MAX_SKIP_LIST_HEIGHT - 1; i >= 0; --i)
		{
			while (it->level[i]->key < key)
				it = it->level[i];
		}
		if (it->level[0]->key == key)
			return &(it->level[0]->val);
		else
			return NULL;
	}

	void Remove(K key)
	{
		if (this->IsEmpty())
			return;
		SListNode<K,V> * it = this->pHead;
		SListNode<K, V> * forUpdate[MAX_SKIP_LIST_HEIGHT];
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
			forUpdate[i] = this->pHead;

		for (int i = MAX_SKIP_LIST_HEIGHT - 1; i >= 0; --i)
		{
			while (it->level[i]->key < key)
				it = it->level[i];

			forUpdate[i] = it;
		}
		if (it->level[0]->key == key)
		{
			it = it->level[0];
			for (int i = 0; i < MAX_SKIP_LIST_HEIGHT && forUpdate[i]->level[i] == it; ++i)
			{
				forUpdate[i]->level[i] = it->level[i];
			}
			delete it;
		}
	}

	bool IsEmpty()
	{
		return this->pHead->level[0] == this->pTail;
	}

private:
	SListNode<K,V> * pHead;
	SListNode<K,V> * pTail;
	//unsigned crnHeight;

	unsigned GetHeight()
	{
		unsigned res = 1;
		while ((rand() % 2 == 1) && res < MAX_SKIP_LIST_HEIGHT)
			res++;
		return res;
	}
};

#endif //SKIP_LIST
