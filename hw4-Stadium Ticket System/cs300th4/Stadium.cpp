#include "Stadium.h"

Stadium::Stadium(){}

Stadium::~Stadium(){
	// Heap destructor
	for (int i = 0; i < rownum; i++)
	{ // destruct them at the same time because they have exactly same sizes
		delete[] Heap[i];
		delete [] Location[i];
	}
	delete[] Heap;
	delete[] Location;

	for (int i = 0; i < blocknum; i++)
	{
		for (int j = 0; j < rownum; j++)
		{
			delete[] seats[blocknum][rownum];
		}
		delete[] seats[blocknum];
	}
	delete[] seats;
}

rownode Stadium::percolateDown(int index, int row){

	int child;
	Heap[row][index].seatnum += 1;
	rownode temp = Heap[row][index];			
	//int index = 1;
	while (index < heapSize-1 && index*2 <= heapSize-1)
	{
		child = index*2;
		if (child != heapSize-1 && Heap[row][child+1].seatnum <= Heap[row][child].seatnum)
		{
			if (Heap[row][child+1].seatnum == Heap[row][child].seatnum && Heap[row][child+1].blocknum < Heap[row][child].blocknum)
			{ // for the case if they have same seat num, we check the block priority.
				child++;
			}
			else if (Heap[row][child+1].seatnum < Heap[row][child].seatnum)
			{
				child++;
			}
		}
		if (Heap[row][child].seatnum <= temp.seatnum)
		{
			if (Heap[row][child].seatnum == temp.seatnum && Heap[row][child].blocknum > temp.blocknum)
			{// for the case if they have same seat num, we check the block priority. 
				break;
			}
			else
			{
				Location[row][Heap[row][index].blocknum] = Location[row][Heap[row][child].blocknum];
				Heap[row][index] = Heap[row][child];
			}
		}
		else
		{
			break;
		}
		index = child;
	}
	Heap[row][index] = temp;
	Location[row][temp.blocknum] = index;
	return temp;
}

void Stadium::insert_block(string name,int index){
	blockindx[name] = index;
	blocknames.push_back(name);
}

void Stadium::insert_row(string name,int index)
{
	rowindx[name] = index;
	rownames.push_back(name);
}

void Stadium::Build(int blocks,int rows, int cols){
	heapSize = blocks+1; // we add 1 for the dummy
	colnum = cols;
	blocknum = blocks;
	rownum = rows;
	Heap = new rownode*[rows];
	// this is the buildHeap part. its to keep track of our indices and locations
	// Location 2d array
	Location = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		Location[i] = new int[heapSize];
		for (int j = 0; j < heapSize; j++)
		{
			Location[i][j] = -1; // we give default value as -1 which indicates that index block-row has not assigned into heap.
		}
	}
	// Heap 2d array
	for (int i = 0; i < rows; i++) 
	{           // we create 2d heap array. for each row, we ll have another prio queue because we ll be asked to check rows.
		Heap[i] = new rownode[heapSize];
		for (int j = 1; j < heapSize; j++) // start from 1 because we have one dummy to percolate accordingly.
		{
			rownode node;
			node.blocknum = j-1; // add -1
			node.blockname = blocknames[j-1];
			node.seatnum = 0; // its all 0 since its empty at the beginning.
			Heap[i][j] = node; 
			Location[i][node.blocknum] = j; // we keep their locations accordingly.
		}
	}
	// this is the Stadium part
	seats = new string**[blocknum];
	for (int i = 0; i < blocknum; i++) // creating 3d array for the stadium
	{
		seats[i] = new string*[rows];
		for (int j = 0; j < rows; j++)
		{
			seats[i][j] = new string[cols];
			for (int k = 0; k < cols; k++)
			{
				seats[i][j][k] = "---"; // we give the default value --- because stadium is initally empty.
			}
		}
	}
}

void Stadium::print(ofstream & file)
{
	file << endl;
	for (int i = 0; i < blocknum; i++)
	{
		file << blocknames[i]+"\n~~~~~~~\n";
		for (int j = 0; j < rownum; j++)
		{
			file << rownames[j] + " :";
			for (int k = 0; k < colnum; k++)
			{
				file << " " + seats[i][j][k]; 
			}
			file << endl;
		}
		file << "=======\n\n"; 
	}
}

void Stadium::rezbyrow(string customer_name,string row_name,ofstream & file){

	if (rezerv.find(customer_name) != rezerv.end())
	{
		file << customer_name + " could not reserve a seat!" << endl;
	}
	else
	{
		int row = rowindx[row_name];
		if (Heap[row][1].seatnum == colnum) // in this case it means there is no seat left
		{
			file << customer_name + " could not reserve a seat!" << endl;
		}
		else
		{
			// we are going to add 1 and percolate down since now [row][1] may not be the min property anymore.
			rownode temp = percolateDown(1,row); // index we pass is 1 because we re going to add min value in min heap.
			// Now after the heap part, we are going to add our customer to stadium accordingly.
			for (int i = 0; i < colnum; i++)
			{
				if (seats[temp.blocknum][row][i] == "---")
				{
					seats[temp.blocknum][row][i] = customer_name.substr(0,3);
					seat seat;
					seat.blockname = blocknames[temp.blocknum];
					seat.rowname = rownames[row];
					seat.column = i;
					rezerv[customer_name] = seat;
					file << customer_name + " has reserved " + temp.blockname + " " + row_name + "-" << i << " by emptiest block" << endl;
					break;
				}
			}
		}
	}
}

void Stadium::rez_seat(string customer_name, string block_name, string row_name, int column,ofstream & file){

	int row = rowindx[row_name];
	int block = blockindx[block_name];
	if (rezerv.find(customer_name) != rezerv.end() || seats[block][row][column] != "---")
	{
		file << customer_name + " could not reserve a seat!" << endl;
	}
	else
	{ 
		int index = Location[row][block]; // we get the index of the block so we can percolate it down after we increment its size.
		rownode node = percolateDown(index,row); // we percolate accordingly to keep the Heap in order.
		seats[block][row][column] = customer_name.substr(0,3);
		seat seat;
		seat.blockname = block_name;
		seat.rowname = row_name;
		seat.column = column;
		rezerv[customer_name] = seat;
		file << customer_name +" has reserved " + block_name + " "+ row_name +"-" << column << endl;
	}

}

void Stadium::get_seat(string customer_name,ofstream & file){

	if (rezerv.find(customer_name) == rezerv.end())
	{
		file << "There is no rezervation made for " + customer_name +"!"<< endl; 
	}
	else
	{
		seat seatt = rezerv[customer_name];
		file << "Found that " + customer_name + " has a reservation in " + seatt.blockname + " " + seatt.rowname + "-" << seatt.column << endl;
	}	
}

void Stadium::cancelrez(string customer_name,ofstream & file){

	if (rezerv.find(customer_name) == rezerv.end())
	{
		file << "Could not cancel the reservation for " + customer_name +"; no reservation found!" << endl;
	}
	else
	{
		// we should percolate up in the minheap because we are decreasing the seatnum of one node by cancelling rezervation 
		seat seatt = rezerv[customer_name];
		int row = rowindx[seatt.rowname];
		int index = Location[row][blockindx[seatt.blockname]];
		Heap[row][index].seatnum -= 1; // we decrease because we are cancelling the rezervation.
		rownode node = Heap[row][index];
		while (index > 1 && Heap[row][index/2].seatnum >= node.seatnum)
		{
			if (Heap[row][index/2].seatnum > node.seatnum ||(Heap[row][index/2].seatnum == node.seatnum && node.blocknum < Heap[row][index/2].blocknum))
			{// we check block priority if seatnum are equal.
				int tmp = Location[row][Heap[row][index].blocknum];
				Location[row][Heap[row][index].blocknum] = Location[row][Heap[row][index/2].blocknum];
				Location[row][Heap[row][index/2].blocknum] = tmp;
				rownode temp = Heap[row][index];
				Heap[row][index] = Heap[row][index/2];
				Heap[row][index/2] = temp;
				index /= 2;
			}
			else
			{
				break;
			}
		}
		Location[row][node.blocknum] = index;
		// now after heap operations, we delete the customer from the hashmap and the stadium.
		int block = blockindx[seatt.blockname];
		seats[block][row][seatt.column] = "---";
		rezerv.erase(customer_name);
		file << "Cancelled the reservation of " + customer_name << endl;
	}
}



