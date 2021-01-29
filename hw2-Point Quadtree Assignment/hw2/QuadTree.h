#ifndef QUAD_TREE_H
#define QUAD_TREE_H
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

struct binarynode
{
	binarynode * NW;
	binarynode * NE;
	binarynode * SW;
	binarynode * SE;
	int xcoord;
	int ycoord;
	string name;
	binarynode()
	{
		NW = nullptr;
		NE = nullptr;
		SW = nullptr;
		SE = nullptr;
	}
};

class QuadTree{
public:
	QuadTree();
	~QuadTree();
	void pretty_print();
	void find(int x, int y, int r);
	void setcoord(int x,int y);
	bool isEmpty();
	void makeEmpty();
	void insert(binarynode * ptr);
	void queries_print();
private:
	binarynode * root;
	int xx,yy;
	vector<string> found_cities;
	vector<string> visited;
	//const ITEM_NOT_FOUND; ? i dont get it
	void insert(binarynode * ptr,binarynode * t);
	void makeEmpty(binarynode * t);
	void pretty_print(binarynode * t);
	void find(binarynode * f,int x, int y, int r);
	void add2end(binarynode * ptr,binarynode * r, string quadrant);
	binarynode * Son(binarynode*ptr, string direction);
	string compare(binarynode * ptr, binarynode * father);
	binarynode * clone(binarynode * t) const;
};
#endif