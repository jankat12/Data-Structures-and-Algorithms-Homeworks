#include <iostream>
#include "PrioQueue.h"
#include <vector>
#include <fstream>
#include <sstream>

// JANKAT YASAR TAKEHOME EXAM 3 SKYLINE
using namespace std;

void shellSort(vector<listitem> & arr){
	int j;
	for (int gap = arr.size()/2; gap > 0; gap/= 2) // loop over increments
	{
		for (int i = gap; i < arr.size(); i++) // loop over elements
		{
			listitem temp = arr[i];
			for (j = i; j >= gap && temp.xcoord < arr[j-gap].xcoord; j-= gap)
			{
				arr[j] = arr[j-gap];
			}
			arr[j] = temp;
		}
	}
}

int main()
{
	vector<listitem> my_list; // this is the list where Im going to push the building and both of their x coordinates seperately
	vector<heapnode> values; // this will contain the values and the labels.
	//PrioQueue Heap;
	ifstream inputs;
	string line,inputname;
	inputname = "7.txt";
	inputs.open(inputname.c_str());
	bool firstline = true; // to check for just the first line
	int labelnum = 0; // this will increase by one as we read lines, so all buildings will have unique labelnum.
	int buildingnum = 0; // this will be the first line which tells us the total building number.
	while (getline(inputs,line))
	{
		if (firstline)
		{
			buildingnum = stoi(line); // if its first line, its the number of how many buildings there are			
			firstline = false;
		}
		else
		{
			stringstream ss(line);
			string word;
			int count = 0;
			int value = 0; // its the height variable
			listitem item;
			while (ss >> word)
			{
				if (count == 0) // this is the first num we read ( left x coord of the building)
				{
					item.xcoord = stoi(word);
					item.label = labelnum;
					item.xpos = "left";					
				} 
				else if (count == 1) // height of the building
				{
					value = stoi(word); // we get the height at the 2nd word of the line
					item.height = value;
					my_list.push_back(item); // we push it here because we need also the height value.
				}
				else if (count == 2) // this is the right x coord of the building
				{
					listitem item2;
					item2.xcoord = stoi(word);
					item2.label = labelnum;
					item2.xpos = "right";
					item2.height = value;
					my_list.push_back(item2); 
				}
				count++;
			}
			labelnum ++;
		}
	}
	shellSort(my_list); // we sort the list.
	PrioQueue Heap(buildingnum);
	int height = 0;
	int position = 0;
	for (int i = 0; i < my_list.size(); i++)
	{
		if (my_list[i].xpos == "left")
		{
			if (i == 0 && my_list[0].xcoord != 0) // if there is no building at the starting point of x = 0
			{
				cout << "0 0" << endl;
			}
			Heap.insert(my_list[i].height,my_list[i].label); // we insert because if we see the left side, we just begin to add it to the skyline.
			if (Heap.GetMax() > height) 
			{			
				if (my_list[i].xcoord == my_list[i+1].xcoord)
				{
					continue; //this statement is for the cases when there is same left x coordinates of buildings.So we wont print unless until we see the other ones.
				}
				height = Heap.GetMax();
				position = my_list[i].xcoord;
				cout << position << " " << height << endl;
			}
		}
		else if (my_list[i].xpos == "right") 
		{
			heapnode removed = Heap.Remove(my_list[i].label); // we remove because seeing the right x means that the building is over.
			if (Heap.GetMax() != height)
			{	
				if (i != my_list.size() -1) // this is for we dont go out of scope (in case mylist[i] is the last element)
				{
					if (my_list[i].xcoord == my_list[i+1].xcoord /*&& my_list[i+1].xpos == "left"*/)
					{
						if (my_list[i].height != my_list[i+1].height) // for the edge cases.
						{
							height = Heap.GetMax();
						}
						continue; // for the case that if there is a one building just start as the other one finishes
					}
				}
				height = Heap.GetMax();				
				position = my_list[i].xcoord;
				cout << position << " " << height << endl;
			}
		}
	}
	return 0;
}