#ifndef SKIP_LIST
#define SKIP_LIST

#include <time.h>

#define MAX_SKIP_LIST_HEIGHT 32

template <typename T>
struct SListNode 
{
	SListNode(T& _val, unsigned _height) : val(_val), height(_height)
	{
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
		{
			level[i] =  NULL;
		}
	}
	T val;
	SListNode<T> * level[MAX_SKIP_LIST_HEIGHT];
	unsigned height;
};



template <typename T>
class SkipList
{
public:
	SkipList(T _minVal,T _maxVal)
	{
		this->pHead = new SListNode<T>(_minVal, MAX_SKIP_LIST_HEIGHT);
		this->pTail = new SListNode<T>(_maxVal, MAX_SKIP_LIST_HEIGHT);
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
		{
			this->pHead->level[i] = this->pTail;
			this->pTail->level[i] = NULL;
		}
		srand(time(NULL));
	}
	~SkipList()
	{
		SListNode<T> * it = this->pHead, * tmp;
		while (it)
		{
			tmp = it;
			it = it->level[0];
			delete tmp;
		}
	}

	bool Insert(T& val)
	{
		SListNode<T> * it = this->pHead;
		SListNode<T> * forUpdate[MAX_SKIP_LIST_HEIGHT];
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
			forUpdate[i] = this->pHead;

		for (int i = MAX_SKIP_LIST_HEIGHT - 1; i >= 0; --i)
		{
			while (it->level[i]->val < val)
				it = it->level[i];

			forUpdate[i] = it;
		}


		unsigned tmpHeight = this->GetHeight();
		SListNode<T> * tmp = new (std::nothrow) SListNode<T>(val, tmpHeight);
		if (!tmp)
			return false;

		for (unsigned i = 0; i < tmpHeight; ++i)
		{
			tmp->level[i] = forUpdate[i]->level[i];
			forUpdate[i]->level[i] = tmp;
		}
		std::cout << "Inserted " << val << " with height " << tmpHeight << std::endl;
		return true;
	}
	
	SListNode<T> * Find(T& val)
	{
		SListNode<T> * it = this->pHead;
		for (int i = MAX_SKIP_LIST_HEIGHT - 1; i >= 0; --i)
		{
			while (it->level[i]->val < val)
				it = it->level[i];
		}
		if (it->level[0]->val == val)
			return it->level[0];
		else
			return NULL;
	}

	void Remove(T& val)
	{
		SListNode<T> * it = this->pHead;
		SListNode<T> * forUpdate[MAX_SKIP_LIST_HEIGHT];
		for (unsigned i = 0; i < MAX_SKIP_LIST_HEIGHT; ++i)
			forUpdate[i] = this->pHead;

		for (int i = MAX_SKIP_LIST_HEIGHT - 1; i >= 0; --i)
		{
			while (it->level[i]->val < val)
				it = it->level[i];

			forUpdate[i] = it;
		}
		if (it->level[0]->val == val)
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
		return this->pHead.level[0] == this->pTail;
	}

private:
	SListNode<T> * pHead;
	SListNode<T> * pTail;
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
