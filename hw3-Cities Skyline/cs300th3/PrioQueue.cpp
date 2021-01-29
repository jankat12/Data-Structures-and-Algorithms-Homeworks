#include "PrioQueue.h"


PrioQueue::PrioQueue(int size){
	totalsize = size+1; // +1 for the dummy
	Heap = new heapnode[totalsize]; // The array which will contain labels and heights.
	Location = new int[totalsize]; // The array for finding elements of the Heap.
	BuildHeap();
	currentsize = 0; // Heap has no element at this point so its 0.
} 

PrioQueue::~PrioQueue()
{
	delete [] Heap; // deallocating memory.
	delete [] Location;
}

void PrioQueue::BuildHeap(){
	for (int i = 0; i < totalsize; i++)
	{
		Location[i] = -1; // giving them a default value of -1
	}	
}

void PrioQueue::insert(int value, int label)
{
	currentsize++;
	int hole = currentsize; // Since we are inserting, we will start at the end of the heap, so hole will be curentsize++
	heapnode node; // creating the Heap item with the given parameters.
	node.height = value;
	node.label = label;
	Heap[hole] = node; // insertion
	Location[label] = hole; // giving the value for the first time.
	while (hole > 1 && Heap[hole/2].height < value) // the swap operation for MaxHeap
	{
		int tmp = Location[Heap[hole].label];
		Location[Heap[hole].label] = Location[Heap[hole/2].label];
		Location[Heap[hole/2].label] = tmp;
		heapnode temp = Heap[hole];		
		Heap[hole] = Heap[hole/2];
		Heap[hole/2] = temp;
		hole /= 2;
	}	
	Location[label] = hole; // we are saving the location of the item with its label, so we can find it in O(1) time later.
}

int PrioQueue::GetMax(){
	if (IsEmpty())
	{
		return 0;
	}
	else
	{
		return Heap[1].height; // return the first element since its MaxHeap.
	}
}

bool PrioQueue::IsEmpty()
{
	if (currentsize == 0)
	{
		return true;
	}
	return false;
}

heapnode PrioQueue::Remove(int label){
	
	int index = Location[label]; // we get the index of the item with label, so we can proceed.
	Location[label] = -1; // there will ne no such label in the heap anymore, so define it with -1.
	heapnode tobereturned = Heap[index];
	Heap[index] = Heap[currentsize]; // move the last element to the item to be deleted, then we re gonna shrink array by one.
	heapnode temp = Heap[index];// element to be percolated down.
	int child;
	while (index <= currentsize && index*2 <= currentsize) // percolate down
	{
		child = index*2;
		if (child != currentsize && Heap[child+1].height > Heap[child].height) // to select which of the 2 childs are bigger, so we swap them.
		{
			child++;
		}
		if (Heap[child].height > temp.height)
		{
			Location[Heap[index].label] = Location[Heap[child].label]; // update the locations array to keep it ordered.
			Heap[index] = Heap[child]; // swap the element and the max child.
		}
		else
		{
			break;
		}
		index = child; // so that we can keep percolate down through the tree
	}
	currentsize--; // shrinking array
	Heap[index] = temp;
	Location[temp.label] = index; // we update the Location of the percolated element
	return tobereturned;
}