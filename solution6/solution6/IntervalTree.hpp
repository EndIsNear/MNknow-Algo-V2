#ifndef INTERVAL_TREE_HPP
#define INTERVAL_TREE_HPP

#include <vector>
#include <algorithm>

template <typename K, typename V>
struct Interval
{
	Interval(K s, K e, V v) : start(s), end(e), val(v){}

	bool IsInside(K key)
	{
		return key >= this->start && key <= this->end;
	}

	K start, end;
	V val;
};

template <typename K, typename V>
struct ITNode
{
	ITNode(K c) : center(c)
	{
		pLeft = pRight = NULL;
	}

	void AddInterval(Interval<K, V>& inter)
	{
		//TODO:should keep sortedByStart sortedByEnd up to date
		this->intervals.push_back(inter);
	}

	void RemoveIntervals(K st, K end)
	{
		//TODO:should keep sortedByStart sortedByEnd up to date
		size_t size = this->intervals.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (intervals[i].start == st && intervals[i].end == end)
			{
				this->intervals.erase(this->intervals.begin() + i);
				i--;
				size--;
			}
		}
	}

	void RemoveInterval(Interval<K, V>& inter)
	{
		//TODO:should keep sortedByStart sortedByEnd up to date
		size_t size = this->intervals.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (intervals[i] == inter)
			{
				this->intervals.erase(this->intervals.begin() + i);
				break;
			}
		}
	}

	bool SearchForDot(K dot, std::vector<Interval<K, V>>& res)
	{
		//TODO: optimize with sorted vectors
		bool found = false;
		for (auto it = this->intervals.begin(); it != this->intervals.end(); ++it)
		{
			if (it->IsInside(dot))
			{
				res.push_back(*it);
				found = true;
			}
		}
		return found;
	}

	std::vector<Interval<K,V>> intervals;
	//TODO: add sorted by begin and end vectors
	//std::vector<Interval<K, V>*> sortedByStart;
	//std::vector<Interval<K, V>*> sortedByEnd;
	K center;
	ITNode<K, V> *pLeft, *pRight;
};

template <typename K, typename V>
class ITree
{
public:
	ITree() = delete;
	~ITree()
	{
		CleanUp(this->root);
	}

	ITree(K min, K max) : minimum(min), maximum(max)
	{
		this->root = new ITNode<K,V>((max - min) / 2 + min);
	}

	ITree(std::vector<Interval<K, V>>& intervals)
	{
		std::sort(intervals.begin(), intervals.end(),
			[](const Interval<K,V>& left, const Interval<K,V>& right)
			{
				return left.start < right.start;
			});

		K min = intervals[0].start, max = intervals[0].end;
		size_t size = intervals.size();
		for (unsigned i = 0; i < size; ++i)
		{
			min = min > intervals[i].start ? intervals[i].start : min;
			max = max < intervals[i].end ? intervals[i].end : max;
		}

		this->minimum = min;
		this->maximum = max;


		this->root = BuildFromSortedIntervals(intervals, min, max);
	}

	bool Insert(K st, K end, V val)
	{
		if (st < this->minimum || end > this->maximum)
			return false;
		Interval<K, V> tmp(st, end, val);
		ITNode<K, V> * it = this->root;
		ITNode<K, V> * parrent = this->root;
		bool rdy = false;
		while (!rdy && it)
		{
			if (tmp.IsInside(it->center))
			{
				it->AddInterval(tmp);
				rdy = true;
			}
			else
			{
				parrent = it;
				it = it->center > tmp.end ? it->pLeft : it->pRight;
			}
		}

		if (!rdy)
		{
			std::vector<Interval<K, V>> tmpVec;
			tmpVec.push_back(tmp);
			if (parrent->center > tmp.end)
			{
				parrent->pLeft = BuildFromSortedIntervals(tmpVec, this->minimum, parrent->center);
			}
			else
			{
				parrent->pRight = BuildFromSortedIntervals(tmpVec, parrent->center, this->maximum);
			}
		}
		return true;
	}

	///push_back all the results
	bool SearchDot(K dot, std::vector<Interval<K, V>>& res)
	{
		if (dot < this->minimum || dot > this->maximum)
			return false;
		ITNode<K, V> * it = this->root;
		bool found = false;
		while (it)
		{
			found = it->SearchForDot(dot, res);
			it = dot < it->center ? it->pLeft : it->pRight;
		}
		return found;
	}

	void Remove(K st, K end)
	{
		Interval<K, V> tmp(st, end, K());
		ITNode<K, V> * it = this->root;
		while (it && !tmp.IsInside(it->center))
		{
			it = it->center > end ? it->pLeft : it->pRight;
		}
		if (it)
			it->RemoveIntervals(st, end);
	}

	void Remove(Interval<K, V>& inter)
	{
		ITNode<K, V> * it = this->root;
		while (it && !inter.IsInside(it->center))
		{
			it = it->center > end ? it->pLeft : it->pRight;
		}
		if (it)
			it->RemoveInterval(st, end);
	}

private:
	ITNode<K, V> * root;
	K minimum, maximum;

	ITNode<K, V> * BuildFromSortedIntervals(std::vector<Interval<K, V>>& intervals, K min, K max)
	{
		size_t size = intervals.size();
		if (!size || intervals[0].start > max)
			return NULL;
		K center = (max - min) / 2 + min;
		ITNode<K, V> * tmp = new (std::nothrow) ITNode<K, V>(center);
		if (!tmp)
			return tmp;
		for (unsigned i = 0; i < size && intervals[i].start <= center; ++i)
		{
			if (intervals[i].IsInside(center))
			{
				tmp->AddInterval(intervals[i]);
				intervals.erase(intervals.begin() + i);
				size--;
				i--;
			}
		}
		tmp->pLeft = BuildFromSortedIntervals(intervals, min, center);
		tmp->pRight = BuildFromSortedIntervals(intervals, center, max);
		return tmp;
	}


	void CleanUp(ITNode<K,V> * node)
	{
		if (node)
		{
			CleanUp(node->pLeft);
			CleanUp(node->pRight);
			delete node;
		}
	}
};



#endif //INTERVAL_TREE_HPP