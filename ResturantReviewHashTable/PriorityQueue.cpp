#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    ReviewInfo temp = *a;
    *a = *b;
    *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    heapArr = new ReviewInfo[50];
    capacity = 50;
    currentSize = 0;
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return (2 * index) + 1;
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    return (2 * index) + 2;
}

void PriorityQ::peek()
{
    if(heapArr[0].restaurantName.empty())
    {
        cout << "no record found" << endl;
    }
    else
    {
        cout << "Restaurant: " << heapArr[0].restaurantName << endl;
        cout << "Customer: " << heapArr[0].customer << endl;
        cout << "Review: " << heapArr[0].review << endl;
        cout << "Time: " << heapArr[0].time << endl;
    }
}

void PriorityQ::heapify(int i)
{
    int smallest = i; //smallest as root
    int left = leftChild(i);
    int right = rightChild(i);

    if(left < currentSize && (heapArr[left].time < heapArr[smallest].time))
    {
        smallest = left;
    }

    if(right < currentSize && (heapArr[right].time < heapArr[smallest].time))
    {
        smallest = right;
    }

    if(smallest != i)
    {
        swap(heapArr[i], heapArr[smallest]);
        heapify(smallest);
    }

}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    //inserting into the heapArr() -> the comment/review
    // check left left() right() parent()
    //the soonest time goes as the top of the heap
    //while loop with swap()

    if(currentSize >= capacity)
    {
        cout << "Maximum heap size reached. Cannot insert anymore." << endl;
    }
    else
    {
        //cout << "in insert element function" << endl;

        heapArr[currentSize] = restaurant;

        //cout << "iafter heapArr" << endl;

        int index = currentSize;

        while(currentSize > 0 && (heapArr[index].time > heapArr[parent(index)].time))
        {
            //cout << "in while loop" << endl;
            swap(heapArr[index], heapArr[parent(index)]);
            index = parent(index);
        }

        currentSize++;

        //cout << "current size is" << currentSize << endl;
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    for(int i = 0; i < currentSize; i++)
    {
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    heapArr[0] = heapArr[currentSize - 1];
    currentSize--;

    heapify(0);

}
