#ifndef PrioQueue_H
#define PrioQueue_H
#include <string>
using namespace std;

struct listitem
{
	int label; // unique building id (kinda)
	int height;
	int xcoord;
	string xpos; // whether its left or right x coordinate
};

struct heapnode{
	int label;
	int height;
};


class PrioQueue{
private:
	heapnode * Heap; // dynamic array of MPQ
	int * Location; // dynamic array of locations
	int totalsize;
	int currentsize;
public:	
	PrioQueue(int size);
	~PrioQueue();
	void BuildHeap();	
	void insert(int value, int label);
	heapnode Remove(int label);
	int GetMax();
	bool IsEmpty();
};
#endif