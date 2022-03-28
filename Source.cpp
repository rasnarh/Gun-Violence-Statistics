//MAIN
//IDE: Visual Studio 2017
//Written by: Amrita Kohli

#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"
#include "Incidents.h"
#include "BinarySearchTree.h"

#define MAX_ARR_SIZE 10

using namespace std;

//function prototypes
bool inputValidation(string choice);
void menu(HashTable &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2, Incidents &incident); // parameters will include objects of BST class and Hashing and Incidents
void readFile(string filename, HashTable& ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2, Incidents &incident);
void insertData(BinarySearchTree <Incidents> &bst1, BinarySearchTree<Incidents> &bst2, HashTable &ht, Incidents* res);
void deleteData(BinarySearchTree <Incidents> &bst1, BinarySearchTree<Incidents> &bst2, HashTable &ht, Incidents &incident, Incidents *res);
void listData(HashTable &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2);
void searchData(HashTable &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2, Incidents &incident, Incidents* res);
void display(Incidents &incident);
int compareID(const Incidents &one, const Incidents &two);
int compareState(const Incidents &one, const Incidents &two);
int comparePerfect(const Incidents &one, const Incidents &two);
bool validateID(string i, BinarySearchTree <Incidents> &bst1, Incidents* res);
bool validateState(string s);
bool validateDate(string d);
bool validateInt(string f);
bool validateString(string r);
void printHeader();
void writeFile(Incidents &incident, ofstream &obj);

int main()
{
    HashTable hTable; 
	BinarySearchTree<Incidents> one;
	BinarySearchTree<Incidents> two;
	Incidents inc;

    readFile("finaldata.txt", hTable, one, two, inc);
	menu(hTable, one, two, inc); 

	cout << "Goodbye!" << endl;
	system("pause");
	return 0;
}

/* The function menu lets the user choose an action to take. The choice the user enters is validated.
   User is prompted to enter their choice until they choose to exit. */
void menu(HashTable &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2, Incidents &incident)
{
	Incidents *res = new Incidents[MAX_ARR_SIZE]; //dynamically allocating array to store incidents

	string choice;
	cout << "Choose one of the following: " << endl;
	cout << "A: Add data" << endl;
	cout << "D: Delete data" << endl;
	cout << "F: Find data" << endl;
	cout << "L: List data " << endl;
	cout << "W: Write data " << endl;
	cout << "S: Statistics " << endl;
	cout << "H: Help" << endl;
	cout << "E: Exit " << endl;

	cout << "Enter your choice: ";
	getline(cin, choice);
	choice[0] = toupper(choice[0]);  //if user enters lowercase make it uppercase

	while ((choice[0]) != 'E')
	{
		if (inputValidation(choice) == true)
		{
			switch (choice[0])
			{
				case 'A': insertData(bst1, bst2, ht, res);
					break;
				case 'D': deleteData(bst1, bst2, ht, incident, res);
					break;
				case 'F': searchData(ht, bst1, bst2, incident, res);
					break;
				case 'L': listData(ht, bst1, bst2);
					break;
				case 'W': 
				{
					if (bst1.writeFile(writeFile))
						cout << "Written to file." << endl;
					else
						cout << "Could not write." << endl;
				}
					break;
				case 'S': ht.printStatistics();
					break;
				case 'H':
				{
					cout << endl << "-- Displaying menu --" << endl;
					cout << "A: Add data" << endl;
					cout << "D: Delete data" << endl;
					cout << "F: Find data" << endl;
					cout << "L: List data " << endl;
					cout << "W: Write data " << endl;
					cout << "S: Statistics " << endl;
					cout << "H: Help" << endl;
					cout << "E: Exit " << endl;
				}
					break;
				default: "Invalid option. Try again.\n";
			} //end switch block
		} //end if
		else
		{
			cout << "Invalid input. Try again.\n";
		}
		cout << endl << "Enter your choice: ";
		getline(cin, choice);
		choice[0] = toupper(choice[0]);
	}  //end while
	delete [] res; 
}

/* Ensures choice is a single letter. */
bool inputValidation(string choice)
{
	if (choice.length() == 1 && isalpha(choice[0]))
		return true;

	return false;
}

/* This function reads the  file passed into it as filename 
   and stores incidents in hash table and binary search trees. */
void readFile(string filename, HashTable &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2, Incidents &incident)
{
	ifstream infile;

	// Open the input file
	infile.open(filename.c_str());

	if (infile.fail())
	{
		cout << "\nError opening the input file: " << filename << endl;
		return;
	}

	string ID, state, date, race, gender;
	int fatalities;
	

	// Read the file line by line	
	while (getline(infile, ID, ','))
	{
		getline(infile, state, ','); 
		getline(infile, date, ',');
		infile >> fatalities; infile.ignore();
		getline(infile, race, ',');
		getline(infile, gender);

		incident.setID(ID);
		incident.setState(state);
		incident.setDate(date);
		incident.setFatalities(fatalities);
		incident.setRace(race);
		incident.setGender(gender);

		ht.insertNode (incident, ID); //inserting incident node into hash table
		bst1.insert(incident, compareID); //inserting incident node into bst sorted by ID
		bst2.insert(incident, compareState); //inserting incident node into bst sorted by state
	}

	infile.close(); // Close the input file
}

/* This function checks if ID entered by user is valid, i.e. has four characters (digits/letters) and is unique. 
   Returns true if valid, otherwise returns false. */
bool validateID(string i, BinarySearchTree <Incidents> &bst1, Incidents* res)
{
	if (i.size() != 4) //size must be 4
		return false;
	for (int n = 0; n < i.size(); n++) 
	{
		if (isdigit(i[n]) == false && isalpha(i[n])==false) //must be a digit or letter
			return false;
	}
	Incidents inc(i, " ", " ", 0, " ", " ");
	int c = 0;
	if (bst1.getEntry(inc, res, c, compareID)==true)
		return false; //can't have duplicate primary key
	return true;
}

/* This function checks if state entered by user is valid, i.e. has two letters.
Returns true if valid, otherwise returns false. */
bool validateState(string s)
{
	if (s.size() != 2) 
		return false; //must be initials
	if (!isalpha(s[0]) || !isalpha(s[1]))
		return false;
	return true;
}

/* This function checks if date entered by user is valid.
Returns true if valid, otherwise returns false. */
bool validateDate(string d)
{
	int n = d.size();
	if (n == 0) //can't be blank
		return false;
	int slash = 0;
	if (isdigit(d[0] == false))  //must have a digit in first character
		return false;
	for (int i = 1; i < n; i++)
	{
		if (d[i] == '/') //counting slashes
			slash++;
		if (isdigit(d[i]) == false && d[i]!='/') //if not a slash or digit - invalid
			return false;
		if (d[i] == '/' && d[i - 1] == '/') //if two adjacent slashes - invalid
			return false;
		if (d[i] == '/' && slash > 2) //if more than two slashes - invalid
			return false;
	}
	if (slash < 2) // if less than two slashes - invalid
		return false;
	for (int i = n - 1; i > n - 5; i--) //if last four characters aren't digits - invalid
	{
		if (isdigit(d[i]) == false)
			return false;
	}
	
	return true;
}

/* This function checks if user entered an int.
Returns true if valid, otherwise returns false. */
bool validateInt(string f)
{
	if (f.size() == 0) //can't be blank
		return false;
	for (int n = 0; n < f.size(); n++) 
	{
		if (isdigit(f[n]) == false) //must consist of digits only
			return false;
	}
	
	return true;
}

/* This function checks if string entered by user consists of characters only.
Returns true if valid, otherwise returns false. */
bool validateString(string r)
{
	if (r.size() == 0)
		return false;
	for (int n = 0; n < r.size(); n++) 
	{
		if (isalpha(r[n]) == false)
			return false;
	}

	return true;
}

/* This function checks if gender entered by user is valid, i.e. M, F, O (other) or U (unknown).
Returns true if valid, otherwise returns false. */
bool validateGender(string g)
{
	if (inputValidation(g) == false)
		return false; //must be one character only
	g[0] = toupper(g[0]); //converting to uppercase
	if (g[0] != 'M' && g[0] != 'O' && g[0] != 'F' && g[0] != 'U')
		return false; //must be male, female, other or unknown
}

/* This function lets user add new and valid data. */
void insertData(BinarySearchTree <Incidents> &bst1, BinarySearchTree<Incidents> &bst2, HashTable &ht, Incidents* res)
{
	Incidents incident;

	string ID, state, date, f, race, gender;

	cout << "Enter 4-digit ID: ";
	getline(cin, ID);
	while (validateID(ID, bst1, res) == false)
	{
		cout << "Enter 4-digit ID: ";
		getline(cin, ID);
	}	

	cout << "Enter state initials: ";
	getline(cin, state);
	while (validateState(state) == false)
	{
		cout << "Enter state initials: ";
		getline(cin, state);
	} //capitalizing initials
	state[0] = toupper(state[0]);
	state[1] = toupper(state[1]);

	cout << "Enter date (MM/DD/YYYY): ";
	getline(cin, date);
	while (validateDate(date) == false)
	{
		cout << "Enter date (MM/DD/YYYY): ";
		getline(cin, date);
	}

	cout << "Enter number of fatalities: ";
	getline(cin, f);
	while (validateInt(f) == false)
	{
		cout << "Enter number of fatalities: ";
		getline(cin, f);
	}
	int fatalities = stoi(f); //converting string to int

	cout << "Enter race: ";
	getline(cin, race);
	while (validateString(race) == false)
	{
		cout << "Enter race: ";
		getline(cin, race);
	}

	cout << "Enter gender: ";
	getline(cin, gender);
	while (validateGender(gender) == false)
	{
		cout << "Enter gender: ";
		getline(cin, gender);
	}
	gender[0] = toupper(gender[0]); //capitalizing gender

	incident.setID(ID);
	incident.setState(state);
	incident.setDate(date);
	incident.setFatalities(fatalities);
	incident.setRace(race);
	incident.setGender(gender);
	cout << endl;
	printHeader(); //printing what has just been entered
	display(incident);

	bool check = false;
	
	check = bst1.insert(incident, compareID); 
	if (check == true)
	{
		cout << endl << "Insertion successful" << endl;
		ht.insertNode(incident, ID);
		bst2.insert(incident, compareState);
	}
	else
		cout << endl << "Insertion unsuccessful" << endl;

}

/* This function deletes data corresponding to incident entered by user. */
void deleteData(BinarySearchTree <Incidents> &bst1, BinarySearchTree<Incidents> &bst2, HashTable &ht, Incidents &incident, Incidents *res)
{
	string ID;
	cout << "Enter ID of incident to delete: ";
	getline(cin, ID);

	Incidents inc(ID," "," ",0," "," ");
	int c = 0;
	bool check = bst1.getEntry(inc, res, c, compareID); // checking if exists and returning item to res
	inc = res[0];
	if (check == true)
	{
		printHeader();
		display(inc);
		cout << endl;
		if (bst1.remove(inc, compareID) == true)
			cout << "Deleted from BST 1" << endl;
		else
			cout << "Not deleted from BST" << endl;

		if (bst2.remove(inc, comparePerfect) == true) 
			cout << "Deleted from BST 2" << endl;
		else
			cout << "Not deleted from BST 2" << endl;

		if (ht.deleteNode(ID) == true)
			cout << "Deleted from HT" << endl;
		else
			cout << "Not deleted from HT" << endl;
	}
	else
		cout << "Not found!" << endl;
}

/* This function prints the header for data of an incident. */
void printHeader()
{
	cout << "==================================================================" << endl;
	cout << setw(6) << "  ID  " << setw(8) << "    State  " << setw(12)  << " Date  " << setw(10) << "  Fatalities  " << setw(10) << "  Race  " << setw(9) << "  Gender" << endl;
	cout << "==================================================================" << endl;
}

/* This function displays data of an incident. */
void display(Incidents &incident)
{
	cout << setw(6) << incident.getID() << setw(8) << incident.getState() << setw(12) << incident.getDate()  << setw(10)
		<< incident.getFatalities() << setw(13) << incident.getRace() << setw(9) << right << incident.getGender() <<endl;
}

/* This function lists data as per user's choice. User is prompted to choose until they exit. */
void listData(HashTable &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2)
{
	string choice;

	cout << endl << "Choose one of the following: " << endl;
	cout << "U - Unsorted List in Hash Table Sequence" << endl;
	cout << "P - Sorted List by ID" << endl;
	cout << "S - Sorted List by State" << endl;
	cout << "Q - ID indented tree" << endl;
	cout << "T - State indented tree" << endl;
	cout << "H - Help" << endl;
	cout << "E - Exit" << endl;
	cout << endl << "Enter your choice: ";
	getline(cin, choice);
	choice[0] = toupper(choice[0]);

	while (choice[0]!='E')
	{
		cout << endl;
		if (inputValidation(choice) == true)
		{
			switch (choice[0])
			{
			case 'U':
			{
				ht.printHashTable(); //printing hash table
			}
				break;
			case 'P':
			{
				printHeader();
				bst1.inOrder(display); //printing BST 1
			}
				break;
			case 'S': 
			{
				printHeader();
				bst2.inOrder(display); //printing BST 2
			}
				break;
			case 'Q': bst1.indentPrint(display, 0); //printing BST 1 with indentation
				break;
			case 'T': bst2.indentPrint(display, 0); //printing BST 2 with indentation
				break;
			case 'H': //printing helper
			{
				cout << "-- List Options --" << endl;
				cout << "U - Unsorted List in Hash Table Sequence" << endl;
				cout << "P - Sorted List by ID" << endl;
				cout << "S - Sorted List by State" << endl;
				cout << "Q - ID indented tree" << endl;
				cout << "T - State indented tree" << endl;
				cout << "H - Help" << endl;
				cout << "E - Exit" << endl;
			}
				break;
			default: cout << "Invalid choice. Try again." << endl;
			}
		}
		else
			cout << "Invalid input. Try again." << endl;

		cout << endl << "Enter your choice: ";
		getline(cin, choice);
		choice[0] = toupper(choice[0]);
	}
}

/* This function searches for data entered by user by ID or state, until user exits. */
void searchData(HashTable &ht, BinarySearchTree<Incidents> &bst1, BinarySearchTree<Incidents> &bst2, Incidents &incident, Incidents *res)
{
	bool found = false; 
	string choice;
	string entry;
	
	cout << endl << "Choose one of the following: " << endl;
	cout << "P - Search by ID" << endl;
	cout << "S - Search by State" << endl;
	cout << "E - Exit" << endl;
	cout << endl << "Enter your choice: ";

	getline(cin, choice);
	choice[0] = toupper(choice[0]);
	while (choice[0] != 'E')
	{
		if (inputValidation(choice) == true)
		{
			switch (choice[0])
			{
			case 'P':
			{
				cout << endl << "Enter ID to search: ";
				getline(cin, entry);
				cout << endl;

				found = ht.searchNode(entry, incident);
				if (found == true)
				{
					printHeader();
					display(incident);
				}
				else
					cout << "Not found" << endl;

			}
			break;
			case 'S':
			{
				cout << endl << "Enter State initials to search: ";
				getline(cin, entry);
				//if user enters in lowercase, capitalize
				entry[0] = toupper(entry[0]);
				entry[1] = toupper(entry[1]);
				 
				Incidents inc(" ", entry, " ", 0, " ", " ");
				int c = 0; //number of found nodes
				found = bst2.getEntry(inc, res, c, compareState); 
				//res returns an array with all results and c returns the number of nodes found
				
				if(found==true)
				{
					printHeader();
					for (int i = 0; i < c; i++)
					{
						display(res[i]);
					}
				}				
				else
					cout << endl << "Not found." << endl;
			}
			break;
			default: cout << endl << "Invalid choice. Try again." << endl;
			} //end switch
		} // end if
		else
			cout << "Invalid input" << endl;
		cout << "\nEnter your choice: ";
		getline(cin, choice);
		choice[0] = toupper(choice[0]);
	}
}

/* This function helps write all data to the file. */
void writeFile(Incidents &incident, ofstream &obj)
{
	obj << incident.getID() << "," << incident.getState() << "," << incident.getDate() << "," << incident.getFatalities() << "," << incident.getRace() << "," << incident.getGender() << endl;

}

/* This function compares two IDs. If both are equal, returns 0. 
   If left > right, return 1. If right > left, return -1. */
int compareID(const Incidents &one, const Incidents &two)
{
	if (one.getID() == two.getID())
		return 0;
	if (one.getID() > two.getID())
		return 1;
	if (one.getID() < two.getID())
		return -1;
}

/* This function compares two states along with their IDs. If both are equal, compare their IDs.
If left > right, return 1. If right > left, return -1. */
int comparePerfect(const Incidents &one, const Incidents &two)
{
	if (one.getState() == two.getState())
	{
		if (two.getID() != " ")
		{
			if (one.getID() > two.getID())
				return 1;
			if (one.getID() < two.getID())
				return -1;
		}
		
		return 0;
	}
	if (one.getState() > two.getState())
		return 1;
	if (one.getState() < two.getState())
		return -1;
}

/* This function compares two states. If both are equal, return 0.
If left > right, return 1. If right > left, return -1. */
int compareState(const Incidents &one, const Incidents &two)
{
	if (one.getState() == two.getState())
	{
		return 0;
	}
	if (one.getState() > two.getState())
		return 1;
	if (one.getState() < two.getState())
		return -1;
}