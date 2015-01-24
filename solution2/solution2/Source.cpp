#include "BTree.hpp"
#include "SkipList.hpp"

#include <iostream>

int main()
{
	BinaryTree<int, int> tree;
	int asd[] = { 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5 };
	for (int i = 0; i <= 10; ++i)
		tree.Insert(asd[i]+1, asd[i]);
	tree.Remove(1);
	for (int i = 0; i <= 12; ++i)
	{
		if (auto res = tree.Find(i))
			std::cout << *(res) << std::endl;
		else
			std::cout << "NOT FOUND!" << std::endl;
	}
	return 0;
}

