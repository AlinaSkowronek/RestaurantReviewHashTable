#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include <fstream>
#include "PriorityQueue.hpp"

using namespace std;

struct node {
   string restaurantName;
   PriorityQ pq;
   struct node* next;
};

class HashTable
{
private:
    int tableSize;  // No. of buckets (linked lists)
    // Pointer to an array containing buckets
    node** table;
    node* createNode(string restaurantName, node* next);
    int numCollision;
public:
    HashTable(int bsize);  // Constructor  
    ~HashTable();  // Constructor
    void setup(string fname);
    void insertItem(ReviewInfo restaurant);
    unsigned int hashFunction(string key);
    int getNumCollision(){return numCollision;};    
    node* searchItem(string key);    
    void displayTable();    
};

#endif
