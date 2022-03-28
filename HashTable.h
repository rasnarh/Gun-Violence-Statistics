//Header file for HashTable class
//Created by: Charu Shekhar

#include <string>
#include "Incidents.h"

using std::string;

#ifndef _HASH_TABLE
#define _HASH_TABLE

#define MAX_ARR_SIZE 49  // Size of the Hash Table Array

class HashTable
{
private:
    struct HashTableNode
        {
            string key;
            Incidents value;
            HashTableNode *next;
        };

    HashTableNode *head; // Array of nodes
    int *collisions;  // Array of collisions
    int  loadFactor;
    int  totalNodes;
    int  totalCollisions;


public:
	HashTable();
	~HashTable();
	void insertNode (Incidents incident, string key);
	bool deleteNode (string key);
	bool searchNode (string key, Incidents &nodeValue);
	void printHashTable ();
	void printStatistics();
	int computeHash(string ID);
};



#endif

