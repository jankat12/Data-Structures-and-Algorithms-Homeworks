#ifndef  STADIUM_H
#define STADIUM_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct rownode{
	string blockname;
	int seatnum;
	int blocknum; // we re going to use this for equal seat empty seat cases.
	rownode(){
	seatnum = 0; // at first there is no one sitting in the row.
	}
};

struct seat{ 
	// this struct is for keep the data of customer name
	string blockname;
	string rowname;
	int column;
};

class Stadium{

private:
	vector<string> rownames; // we keep rownames here		
	vector<string> blocknames; // we keep blocknames here
	unordered_map<string, seat> rezerv; // this is the info of the customer rezervation
	unordered_map<string,int> rowindx; // to convert row names to int so we can keep track of indices.
	unordered_map<string,int> blockindx; // to convert block names to int so we can keep track of indices.
	string *** seats; // simulate whole stadium.
	rownode ** Heap; // In heap we re going to keep the empty seat number of each block in each row.
	int ** Location; // we also keep locations accordingly to reach them in O(1) time.
	int heapSize; 
	int blocknum; // we store the total block number
	int rownum; // we store the total row number
	int colnum; // we store the total column number
	void byrow_insert(rownode node,seat seat);// priv func for rez by row.
public:
	Stadium();
	~Stadium();
	void Build(int blocks,int rows, int cols);
	void insert_block(string name,int index);
	void insert_row(string name,int index);
	void print(ofstream & file);
	rownode percolateDown(int index, int row);
	void rezbyrow(string customer_name,string row_name,ofstream & file);
	void rez_seat(string customer_name,string block_name, string row_name, int column,ofstream & file);
	void get_seat(string customer_name,ofstream & file);
	void cancelrez(string customer_name,ofstream & file);
};
#endif // ! STADIUM_H
