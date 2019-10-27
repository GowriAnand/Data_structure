// TreeTemplateIter_F2019.cpp : Defines the entry point for the console application.

#include <iostream>
#include "TreeT.h"
#include "HashTable.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Used with traverse to print out all the elements in traverse
void Print(string& item)
{
	std::cout << "displaying item : " << item << "\n";
}

//to write the output to the text file
void display3(string& anItem, ofstream& myout)
{
	myout << "Displaying item - " << anItem << endl;
}


void display2(int& anItem)
{
	cout << "Displaying item - " << anItem << endl;
}

//to test the working of the tree
void TreeTest1(TreeT<int, string>* testTable, ofstream& myout)
{
	testTable->Add(60, "F");
	testTable->Add(70, "G");
	testTable->Add(40, "D");
	testTable->Add(80, "H");
	testTable->Add(30, "C");
	testTable->Add(50, "E");
	testTable->Add(10, "A");
	testTable->Add(20, "B");

	cout << "Traversing data items:\n";
	testTable->Traverse(display1, myout);

	testTable->Remove(10);  // A
	testTable->Remove(80);	// H
	testTable->Remove(40);	// D

	cout << "\nAfter Removing 10/A, 40/D & 80/H, traverse data items:\n";
	testTable->Traverse(display1, myout);

	cout << "\nTrying to remove 40/D again\n";
	if (testTable->Remove(40))
		cout << "Removed second 40 :-(\n\n";
	else
		cout << "Could not remove second 40 :-)\n\n";

	cout << "Getting key/item 20/B: " << testTable->getItem(20) << endl;
	cout << "Getting key/item 70/G: " << testTable->getItem(70) << endl;
	cout << "Getting key/item 50/E: " << testTable->getItem(50) << endl;
	cout << "Contains key/item 80/H: " << testTable->Contains(80) << endl;
	cout << "Contains key/item 00/??: " << testTable->Contains(00) << endl;

	cout << "\nAfter changing 20/B to 20/Z, traverse data items:\n";
	testTable->Add(20, "Z");
	testTable->Traverse(display1, myout);
}

// to test the working of hash table
void HashTest1(HashTable<int, string>* testTable, ofstream& myout)
{
	testTable->Add(60, "F");
	testTable->Add(70, "G");
	testTable->Add(40, "D");
	testTable->Add(80, "H");
	testTable->Add(30, "C");
	testTable->Add(50, "E");
	testTable->Add(10, "A");
	testTable->Add(20, "B");

	cout << "Traversing data items:\n";
	testTable->traverse(display1, myout);

	testTable->Remove(10);
	testTable->Remove(80);
	testTable->Remove(40);

	cout << "\nAfter Removing 10/A, 40/D & 80/H, traverse data items:\n";
	testTable->traverse(display1, myout);

	cout << "\nTrying to remove 40/D again\n";
	if (testTable->Remove(40))
		cout << "Removed second 40 :-(\n\n";
	else
		cout << "Could not remove second 40 :-)\n\n";

	cout << "Getting key/item 20/B: " << testTable->getItem(20) << endl;
	cout << "Getting key/item 70/G: " << testTable->getItem(70) << endl;
	cout << "Getting key/item 50/E: " << testTable->getItem(50) << endl;
	cout << "Contains key/item 80/H: " << testTable->Contains(80) << endl;
	cout << "Contains key/item 00/??: " << testTable->Contains(00) << endl;

	//testTable->clear();

	cout << "\nTrying to traverse after clear\n";
	testTable->traverse(display1, myout);
	cout << "If nothing displayed, that is good!\n";

	if (testTable->Remove(20))
		cout << "Removed 20 from an empty dictionary :-(\n\n";
	else
		cout << "Could not remove 20 from an empty dictionary :-)\n\n";
}

int main()
{
	//to take input from the text file and write output to the text file
	ofstream outFile;
	ifstream inFile;

	cout << "Testing DictTree" << endl << endl;
	TreeT<int, string>* tree1 = new TreeT<int, string>();
	TreeTest1(tree1, outFile);
	cout << "-----------------------------------------" << endl;
	cout << "Testing HashTree" << endl << endl;
	HashTable<int, string>* dict1 = new HashTable<int, string>();
	HashTest1(dict1, outFile);

	TreeT<int, string>* myTree = new TreeT<int, string>();
	HashTable<int, string>* myHash = new HashTable<int, string>();

	outFile.open("output.txt");
	inFile.open("unit_test.txt");	

	//Exit the program if the input or output file does not exist
	if (!inFile)
	{
		cout << "Input File not found!" << endl;
		exit(0);
	}
	if (!outFile)
	{
		cout << "Output File not found!" << endl;
		exit(0);
	}

	string command;
	inFile >> command;

	while (command != "quit")
	{
		if (command == "Add")
		{
			int num;
			string letter;
			inFile >> num;
			inFile >> letter;
			myHash->Add(num,letter);
			outFile << "Adding " << num << endl;
		}
		else if (command == "Remove")
		{
			int num;
			inFile >> num;
			myHash->Remove(num);
			outFile << "Removing " << num << endl;
		}
		else if (command == "getItem")
		{
			int num;
			inFile >> num;
			string a = myHash->getItem(num);
			outFile<< "the item of the key " << num << " is : " << a << endl;
		}
		else if (command == "Print")
		{
			myHash->traverse(display3, outFile);
		}
		else if (command == "Contains")
		{
			int num;
			inFile >> num;
			bool check = myHash->Contains(num);

			if (check==true)
				outFile << "Searched number found "<< num<< endl;
			else
				outFile << "Searched number not found " << num << endl;
		}
		else if (command == "Size")
		{
			int out = myHash->Size();
			outFile << "size: " << out << endl;
		}
		inFile >> command;
	}
	return 0;
}