#include <chrono>
#include <iostream>
#include "Splay.hpp"
#include "AVL.hpp"

void fillTestArrWithRand(unsigned * arr, unsigned size)
{
	srand((unsigned)time(NULL));
	for (unsigned i = 0; i < size; ++i)
	{
		arr[i] = rand();
	}
}

void TestSplay(unsigned * arr, unsigned size, unsigned minIdx, unsigned maxIdx)
{
	std::chrono::duration<double> InputDur;
	std::chrono::duration<double> SearchDur;
	Splay<unsigned, unsigned> splay;

	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

	for (unsigned k = 0; k < size; ++k)
	{
		splay.Insert(arr[k], arr[k]);
	}

	InputDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);
	startTime = std::chrono::high_resolution_clock::now();

	int idx = 0;
	unsigned tests = size * 128;
	for (unsigned k = 0; k < tests; ++k)
	{
		idx = rand() % maxIdx + minIdx;
		splay.Find(arr[idx]);
	}

	SearchDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);

	std::cout << "Biniri tree:" << std::endl;
	std::cout << "Insert " << size << " elements: ~" << InputDur.count() << " seconds." << std::endl;
	std::cout << "Find " << size << " elements ~" << SearchDur.count() << " seconds." << std::endl;
}

void TestAVLTree(unsigned * arr, unsigned size, unsigned minIdx, unsigned maxIdx)
{
	std::chrono::duration<double> InputDur;
	std::chrono::duration<double> SearchDur;
	AVLTree<unsigned, unsigned> AVL;

	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

	for (unsigned k = 0; k < size; ++k)
	{
		AVL.Insert(arr[k], arr[k]);
	}

	InputDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);
	startTime = std::chrono::high_resolution_clock::now();

	int idx = 0;
	unsigned tests = size * 128;
	for (unsigned k = 0; k < tests; ++k)
	{
		idx = rand() % maxIdx + minIdx;
		AVL.Find(arr[idx]);
	}

	SearchDur = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);

	std::cout << "Skip list:" << std::endl;
	std::cout << "Insert " << size << " elements: ~" << InputDur.count() << " seconds." << std::endl;
	std::cout << "Find " << size << " elements ~" << SearchDur.count() << " seconds." << std::endl;
}

void Test(unsigned testLen)
{
	unsigned * arr = new unsigned[testLen];
	if (!arr)
		exit(-1);

	fillTestArrWithRand(arr, testLen);
	std::cout << "Test with random search." << std::endl;
	std::cout << "=======================" << std::endl;
	TestAVLTree(arr, testLen, 0, testLen);
	TestSplay(arr, testLen, 0, testLen);
	std::cout << "=======================" << std::endl;

	std::cout << "Search only 128 elements." << std::endl;
	std::cout << "=======================" << std::endl;
	unsigned startIdx = rand() % (testLen - 128);
	TestAVLTree(arr, testLen, startIdx, startIdx + 128);
	TestSplay(arr, testLen, startIdx, testLen);
	std::cout << "=======================" << std::endl;

	std::cout << "Search only 64 elements." << std::endl;
	std::cout << "=======================" << std::endl;
	startIdx = rand() % (testLen - 64);
	TestAVLTree(arr, testLen, startIdx, startIdx + 64);
	TestSplay(arr, testLen, startIdx, testLen);
	std::cout << "=======================" << std::endl;

	std::cout << "Test only 16 elements." << std::endl;
	std::cout << "=======================" << std::endl;
	startIdx = rand() % (testLen - 16);
	TestAVLTree(arr, testLen, startIdx, startIdx + 16);
	TestSplay(arr, testLen, startIdx, startIdx + 16);
	std::cout << "=======================" << std::endl;


	delete[] arr;
}

int main()
{
	const unsigned testLen = 2048;
	Test(testLen);
	return 0;
}
