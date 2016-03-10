/*
 * File: pqueuetest.cpp
 * --------------------
 * Implementation file for the the module which test the
 * different operations of a PQueue.   You may want to edit
 * the code to add more specific or thorough tests of your own.
 *
 * Julie Zelenski, CS106, Fall 2007
 */

#include "pqueuetest.hpp"
#include <iostream>
#include <random>

using namespace std;

bool ArrayIsSorted(int array[], int size);


/*
 * Function: BasicPQueueTest
 * Usage: BasicQueueTest();
 * ------------------------
 * Runs a test of the PQueue focusing on simple enqueue, dequeueMax.
 * Reports results of test to cout.
 */
void BasicPQueueTest()
{
    PQueue pq;
    
    cout << boolalpha;	// configure stream to print booleans as true/false instead of 1/0
    cout << endl << "-----------   Testing Basic PQueue functions -----------" << endl;
    cout << "The pqueue was just created.  Is it empty? " << pq.isEmpty() << endl;
    
    cout << endl << "Now enqueuing integers from 1 to 10 (increasing order)" << endl;
    for (int i = 1; i <= 10; i++)
        pq.enqueue(i);
    
    cout << "Pqueue should not be empty.  Is it empty? " << pq.isEmpty() << endl;
    cout << "Pqueue should have size = 10.  What is size? " << pq.size() << endl;
    
    cout << "Dequeuing the top 5 elements: ";
    for (int j = 0; j < 5; j++)
        cout << pq.dequeueMax() << " ";
    cout << endl << "Pqueue should have size = 5.  What is size? " << pq.size() << endl;
    
    cout << endl << "Dequeuing all the rest: ";
    while (!pq.isEmpty())
        cout << pq.dequeueMax() << " ";
    cout << endl << "Pqueue should be empty.  Is it empty? " << pq.isEmpty() << endl;
    
}


/*
 * Function: MoreQueueTest
 * Usage: MoreQueueTest();
 * -----------------------
 * Tests a few more enqueue, dequeueMax, some boundary cases explored.
 * Reports results of test to cout.
 */
void MorePQueueTest()
{
    PQueue pq;
    
    cout << boolalpha;
    cout << endl << "-----------   More pqueue testing functions -----------" << endl;
    
    cout << endl << "Enqueuing integers from 15 downto 1 (decreasing order)" << endl;
    for (int i = 15; i > 0; i--)
        pq.enqueue(i);
    
    cout << "Enqueuing duplicates for even numbers 2 to 14" << endl;
    for (int j = 2; j <= 14; j += 2)
        pq.enqueue(j);
    
    cout << "Dequeuing the top 10 elements: ";
    for (int k = 0; k < 10; k++)
        cout << pq.dequeueMax() << " ";
    
    cout << endl << "Dequeuing all the rest: ";
    while (!pq.isEmpty())
        cout << pq.dequeueMax() << " ";
    cout << endl << "Pqueue should be empty.  Is it empty? " << pq.isEmpty() << endl;
    
}



/*
 * Function: PQueueSortTest
 * Usage: PQueueSortTest();
 * ------------------------
 * Tests the use of the priority queue to implement a sort algorithm.  Enqueues
 * a bunch of values into pqueue and then pull them out using dequeueMax to arrange in
 * array in sorted order.  Tries it with random data inserted and then two more times
 * with data inserted in sorted order (both forward and backward) to learn how
 * the performance is affected by already sorted data.
 */
void PQueueSortTest()
{
    const int SortSize = 20;
    int array[SortSize];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    
    cout << endl << "-----------   Testing use of pqueue to sort  -----------" << endl;
    
    cout << "Enqueuing " << SortSize << " numbers into pqueue in increasing order." << endl;
    for (int i = 0; i < SortSize; i++) array[i] = i;
    PQSort(array, SortSize);
    cout << "Using dequeue to pull out numbers in sorted order.  Are they sorted? " <<
    ArrayIsSorted(array, SortSize) << endl;
    
    cout << "Enqueuing " << SortSize << " random values into the pqueue." << endl;
    for (int j = 0; j < SortSize; j++) array[j] = dis(gen);
//    for (int j = 0; j < SortSize; ++j) cout << array[j] << endl;
    PQSort(array, SortSize);
//    cout << "after sort:" << endl;
//    for (int j = 0; j < SortSize; ++j) cout << array[j] << endl;
    cout << "Using dequeue to pull out numbers in sorted order.  Are they sorted? " <<
    ArrayIsSorted(array, SortSize) << endl;
    
}

/*
 * Function: PQSort
 * Usage: PQSort(arr, n);
 * ----------------------
 * Uses the priority queue to sort an array.  Inserts all values from array into
 * a pqueue and then pulls them out with dequeueMax and assigns into array into
 * sorted order.  Depending on the running times of the underlying PQueue, this
 * can be a pretty decent sorting algorithm (for example, when using heap implementation
 * this is effectively HeapSort). This routine is exported since it is used by
 * the performance module as well as the test module.
 */

void PQSort(int array[], int nElems)
{
    PQueue pq;
    for (int i = 0; i < nElems; i++)
        pq.enqueue(array[i]);
    for (int i = nElems-1; i >= 0; i--)
        array[i] = pq.dequeueMax();
}


// Simple prredicate to verify array is sorted in increasing order
bool ArrayIsSorted(int array[], int size)
{
    for (int i = 0; i < size-1; i++)	
        if (array[i] > array[i+1]) return false;
    return true;
}

