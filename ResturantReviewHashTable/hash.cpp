// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    //node* new_restaurant = new node();
    //new_restaurant -> restaurantName = restaurantName;
    //new_restaurant -> pq = PriorityQ(); // empty
    //create priority queue
    //new_restaurant -> next = next;

    return new node{restaurantName, PriorityQ(50), next};


    //return new_restaurant;
}

HashTable::HashTable(int bsize)
{
    numCollision = 0;
    tableSize = bsize;
    table = new node*[bsize];
    //nullptr;
    for(int i = 0; i < bsize; i++)
    {
        table[i] = nullptr;
    }

}

HashTable::~HashTable()
{
    for(int i = 0; i < tableSize; i++)
    {
        node* current = table[i];

        while(current != nullptr)
        {
            node* temp = current -> next;

            delete current;

            current = temp;
        }
    }

    delete[] table;

}

void HashTable::displayTable()
{
    for(int i = 0; i < tableSize; i++)
    {
        cout << i << " | ";
        
        node * current = table[i];

        while(current != nullptr)
        {
            cout << current ->restaurantName;

            if(current ->next != nullptr)
            {
                cout << "-->";
            }
            else
            {
                cout << "--> NULL";
            }

            current = current -> next;
        }
        cout << endl;
    }

}

unsigned int HashTable::hashFunction(string restaurantName)
{
   unsigned int total = 0;

    for(int i = 0; i < restaurantName.size(); i++)
    {
        total += restaurantName[i];
    }

    return total % tableSize;
}

node* HashTable::searchItem(string restaurantName)
{
    int index = hashFunction(restaurantName);

    node* current = table[index];

    while(current != nullptr)
    {
        if(current -> restaurantName == restaurantName)
        {
            return current;
        }
        current = current -> next;
    }

    
    return nullptr;

}

void HashTable::insertItem(ReviewInfo restaurant)
{
    node* resturantFinder = searchItem(restaurant.restaurantName);

    //cout << resturantFinder << endl;

    if (resturantFinder != nullptr) {
        //cout << "rf is not null" << endl;
        // If a node exists, insert the ReviewInfo restaurant into its priorityQueue
        resturantFinder->pq.insertElement(restaurant);
    } 
    else
    {
        //cout << "rf is null" << endl;

        node* new_node = createNode(restaurant.restaurantName, nullptr);
        int index = hashFunction(restaurant.restaurantName);

        if (table[index] == nullptr) 
        {
            // This is the first node of that chain, update the chain head in the table
            table[index] = new_node;
        } 
        else 
        {
            //cout << "in else stament" << endl;
            // This is a collision, update the numCollision
            numCollision++;
            //cout << "num of coliisions is " << numCollision << endl;
            // Add the node to the start of the linked list
            new_node->next = table[index];
            table[index] = new_node;
        }

        new_node->pq.insertElement(restaurant);
    } 

    
}


void HashTable::setup(string fname)
{
    ifstream fin;

    fin.open(fname);


    if(fin.is_open())
    {
        string line;

        while(getline(fin, line))
        {
            stringstream s(line);
            string name;
            string review;
            string customerName;
            string timeString;
            int time;

            getline(s, name, ';');
            getline(s, review, ';');
            getline(s, customerName, ';');

            getline(s, timeString);
            time = stoi(timeString);

            ReviewInfo r = {name, review, customerName, time};

            /*cout << " Name is " << r.restaurantName << endl; 
            cout << " Review is " << r.review << endl; 
            cout << "Customer Name is " << r.customer << endl; 
            cout << "Time is " << r.time << endl;
            cout << endl;*/
            insertItem(r);
        }
    }


}