
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#include <string>
#include "HashADT.h"




void readShootings(string filename, HashTable <string> &hashTable);

int main()
{

    HashTable <string> hTable;

    readShootings("data.txt", hTable);
    hTable.printHashTable();

}
