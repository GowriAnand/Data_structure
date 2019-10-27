// chunklist.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Including header files and standard packages.
#include "Header.h"
#include <string>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

//Start of the main function
int main()
{
	//File stream initializations and other initializations
	ofstream outFile;
	ifstream inFile;
	Header<int> myList;

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

	//Running the loop of instructions until quit is called
	while (command != "quit")
	{
		if (command == "append")
		{
			int num;
			inFile >> num;
			myList.append(num);
			outFile << "Appending " << num << endl;
		}
		if (command == "Remove")
		{
			int num;
			inFile >> num;
			myList.Remove(num);
			outFile << "Removing " << num << " if it exists" << endl;
		}
		else if (command == "print")
		{
			// Traversing based on node length, array length in each node
			myList.print();
			outFile << endl << "Printing Node and its values : " << endl;
			int myNodeCount = myList.getNodeCount();
			for (int m = 0; m < myNodeCount; m++)
			{
				int nLen = myList.getNodeLen(m);
				outFile << "Node # " << m + 1 << endl;

				for (int n = 0; n < nLen; n++)
				{
					int value = myList.getValue(m, n);
					outFile << value << "  ";
				}
				outFile << endl;
			}
			outFile << "\n";
		}
		else if (command == "Search")
		{
			int num;
			inFile >> num;
			int* check = myList.Search(num);

			if (check != nullptr)
				outFile << "Searched number found : " << *check << endl;
			else
				outFile << "Searched number not found and hence returning NULL : " << check << endl;
		}
		else if (command == "GetLength")
		{
			int out = myList.GetLength();
			outFile << "GetLength: " << out << endl;
		}
		else if (command == "GetIndex")
		{
			int num;
			inFile >> num;
			int index = myList.GetIndex(num);
			if (index == -9999)
			{
				outFile << "Index " << num << " does not exist " << endl;
			}
			else
			{
				outFile << "Index " << num << " exists and its value is : " << index << endl;
			}
		}
		inFile >> command;
	}
	return 0;
}