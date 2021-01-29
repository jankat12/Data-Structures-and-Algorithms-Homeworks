#include "QuadTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Jankat Yasar CS-300 HW assignment 2.

using namespace std;

int main(){
	QuadTree mytree;
	string line,cities,queries;
	ifstream citiesinput;
	cities = "cities.txt";
	queries = "queries0.txt";
	citiesinput.open(cities.c_str());
	while (getline(citiesinput,line))
	{
		if (isalpha(line[0])) // to add only cities, not the first info of 100x100 etc
		{
			stringstream ss(line);
			binarynode * node = new binarynode();
			string word;
			int count = 0; // to keep track of which word we get.
			while (ss >> word)
			{
				if (count == 0)
				{
					node->name = word;
				}
				else if (count == 1)
				{
					int x = stoi(word);
					node->xcoord = x;
				}
				else if (count == 2)
				{
					int y = stoi(word);
					node->ycoord = y;
				}
				count ++;
			}
			mytree.insert(node);
		}
		else
		{
			stringstream ss(line);
			string xx,yy;
			while(ss >> xx >> yy)
			{
				int x = stoi(xx);
				int y = stoi(yy);
				mytree.setcoord(x,y);
			}
		}
	}
	citiesinput.close();
	mytree.pretty_print();
	ifstream queriesinput;
	queriesinput.open(queries.c_str());
	while (getline(queriesinput,line))
	{
		stringstream ss(line);
		string word;
		int count = 0;  // to keep track of which word we get.
		int x,y,r;
		while (ss >> word)
		{
			if (count == 0)
			{
				word = word.substr(0,word.find(','));
				x = stoi(word);
			}
			else if (count == 1)
			{
				word = word.substr(0,word.find(','));
				y = stoi(word);
			}
			else if (count == 2)
			{
				r = stoi(word);
			}
			count ++;
		}
		mytree.find(x,y,r);
		mytree.queries_print();
	}
	queriesinput.close();
	return 0;
}