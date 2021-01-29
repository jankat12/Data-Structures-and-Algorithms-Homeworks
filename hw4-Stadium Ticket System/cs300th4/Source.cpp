#include <iostream>
#include "Stadium.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(){
	Stadium stadium;
	int colnum = 0;  // numbers of colons we will pass this to class
	string inputfilename = "inputs3.txt"; // the file name we re going to read
	string outfilename = "outputs.txt"; // the file name we re going to write
	ifstream inputfile;
	ofstream file;
	file.open(outfilename);
	inputfile.open(inputfilename.c_str());
	int linectr = 0; // to keep track of the lines we read
	int blocknum = 0; // numbers of blocks we will pass this to class
	int rownum = 0;// numbers of rows we will pass this to class
	string line;
	
	while (getline(inputfile,line))
	{
		
		stringstream ss(line);
		string word;
		if (linectr == 0) // first line of code will take the block names
		{
			while (ss >> word)
			{			
				stadium.insert_block(word,blocknum);
				blocknum ++;
			}
		}
		else if (linectr == 1) // second line ýf code will take the rownames
		{
			while (ss >> word)
			{				
				stadium.insert_row(word,rownum);
				rownum ++;
			}
		}
		else if (linectr == 2) // third line will take the column number.
		{
			colnum = stoi(line); 
			stadium.Build(blocknum,rownum,colnum); // we can now build the stadium because we have enough info.
		}
		else
		{
			ss >> word;
			if (word == "print")
			{
				stadium.print(file);
			}
			else if (word == "reserve_seat")
			{
				ss >> word;
				string cust_name = word;
				ss >> word;
				string block_name = word;
				ss >> word;
				string row_name = word;
				ss >> word;
				int column = stoi(word);
				stadium.rez_seat(cust_name,block_name,row_name,column,file);
			}
			else if (word == "reserve_seat_by_row")
			{
				ss >> word;
				string cust_name = word;
				ss >> word;
				string row_name = word;
				stadium.rezbyrow(cust_name,row_name,file);
			}
			else if (word == "cancel_reservation")
			{
				ss >> word;
				string cust_name = word;
				stadium.cancelrez(cust_name,file);
			}
			else if (word == "get_seat")
			{
				ss >> word;
				string cust_name = word;
				stadium.get_seat(cust_name,file);
			}
		}
		linectr ++;
	}
	inputfile.close();
	file.close();
	return 0;
}
