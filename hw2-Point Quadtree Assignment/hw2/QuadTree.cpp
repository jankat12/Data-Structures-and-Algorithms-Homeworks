#include "QuadTree.h"



QuadTree::QuadTree()
{
	root = NULL;
}

QuadTree::~QuadTree()
{
	makeEmpty();
}

bool QuadTree::isEmpty()
{
	if (root == nullptr)
	{
		return true;
	}
	return false;
}

void QuadTree::makeEmpty()
{
	makeEmpty(root);
}

void QuadTree::makeEmpty(binarynode * t)
{
	if (t != NULL)
	{
		makeEmpty(t->SE);
		makeEmpty(t->SW);
		makeEmpty(t->NE);
		makeEmpty(t->NW);
		delete t;
	}
	t = NULL;
}

void QuadTree::setcoord(int x,int y)
{
	xx = x;
	yy = y;
}

void QuadTree::queries_print()
{
	if (found_cities.empty())
	{
		cout << "<None>" << endl;
	}
	else
	{
		for (int i = 0; i < found_cities.size(); i++)
		{
			if (found_cities.size()-1 == i)
			{
				cout << found_cities[i] << endl;
			}
			else
			{
				cout << found_cities[i] << ", ";
			}
		}
	}
	for (int j = 0; j < visited.size(); j++)
	{
		if (visited.size()-1 == j)
		{
			cout << visited[j] << endl << endl;
		}
		else
		{
			cout << visited[j] << ", ";
		}
	}
	found_cities.clear();
	visited.clear();
}

void QuadTree::pretty_print()
{
	if (root != nullptr)
	{
		pretty_print(root);
		cout << endl;
	}
}

void QuadTree::pretty_print(binarynode * r)
{
	if (r != nullptr)
	{
		cout << r->name << endl;
		pretty_print(r->SE);
		pretty_print(r->SW);
		pretty_print(r->NE);
		pretty_print(r->NW);
	}
}

void QuadTree::insert(binarynode * ptr)
{
	if (!(ptr->xcoord > 100 || ptr->ycoord > 100 || ptr->xcoord <0 || ptr->ycoord < 0))
	{
		if (root == nullptr)
		{
			root = ptr; 
		}
		else
		{
			insert(ptr,root);
	}
	}
}

void QuadTree::insert(binarynode * ptr, binarynode * r)
{
	if (r == nullptr)
	{
		r = ptr; // just in case
	}
	else
	{
		binarynode * tracker = r;
		binarynode * father = nullptr;
		string quadrant;
		while (tracker != nullptr)
		{
			if (ptr->xcoord == tracker->xcoord && ptr->ycoord == tracker->ycoord) // if its exactly the same we wont add it.
			{
				break;
			}
			father = tracker;
			quadrant = compare(ptr,tracker);
			tracker = Son(tracker,quadrant);
		}
		if (tracker == nullptr) // we add it if there is not already same city.
		{
			add2end(ptr,father,quadrant);
		}
	}
}

string QuadTree::compare(binarynode * ptr, binarynode * f)
{
	if (ptr->xcoord < f->xcoord)
	{
		if (ptr->ycoord < f->ycoord)
		{
			return "SW";
		}
		else
		{
			return "NW";
		}
	}
	else if (ptr->ycoord < f->ycoord)
	{
		return "SE";
	}
	else
	{
		return "NE";
	}
}

binarynode * QuadTree::Son(binarynode * ptr, string direction)
{
	if (direction == "SW")
	{
		return ptr->SW;
	}
	else if (direction == "SE")
	{
		return ptr->SE;
	}
	else if (direction == "NE")
	{
		return ptr->NE;
	}
	else if (direction == "NW")
	{
		return ptr->NW;
	}
}

void QuadTree::add2end(binarynode * ptr,binarynode * r, string quadrant)
{
	if (quadrant == "SW")
	{
		r->SW = ptr;
	}
	else if (quadrant == "SE")
	{
		r->SE = ptr;
	}
	else if (quadrant == "NE")
	{
		r->NE = ptr;
	}
	else if (quadrant == "NW")
	{
		r->NW = ptr;
	}
}

void QuadTree::find(int x, int y, int r)
{
	find(root,x,y,r);
}

void QuadTree::find(binarynode * f,int x,int y,int r)
{
	if (f != nullptr)
	{
		visited.push_back(f->name);
		if (f->xcoord < x-r && f->ycoord > y+r) // for the point 1
		{
			find(f->SE,x,y,r);
		}
		else if ((f->xcoord >= x-r && f->xcoord <= x+r) && f->ycoord > y+r) // for the point 2
		{
			find(f->SE,x,y,r);
			find(f->SW,x,y,r);
		}
		else if (f->xcoord > x+r && f->ycoord > y+r) // for the point 3
		{
			find(f->SW,x,y,r);
		}
		else if (f->xcoord < x-r && (f->ycoord <= y+r && f->ycoord >= y-r)) // for the point 4
		{
			find(f->SE,x,y,r);
			find(f->NE,x,y,r);
		}
		else if (f->xcoord > x+r && (f->ycoord <= y+r && f->ycoord >= y-r)) // for the point 5
		{
			find(f->SW,x,y,r);
			find(f->NW,x,y,r);
		}
		else if (f->xcoord < x-r && f->ycoord < y-r) // for the point 6
		{
			find(f->NE,x,y,r);
		}
		else if ((f->xcoord >= x-r && f->xcoord <= x+r) && f->ycoord < y-r) // for the point 7
		{
			find(f->NE,x,y,r);
			find(f->NW,x,y,r);
		}
		else if (f->xcoord > x+r && f->ycoord < y-r) // for the point 8
		{
			find(f->NW,x,y,r);
		}
		else // for the condition that point is inside the square where its corner points are {(x-r,y-r),(x-r,y+r),(x+r,y-r),(x+r,y+r)}.
		{
			int dist = pow(r,2) - (pow((x-f->xcoord),2) + pow((y-f->ycoord),2)); // distance between the point and circle area.
			if (dist >= 0) // it means its in the circle, so point 13
			{
				found_cities.push_back(f->name);
				find(f->SE,x,y,r);
				find(f->SW,x,y,r);
				find(f->NE,x,y,r);
				find(f->NW,x,y,r);
			}
			else if (f->xcoord <= x && f->ycoord >= y) // for point 9
			{
				find(f->SE,x,y,r);
				find(f->SW,x,y,r);
				find(f->NE,x,y,r);
			}
			else if (f->xcoord >= x && f->ycoord >= y) // for point 10
			{
				find(f->SE,x,y,r);
				find(f->SW,x,y,r);
				find(f->NW,x,y,r);
			}
			else if (f->xcoord <= x && f->ycoord <= y) // for point 11
			{
				find(f->SE,x,y,r);
				find(f->NE,x,y,r);
				find(f->NW,x,y,r);
			}
			else if (f->xcoord >= x && f->ycoord <= y) // for point 12
			{
				find(f->SW,x,y,r);
				find(f->NE,x,y,r);
				find(f->NW,x,y,r);
			}
		}
	}
}