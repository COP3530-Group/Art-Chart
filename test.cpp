// Testing without graphics

#include <vector>
#include <chrono>
#include "Parser.h"
#include "RadixSort.h"
#include "HeapSort.h"
#include "Piece.h"

using namespace std;

int main()
{
	vector<Piece> gallery;

	gallery = parseDataset(600000);
	cout << "Gallery size after parsing 600,000 entries: " << gallery.size() << endl;
	
	vector<Piece> gallery2 = gallery; // Make a copy of gallery so that we can sort it 2 ways and compare the execution times of quick and heap sort
	
	// Radix sort
	auto rstart = std::chrono::high_resolution_clock::now();
	gallery = radixSort(gallery, 10);
	auto rstop = std::chrono::high_resolution_clock::now();
	auto rduration = std::chrono::duration_cast<std::chrono::microseconds>(rstop-rstart);

	// Heap sort
	auto hstart = std::chrono::high_resolution_clock::now();
	gallery2 = heapSort(gallery2);

	for (int i = 1; i < gallery2.size(); i++)
	{
		cout << gallery2[i].value << endl;
		if (gallery2[i].value < gallery[i - 1].value)
		{
			cout << "not sorted" << endl;
			break;
		}

	}

	auto hstop = std::chrono::high_resolution_clock::now();
	auto hduration = std::chrono::duration_cast<std::chrono::microseconds>(hstop-hstart);

	cout << gallery.size() << " elements sorted in " << rduration.count() << " microseconds using radix sort" << endl;
	cout << gallery2.size() << " elements sorted in " << hduration.count() << " microseconds using heap sort" << endl;

	return 0;
}