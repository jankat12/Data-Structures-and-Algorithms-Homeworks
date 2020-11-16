#include "my_heap.h"
#include <string>
#include <iostream>


using namespace std;

My_heap::My_heap()
{
	heap_begin = nullptr;
	blk = nullptr;
	used_bytes = 0;
}

My_heap::~My_heap()
{
	memory_block * ptr = heap_begin;
	int leak = 0;
	while (heap_begin != nullptr)
	{
		if (heap_begin->used == true)
		{
			leak += heap_begin->size;
		}
		ptr=ptr->right;
		delete heap_begin;
		heap_begin = ptr;
	}
	cout << "At destruction, the heap had a memory leak of " << leak << " bytes" << endl;
}

memory_block*My_heap::bump_allocate(int num_bytes)
{
	if (heap_begin == nullptr) // if the heap is empty
	{
		memory_block*block = new memory_block();
		block->size = num_bytes;
		block->used = true;
		block->starting_address = 0;  // since its the first block
		block->finishing_adress = num_bytes; // its the first block so its finishing adress is its size.
		block->right = nullptr;
		block->left = nullptr;
		blk = block; 
		heap_begin = block; // both blk and heap_begin points to this block since its the only one.
		used_bytes += num_bytes;
		return block;
	}
	else if (used_bytes + num_bytes > MAX_CAPACITY)
	{
		return nullptr; // we return nullptr because there is not enough memory.
	}
	else
	{
		memory_block * block = new memory_block();
		block->size = num_bytes;
		block->used=true;
		memory_block * tracker = heap_begin;
		while (tracker->right != nullptr)
		{
			tracker = tracker->right;
		}
		tracker->right = block;
		block->starting_address = tracker->finishing_adress;
		block->left = tracker;
		block->finishing_adress = block->starting_address + num_bytes;
		block->right = nullptr;
		blk = block;
		used_bytes += num_bytes;
		return block;
	}
}

memory_block*My_heap::first_fit_allocate(int num_bytes)
{
	if (heap_begin == nullptr) // if there is no block in the heap.
	{
		return bump_allocate(num_bytes);
	}
	else
	{
		if (used_bytes + num_bytes > MAX_CAPACITY) // return null if there is not enough memory
		{
			return nullptr;
		}
		else
		{
			memory_block* ptr = heap_begin;
			bool found = false; // going to be true if we find a suitable block
			while (ptr != nullptr)
			{
				if (ptr->used == false && ptr->size >= num_bytes)
				{
					found = true;
					break; // we break because  this function allocates the first found block.
				}
				ptr = ptr->right;
			}
			if (found == true) // if we found it
			{
				ptr->used = true;
				return ptr;
			}
			if (found == false) // if there is no suitable block, we add new one to the end.
			{
				return bump_allocate(num_bytes);
			}
		}
	}
}

memory_block*My_heap::best_fit_allocate(int num_bytes)
{
	if (heap_begin == nullptr)
	{
		return bump_allocate(num_bytes);
	}
	else
	{
		memory_block*tracker;
		memory_block*tobeadded;
		int diff = -1; // -1 is the default value for now.
		tracker = heap_begin;
		while (tracker != nullptr)
		{
			if (tracker->used == false && tracker->size >= num_bytes)
			{
				if (diff == -1 || tracker->size-num_bytes < diff) // if we check for the first time (-1 default value) or if the difference is less its better fit.
				{
					tobeadded = tracker;
					diff = tobeadded->size - num_bytes; 
				}
			}
			tracker = tracker->right;
		}
		if (diff == -1) // which means there was no suitable memory block.
		{
			return bump_allocate(num_bytes);
		}
		else
		{
			tobeadded->used = true;
			return tobeadded;
		}
	}
}

memory_block*My_heap::first_fit_split_allocate(int num_bytes)
{
	if (heap_begin == nullptr)
	{
		return bump_allocate(num_bytes);
	}
	else
	{
		memory_block * ptr = heap_begin;
		bool found = false; // going to be true if we find a suitable block
		while (ptr != nullptr)
		{
			if (ptr->used == false && ptr->size >= num_bytes)
			{
				found = true;
				break; // we break because  this function allocates the first found block.
			}
			ptr=ptr->right;
		}
		if (found == true) // if we found it
		{
			if (ptr->size == num_bytes)
			{
				ptr->used;
				return ptr;
			}
			else
			{
				memory_block * newfreeblk = new memory_block();
				newfreeblk->size = ptr->size - num_bytes;
				if (ptr->right != nullptr) // if the ptr is the blk.
				{
					newfreeblk->right = ptr->right;
					ptr->right->left = newfreeblk;
				}
				else
				{
					newfreeblk->right = nullptr;
				}
				ptr->right = newfreeblk; // initializations of both newfreeblock and ptr.
				newfreeblk->left = ptr;
				ptr->finishing_adress = ptr->finishing_adress - (ptr->size - num_bytes);
				newfreeblk->starting_address = ptr->finishing_adress;
				newfreeblk->finishing_adress = newfreeblk->starting_address + newfreeblk->size;
				newfreeblk->used = false;
				ptr->size = num_bytes;
				ptr->used = true;
			}
		}
		if (found == false) // if there is no suitable block, we add new one to the end.
		{
			return bump_allocate(num_bytes);
		}
	}
}

void My_heap::deallocate(memory_block* block_address)
{
	used_bytes = used_bytes - block_address->size;
	if (block_address->left == nullptr && block_address ->right == nullptr)
	{
		block_address->used = false; // if its the only block
	}
	else if (block_address == heap_begin)
	{		
		if (block_address->right->used == false) // in case the right block is a free block.
		{	
			memory_block * rightptr = block_address->right;
			block_address->size += rightptr->size;
			block_address->finishing_adress = rightptr->finishing_adress; // initialize finishing adress of right because it comes last when we merge.
			if (rightptr->right != nullptr)  // making right connections before combining.
			{			
				block_address->right->right->left = block_address;
				block_address->right = block_address->right->right;
			}
			else
			{
				block_address->right = nullptr;
				blk = block_address; // since there is no block at right, it makes it the blk.
			}
			delete rightptr;
			
		}
		block_address->used = false;
	}
	else if (block_address == blk)
	{
		memory_block * leftptr = block_address->left;
		if (block_address->left->used == false) // in case the left block is a free block.
		{			
			block_address->size += leftptr->size;
			block_address->starting_address = leftptr->starting_address; // initialize starting adress of left because it comes first when we merge.
			if (leftptr->left != nullptr) 
			{
				leftptr->left->right = block_address; // connecting the left pointer before combining 
				block_address->left = leftptr->left;			
			}
			else
			{
				block_address->left = nullptr;
				heap_begin = block_address; // since there is no block at left, it makes this the heap_begin.
			}
			delete leftptr;			
		}
		block_address->used = false;
	}
	else if (block_address->left->used == false && block_address->right == false) // in case if block is in between two used=false blocks.
	{
		memory_block * leftptr = block_address->left;
		memory_block * rightptr = block_address->right;
		block_address->size += block_address->right->size + block_address->left->size; // adding the sizes of the blocks.
		block_address->starting_address = leftptr->starting_address; // initialize starting adress of left because it comes first when we merge.
		block_address->finishing_adress = rightptr->finishing_adress; // initialize finishing adress of right because it comes last when we merge.
		if (leftptr->left != nullptr) 
		{
			leftptr->left->right = block_address; // connecting the left pointer before combining 
			block_address->left = leftptr->left;			
		}
		else
		{
			block_address->left = nullptr;
			heap_begin = block_address; // since there is no block at left, it makes this the heap_begin.
		}
		if (rightptr->right != nullptr)  // making right connections before combining.
		{			
			block_address->right->right->left = block_address;
			block_address->right = block_address->right->right;
		}
		else
		{
			block_address->right = nullptr;
			blk = block_address; // since there is no block at right, it makes it the blk.
		}
		delete leftptr;
		delete rightptr;
		block_address->used = false;
	}
	else if (block_address->left->used == false) // in case the left block is a free block.
	{
		memory_block * leftptr = block_address->left;
		block_address->size += leftptr->size;
		block_address->starting_address = leftptr->starting_address; // initialize starting adress of left because it comes first when we merge.
		if (leftptr->left != nullptr) 
		{
			leftptr->left->right = block_address; // connecting the left pointer before combining 
			block_address->left = leftptr->left;			
		}
		else
		{
			block_address->left = nullptr;
			heap_begin = block_address; // since there is no block at left, it makes this the heap_begin.
		}
		delete leftptr;
		block_address->used = false;
	}
	else if (block_address->right->used == false) // in case the right block is a free block.
	{
		memory_block * rightptr = block_address->right;
		block_address->size += rightptr->size;
		block_address->finishing_adress = rightptr->finishing_adress; // initialize finishing adress of right because it comes last when we merge.
		if (rightptr->right != nullptr)  // making right connections before combining.
		{			
			block_address->right->right->left = block_address;
			block_address->right = block_address->right->right;
		}
		else
		{
			block_address->right = nullptr;
			blk = block_address; // since there is no block at right, it makes it the blk.
		}
		delete rightptr;
		block_address->used = false;
	}
	else // if there is no free memory around it
	{
		block_address->used = false;
	}
}

void My_heap::print_heap()
{
	memory_block*tracker = heap_begin;
	int usedmemory = 0;
	int totalblocks = 0;
	int totalusedblocks = 0;
	int totalfreeblocks = 0;
	while (tracker != nullptr)
	{
		totalblocks ++;
		if (tracker->used == true)
		{
			totalusedblocks ++;
			usedmemory += tracker->size;
		}
		if (tracker->used == false)
		{
			totalfreeblocks ++;
		}
		tracker = tracker->right;
	}
	cout << "Maximum capacity of heap: 512B\nCurrently used memory: (B): " << usedmemory << "\nTotal memory blocks: " << totalblocks <<
		"\nTotal used memory blocks: "<< totalusedblocks << "\nTotal free memory blocks: " << totalfreeblocks <<
		"\nFragmentation: " << get_fragmantation() << "%\n------------------------------\n";
	tracker = heap_begin;
	int counter = 0;
	while (tracker != nullptr)
	{
		string usedd;
		if (tracker->used)
		{
			usedd = "True";
		}
		else
		{
			usedd = "False";
		}
		
		cout << "Block " << counter <<"\t\tUsed: " << usedd << "\tSize (B): " << tracker->size << "\tStarting Adress: 0x"<<
			hex << tracker->starting_address << dec << endl;
		tracker = tracker->right;
		counter++;
	}
	cout << "------------------------------\n------------------------------" << endl;
}

float My_heap::get_fragmantation()
{
	int totalfreememory = MAX_CAPACITY;
	float defaultfreeblock = 512; // whole heap is one block when nothing initialized. (default)
	float biggestfreeblock = 0;
	memory_block*tracker = heap_begin;
	while (tracker != nullptr)
	{
		defaultfreeblock = defaultfreeblock - tracker->size;
		if (tracker->used == false)
		{			
			if (biggestfreeblock < tracker->size)
			{
				biggestfreeblock = tracker->size;
			}
		}
		if (tracker->used == true)
		{
			totalfreememory -= tracker->size;
		}
		tracker=tracker->right;
	}
	if (biggestfreeblock < defaultfreeblock) // if there is no block is bigger than the default setted one, we set biggestfreeblock to default.
	{
		biggestfreeblock = defaultfreeblock;
	}
	float frag = 100*(totalfreememory - biggestfreeblock)/totalfreememory;
	return frag;
}
