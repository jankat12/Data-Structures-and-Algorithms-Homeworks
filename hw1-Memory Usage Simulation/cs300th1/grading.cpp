
#include <stdio.h>
#include "my_heap.h"
#include <iostream>
using namespace std;

bool simple1() {

    try
    {
        My_heap heap;

        memory_block* b1 = heap.bump_allocate(10);
        memory_block* b2 = heap.first_fit_allocate(20);
        memory_block* b3 = heap.first_fit_split_allocate(10);
        memory_block* b4 = heap.best_fit_allocate(15);

        heap.deallocate(b2);

        heap.print_heap();
		if (fabs(heap.get_fragmantation() - 4.19) < 0.01)
			return true;

        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
 
}

bool simple2() {

    try
    {
        My_heap heap;

        memory_block* b1 = heap.first_fit_allocate(20);
        memory_block* b2 = heap.bump_allocate(20);
        memory_block* b3 = heap.best_fit_allocate(20);
        heap.deallocate(b2);
        memory_block* b4 = heap.first_fit_split_allocate(3);

        heap.print_heap();

		if (fabs(heap.get_fragmantation() - 3.62) < 0.01)
			return true;

        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
   
}

bool simple3() {

    try
    {
        My_heap heap;

        memory_block* b1 = heap.first_fit_allocate(20);
        heap.deallocate(b1);
        memory_block* b2 = heap.bump_allocate(20);
        heap.deallocate(b2);
        memory_block* b3 = heap.best_fit_allocate(20);
        heap.deallocate(b3);
        heap.print_heap();

		if (fabs(heap.get_fragmantation() - 7.81) < 0.01)
			return true;
        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
   
}

bool fair1() {
    // testing the corner case od deallocating an already deallocated memory_block

    try
    {
        My_heap heap;

        memory_block* b1 = heap.bump_allocate(10);

        heap.deallocate(b1);
        heap.deallocate(b1);

        heap.print_heap();

		if (fabs(heap.get_fragmantation() - 1.95) < 0.01)
			return true;
        return false;
    }

    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
}

bool fair2() {
    // checking the condition of allocating a memory block of size more than 512
    // and checking  the consition of a memory block if no free space in the heap.
    try
    {
        My_heap heap;
		// it shoud not allocate nor deallocate b1
        memory_block* b1 = heap.first_fit_allocate(513);

        heap.deallocate(b1);

        memory_block* b2 = heap.first_fit_split_allocate(511);
        memory_block* b3 = heap.first_fit_allocate(2);
		
        heap.print_heap();

		if (fabs(heap.get_fragmantation() - 0) < 0.01)
			return true;

        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
    
}

bool fair3() {

    try
    {
        My_heap heap;

        memory_block* b1 = heap.first_fit_allocate(10);
        memory_block* b2 = heap.bump_allocate(15);
        memory_block* b3 = heap.best_fit_allocate(15);
        memory_block* b4 = heap.best_fit_allocate(20);

        heap.deallocate(b2);
        heap.deallocate(b3);

        memory_block* b5 = heap.first_fit_split_allocate(8);
        memory_block* b6 = heap.first_fit_split_allocate(16);
        memory_block* b7 = heap.first_fit_split_allocate(6);

        heap.print_heap();

		if (fabs(heap.get_fragmantation() - 0) < 0.01)
			return true;

        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
    
}

bool hard1() {

    try
    {
        My_heap heap;

        memory_block* b1 = heap.bump_allocate(10);
        memory_block* b2 = heap.first_fit_split_allocate(20);
        memory_block* b3 = heap.first_fit_allocate(14);
        memory_block* b4 = heap.best_fit_allocate(35);
        memory_block* b5 = heap.first_fit_allocate(36);
        memory_block* b6 = heap.best_fit_allocate(10);
        memory_block* b7 = heap.bump_allocate(20);
        memory_block* b8 = heap.best_fit_allocate(14);
        memory_block* b9 = heap.first_fit_allocate(35);
        memory_block* b10 = heap.bump_allocate(36);

        heap.deallocate(b2);
        heap.deallocate(b4);
        heap.deallocate(b6);
        heap.deallocate(b8);


        memory_block* b11 = heap.first_fit_split_allocate(4);
        memory_block* b12 = heap.first_fit_split_allocate(11);
        memory_block* b13 = heap.first_fit_split_allocate(2);
        memory_block* b14 = heap.first_fit_split_allocate(20);
        memory_block* b15 = heap.first_fit_split_allocate(1);
        memory_block* b16 = heap.first_fit_split_allocate(13);
        memory_block* b17 = heap.first_fit_split_allocate(3);
        memory_block* b18 = heap.first_fit_split_allocate(15);


        heap.print_heap();

		if (fabs(heap.get_fragmantation() - 8.56) < 0.01)
			return true;

        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
    
}

bool hard2() {

    try
    {
        My_heap heap;

        memory_block* b1 = heap.first_fit_allocate(100);
        memory_block* b2 = heap.bump_allocate(50);
        memory_block* b3 = heap.best_fit_allocate(100);
        memory_block* b4 = heap.first_fit_allocate(40);
        memory_block* b5 = heap.bump_allocate(5);
        memory_block* b6 = heap.best_fit_allocate(15);
        memory_block* b7 = heap.first_fit_allocate(35);
        memory_block* b8 = heap.bump_allocate(55);
        memory_block* b9 = heap.best_fit_allocate(65);
        memory_block* b10 = heap.first_fit_allocate(10);

        heap.deallocate(b2);
        heap.deallocate(b3);
        heap.deallocate(b5);
        heap.deallocate(b7);
        heap.deallocate(b9);

        memory_block* b11 = heap.first_fit_split_allocate(3);
        memory_block* b12 = heap.first_fit_allocate(20);
        memory_block* b13 = heap.first_fit_split_allocate(27);
        memory_block* b14 = heap.first_fit_allocate(20);
        memory_block* b15 = heap.first_fit_split_allocate(13);
        memory_block* b16 = heap.best_fit_allocate(15);


        heap.deallocate(b12);
        heap.deallocate(b14);
        heap.deallocate(b1);

        memory_block* b17 = heap.first_fit_allocate(30);
        memory_block* b18 = heap.first_fit_split_allocate(12);
        memory_block* b19 = heap.best_fit_allocate(10);
        memory_block* b20 = heap.first_fit_split_allocate(5);
        memory_block* b21 = heap.best_fit_allocate(12);


        heap.print_heap();

		if (fabs(heap.get_fragmantation() - 59.09) < 0.01)
			return true;

        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
    
}

bool hard3() {

    try
    {
        My_heap heap;

        memory_block* b1 = heap.first_fit_allocate(10);
        memory_block* b2 = heap.bump_allocate(20);
        memory_block* b3 = heap.best_fit_allocate(30);
        memory_block* b4 = heap.first_fit_allocate(40);
        memory_block* b5 = heap.bump_allocate(5);
        memory_block* b6 = heap.best_fit_allocate(15);
        memory_block* b7 = heap.first_fit_allocate(35);
        memory_block* b8 = heap.bump_allocate(55);
        memory_block* b9 = heap.best_fit_allocate(65);
        memory_block* b10 = heap.first_fit_allocate(10);

        heap.deallocate(b2);
        heap.deallocate(b3);
        heap.deallocate(b5);
        heap.deallocate(b7);
        heap.deallocate(b9);

        memory_block* b11 = heap.first_fit_split_allocate(3);
        memory_block* b12 = heap.first_fit_allocate(20);
        memory_block* b13 = heap.first_fit_split_allocate(27);
        memory_block* b14 = heap.first_fit_allocate(20);
        memory_block* b15 = heap.first_fit_split_allocate(13);
        memory_block* b16 = heap.best_fit_allocate(15);
        memory_block* b17 = heap.first_fit_allocate(30);
        memory_block* b18 = heap.first_fit_split_allocate(12);
        memory_block* b19 = heap.best_fit_allocate(10);
        memory_block* b20 = heap.best_fit_allocate(3);
        memory_block* b21 = heap.best_fit_allocate(17);

        heap.print_heap();
		if (fabs(heap.get_fragmantation() - 5.79) < 0.01)
			return true;

        return false;
    }
    catch (const std::exception& exc)
    {
        cout << exc.what() << endl;
		return false;
    }
    
}


int main() {

	bool out1 = simple1();
	cout << "simple 1: " << std::boolalpha << out1 << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out2 = simple2();
	cout << "simple 2: " << out2<< endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out3 = simple3();
	cout << "simple 3: " << out3 << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out4 = fair1();
	cout << "fair 1: " << out4 << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out5 = fair2();
	cout << "fair 2: " << out5 << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out6 = fair3();
	cout << "fair 3: " << out6 << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out7 = hard1();
	cout << "hard 1: " << out7 << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out8 = hard2();
	cout << "hard 2: " << out8 << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
	bool out9 = hard3();
	cout << "hard 3: " << out9 << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;


    return 0;
}
