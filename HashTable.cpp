// Implementation file for the HashTable class
// Written By: Charu Shekhar

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "HashTable.h"

using namespace std;

//***************************************************************************************
// Constructor
// This function allocates and initializes a sentinel node
//      A sentinel (or dummy) node is an extra node added before the first data record.
//      This convention simplifies and accelerates some list-manipulation algorithms,
//      by making sure that all links can be safely dereferenced and that every list
//      (even one that contains no data elements) always has a "first" node.
//***************************************************************************************

HashTable::HashTable()
{
    int i;

    head = new HashTableNode [MAX_ARR_SIZE];
    collisions = new int [MAX_ARR_SIZE];

    for (i=0; i< MAX_ARR_SIZE; i++)
    {
		head[i].next = NULL;
        head[i].key = "";
        collisions [i] = 0;
    }
    loadFactor = 0;
    totalNodes = 0;
    totalCollisions = 0;
}

HashTable::~HashTable()
{
    int i;
    HashTableNode *currentNode;
    HashTableNode *nextNode;

    //First delete all the Hash Table nodes

    for (i=0; i< MAX_ARR_SIZE; i++)
    {
        currentNode = head[i].next;

        //If there is a linked list at this index, traverse thru the list, and delete all the nodes
        while (currentNode != NULL)
        {
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }
    // Now delete the dynamically allocated Hash Table Array
    delete [] head;
    // Now delete the dynamically created Collisions Array
    delete [] collisions;
}

void HashTable::insertNode (Incidents newIncident, string key)
{
    int index;
    HashTableNode *newNode;
    HashTableNode *currentNode;

    index = computeHash(key);

    currentNode = head[index].next; // Directly go the correct array element

    // Create a new Node dynamically, and fill in the values 
    newNode = new HashTableNode;
    newNode->value = newIncident;
    newNode->key = key;
    newNode->next = NULL;


    if (head[index].next == NULL)
    {
        // The slot in the hash table is empty. So insert in at the head of the linked list
        head[index].next = newNode;
    }
    else
    {
        //There was a collision 
        //Increment collision statistic
        collisions[index]++;
        totalCollisions++;
        // The slot in the hash table is NOT empty. So insert in at the tail of the linked list
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
    totalNodes++;

    //Now compute Hash Table Load Factor
    //First compute how many Hash Table Array elements are occupied
    int occupied = 0;

    for (index=0; index < MAX_ARR_SIZE; index++)
    {
        if (head[index].next != NULL)
            occupied++;
    }
    loadFactor = occupied*100/MAX_ARR_SIZE;
}


void HashTable::printHashTable()
{
    int index=0;
    HashTableNode *newNode;
    HashTableNode *currentNode;

    cout << endl;
    for (index=0; index< MAX_ARR_SIZE; index++)
    {
       cout << "Index: " << index << "; ";
       currentNode = head[index].next;
       cout << "Collisions: " << collisions[index] << "; ";
       if (currentNode == NULL)
       {
           cout << " Empty";
       }
       else
       {
           //Let us print the linked list now.
           while (currentNode != NULL)
           {
               cout << " " << currentNode->key <<"->";
               currentNode = currentNode->next; // Move to next node
           }
       }
       cout << endl;
    }
}

bool HashTable::deleteNode (string deleteKey)
{
    int index;

    HashTableNode *currentNode;
    HashTableNode *previousNode;
	Incidents inc;

    index = computeHash(deleteKey);

	previousNode = &head[index];//.next;
    currentNode= head[index].next; // Start at the first node

    while(currentNode != NULL)
    {
        if (deleteKey == currentNode->key)
        {
			if (collisions[index] != 0)
			{
				collisions[index]--;
				totalCollisions--;
			}
			//cout << totalCollisions;

           previousNode->next = currentNode->next; //Repoint the previous node

           delete currentNode;
           totalNodes--;
           return true;
        }
        // Advance both previousNode and currentNode
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    return false;
}

bool HashTable::searchNode (string searchKey, Incidents &nodevalue)
{
    int index=0;

    HashTableNode *currentNode;

    index = computeHash(searchKey);
    currentNode= head[index].next; // Start at the first node
    while(currentNode != NULL)
    {
        if (searchKey == currentNode->key)
        {
            nodevalue = currentNode->value;
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

int HashTable::computeHash(string ID)
{
	int seed = 3;
	int hash = 0;
	int i;
	int temp;

	for (i = 0; i < ID.length(); i++)
	{
		temp = ID[i];
		hash = (hash * seed) + ID[i];
	}
	hash = (hash % MAX_ARR_SIZE);

	return hash;
}

void HashTable::printStatistics()
{
    cout << "Load Factor : " << loadFactor << "%"<<endl;
    cout << "Total nodes : " << totalNodes <<endl;
    cout << "Total collisions : " << totalCollisions <<endl;
}
