#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);


    bool optionOneChosen = false;
	
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
				//
                if(optionOneChosen == true)
                {
                    cout << "Data Structure has already been built!" << endl;
                    break;
                }
                
                ht.setup(fname);
                optionOneChosen = true;
				break;
            }
            case 2:
			{
                //
                string RestaurantName;
                string CustomerName;
                string CustomerReview;
                string ReviewTimeString;
                int ReviewTime;

                cout << "Restaurant Name: " << endl;
                getline(cin, RestaurantName);

                cout << "Customer: " << endl;
                getline(cin, CustomerName);

                cout << "Review: " << endl;
                getline(cin, CustomerReview);

                cout << "Time: " << endl;
                getline(cin, ReviewTimeString);
                ReviewTime = stoi(ReviewTimeString);


                ReviewInfo new_Review = {RestaurantName, CustomerName, CustomerReview, ReviewTime};

                ht.insertItem(new_Review);

				break;
            }
            case 3:
			{
                //
                string RestaurantName;
                cout << "Restaurant name: " << endl;
                getline(cin, RestaurantName);

                node* resturantFinder = ht.searchItem(RestaurantName);
                if(resturantFinder != nullptr)
                {
                    resturantFinder->pq.peek();
                }

				break;
            }
            case 4:
			{
                //
                string RestaurantName;
                cout << "Restaurant name: " << endl;
                getline(cin, RestaurantName);

                node* resturantFinder = ht.searchItem(RestaurantName);
                if(resturantFinder != nullptr)
                {
                    resturantFinder->pq.pop();
                }
                if(resturantFinder == nullptr)
                {
                    cout << "no record found" << endl;
                }
				break;
            }
            case 5:
			{
				//
                string RestaurantName;
                cout << "Restaurant name: " << endl;
                getline(cin, RestaurantName);

                node* resturantFinder = ht.searchItem(RestaurantName);
                if(resturantFinder != nullptr)
                {
                    resturantFinder->pq.print();
                }

				break;
			}
            case 6:
                //
                cout << ht.getNumCollision() << endl;

                break;
            case 7:
                // 

                ht.displayTable();
                break;

            case 8:
				break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
