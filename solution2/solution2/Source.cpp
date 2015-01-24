#include <iostream>
#include <cstdlib>
#include <chrono>

#include "BTree.hpp"
#include "SkipList.hpp"

void fillTestArrWithRand(unsigned * arr, unsigned size)
{
	srand((unsigned)time(NULL));
	for (unsigned i = 0; i < size; ++i)
	{
		arr[i] = rand();
	}
}

void fillTestArrWithSort(unsigned * arr, unsigned size)
{
	for (unsigned i = 0; i < size; ++i)
	{
		arr[i] = i;
	}
}


void fillTestArrWithAlmostSort(unsigned * arr, unsigned size, unsigned swaps)
{
	fillTestArrWithSort(arr, size);
	for (unsigned i = 0; i < swaps; ++i)
	{
		std::swap(arr[rand() / size], arr[rand() / size]);
	}
}

void TestBinTree(unsigned * arr, unsigned size)
{
	std::chrono::duration<double> InputDur;
	std::chrono::duration<double> SearchDur;
	BinaryTree<unsigned, unsigned> bTree;

	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

	for (unsigned k = 0; k < size; ++k)
	{
		bTree.Insert(arr[k], arr[k]);
	}

	InputDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);
	startTime = std::chrono::high_resolution_clock::now();

	for (unsigned k = 0; k < size; ++k)
	{
		bTree.Find(arr[k]);
	}

	SearchDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);

	std::cout << "Biniri tree:" << std::endl;
	std::cout << "Insert " << size << " elements: ~" << InputDur.count() << " seconds." << std::endl;
	std::cout << "Find " << size << " elements ~" << SearchDur.count() << " seconds." << std::endl;
}

void TestSkipList(unsigned * arr, unsigned size)
{
	const unsigned tests = 5;
	std::chrono::duration<double> InputDur;
	std::chrono::duration<double> SearchDur;
	SkipList<unsigned, unsigned> sList(0, unsigned() - 1);

	for (unsigned i = 0; i < tests; ++i)
	{
		std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

		for (unsigned k = 0; k < size; ++k)
		{
			sList.Insert(arr[k], arr[k]);
		}

		InputDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);
		startTime = std::chrono::high_resolution_clock::now();

		for (unsigned k = 0; k < size; ++k)
		{
			sList.Find(arr[k]);
		}

		SearchDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);
	}
	InputDur /= tests;
	SearchDur /= tests;

	std::cout << "Skip list:" << std::endl;
	std::cout << "Insert " << size << " elements: ~" << InputDur.count() << " seconds." << std::endl;
	std::cout << "Find " << size << " elements ~" << SearchDur.count() << " seconds." << std::endl;
}

void Test(unsigned testLen)
{
	unsigned * arr = new unsigned[testLen];
	if (!arr)
		exit(-1);

	std::cout << "Test with random array." << std::endl;
	std::cout << "=======================" << std::endl;
	fillTestArrWithRand(arr, testLen);
	TestSkipList(arr, testLen);
	TestBinTree(arr, testLen);
	std::cout << "=======================" << std::endl;

	std::cout << "Test with sorted array." << std::endl;
	std::cout << "=======================" << std::endl;
	fillTestArrWithSort(arr, testLen);
	TestSkipList(arr, testLen);
	TestBinTree(arr, testLen);
	std::cout << "=======================" << std::endl;

	const unsigned swaps = testLen / 100;
	std::cout << "Test with almost sorted array." << std::endl;
	std::cout << "=======================" << std::endl;
	fillTestArrWithAlmostSort(arr, testLen, swaps);
	TestSkipList(arr, testLen);
	TestBinTree(arr, testLen);
	std::cout << "=======================" << std::endl;

	delete[] arr;
}

int main()
{
	const unsigned testLen = 4096 * 8;
	Test(testLen);
	return 0;
}
