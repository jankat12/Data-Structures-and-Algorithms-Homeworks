//#include "my_heap.h"
//int main(){
//My_heap heap;
//heap.print_heap();
//memory_block* block = heap.bump_allocate(8);
//memory_block* block1 = heap.bump_allocate(12);
//memory_block* block2 = heap.bump_allocate(9);
//memory_block* block3 = heap.bump_allocate(23);
//heap.print_heap();
//heap.deallocate(block1);
//heap.print_heap();
//heap.deallocate(block2);
//heap.print_heap();
//return 0;
//}

//#include "my_heap.h"
//#include <iostream>
//using namespace std;
//
//
//int main(){
//    My_heap heap;
//
//    memory_block* b1 = heap.bump_allocate(10);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "Bump allocate 10\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    memory_block* b2 = heap.first_fit_allocate(20);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "First fit allocate 20\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    memory_block* b3 = heap.first_fit_split_allocate(10);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "First fit split allocate 10\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    memory_block* b4 = heap.best_fit_allocate(15);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "Best fit allocate 15\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//
//    heap.deallocate(b4);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "deallocate\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//    heap.deallocate(b2);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "deallocate\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//
//    memory_block* b5 = heap.best_fit_allocate(12);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "Best fit allocate 12\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//
//    memory_block* b6 = heap.first_fit_split_allocate(16);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "First fit split allocate 16\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//
//    heap.deallocate(b3);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "deallocate\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//    heap.deallocate(b5);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "deallocate\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//    memory_block* b7 = heap.first_fit_allocate(16);
//    cout << "~~~~~~~~~~~~~~\n";
//    cout << "First fit allocate 16\n";
//    cout << "~~~~~~~~~~~~~~\n";
//    heap.print_heap();
//
//    
//    return 0;
//}