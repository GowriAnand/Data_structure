#pragma once
//including the packages needed for compilation
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//defining the node structure
template<class T>
struct Node
{
	Node* next = NULL;
	T len = 0;
	T values[8] = { };
};

//Class definition
template<class T>
class Header
{
public:
	Header();
	~Header();
	Node<T>* head;
	Node<T>* tail;

	int nodeCount = 0;
	int len = 0;
	int getNodeCount();
	int getNodeLen(T i);
	int getValue(T i, T j);

	void append(T elem);
	bool IsEmpty();
	void print();
	int GetLength();
	T GetIndex(int i);
	T* Search(T elem);
	void Remove(T elem);
	void updateArray(Node<T>* current, int j);
};

//Constructor definition
template<class T>
Header<T>::Header()
{
	head = nullptr;
	tail = nullptr;
}

//Desctructor definition
template<class T>
Header<T>::~Header()
{
	while (head != nullptr) {
		Node<T>* tmp = head;
		head = head->next;
		delete tmp;
	}
}

//Function that updates the value of array of the node
template<class T>
void Header<T>::updateArray(Node<T>* current, int j)
{
	int i;
	for (i = j; i < current->len; i++)
	{
		current->values[i] = current->values[i + 1];
	}
	current->len--;
	len--;
	current->values[current->len] = NULL;
}

//Function that returns the total number of nodes
template<class T>
int Header<T>::getNodeCount()
{
	return nodeCount;
}

//Function that returns the lengh of the node
template<class T>
int Header<T>::getNodeLen(T i)
{
	Node<T>* current = head;
	for (int j = 0; j < nodeCount; j++)
	{
		if (j == i)
			return current->len;
		current = current->next;
	}
	return -1;
}

//Returns the value of the matching node and node index
template<class T>
int Header<T>::getValue(T mynode, T mynodeInd)
{
	Node<T>* current = head;
	for (int j = 0; j < nodeCount; j++)
	{
		if (j == mynode)
			return current->values[mynodeInd];
		current = current->next;
	}
	return -1;
}

//Definition of the append function
template<class T>
void Header<T>::append(T elem)
{
	//checking if the list is empty. This will happen only when the list is empty
	if (IsEmpty())
	{
		Node<T>* newNode = new Node<T>;
		nodeCount++;
		newNode->next = nullptr;
		head = newNode;
		tail = head;
		newNode->values[newNode->len] = elem;
		newNode->len++;
		len++;
	}
	else
	{
		if (tail->len < 8)
		{
			tail->values[tail->len] = elem;
			tail->len++;
			len++;
		}
		else
		{
			Node<T>* newNode = new Node<T>;
			nodeCount++;
			tail->next = newNode;
			newNode->next = nullptr;
			tail = newNode;
			newNode->values[newNode->len] = elem;
			newNode->len++;
			len++;
		}
	}
}

//Function to check if there are no nodes in the linked list
template<class T>
bool Header<T>::IsEmpty()
{
	return head == nullptr;
}

//Function print to print the nodes and its contents
template<class T>
void Header<T>::print()
{
	Node<T>* temp = head;
	for (int i = 0; i < nodeCount; i++)
	{
		cout << "node# " << i + 1 << endl;
		for (int j = 0; j < temp->len; j++)
			cout << temp->values[j] << endl;
		temp = temp->next;
	}
}

//Function to return the length of the node
template<class T>
int Header<T>::GetLength()
{
	return len;
}

//Function to get the value in the index specified 
template<class T>
T Header<T>::GetIndex(int x)
{
	Node<T>* current = head;
	int temp = x - current->len;

	//return if the index requested is more than the existing total length of the items in all the nodes
	if (len < x)
		return -9999;
	else
	{
		//checking each node if the index lies within that array
		for (int i = 0; i < nodeCount; i++)
		{
			if (temp > 0)
			{
				current = current->next;
				temp = temp - current->len;
			}
			else
				return current->values[current->len + temp];
		}
		return -9999;
	}
}

//Function to search for the item given and return if it 
//exists else returns null pointer
template<class T>
T* Header<T>::Search(T elem)
{
	Node<T>* current = head;
	T j, i;
	for (i = 0; i < nodeCount; i++)
	{
		for (j = 0; j < current->len; j++)
		{
			if (current->values[j] == elem)
				return new T(current->values[j]);
		}
		current = current->next;
	}
	return nullptr;
}

//Function to remove an item if it exits
template<class T>
void Header<T>::Remove(T elem)
{
	Node<T>* current = head;
	Node<T>* prev = current;
	bool flag2;
	for (int i = 0; i < nodeCount; i++)
	{
		flag2 = false;
		for (int j = 0; j < current->len; j++)
		{
			if (current->values[j] == elem)
			{
				//For the case of 1st node in the list
				if (current == head)
				{
					if (head->next == nullptr)
					{
						//if the node contains array of only 1 item which will be removed, then delete the node
						//else remove the item from the array and update the array with moving its elements to its previous position
						if (head->len == 1)
						{
							len--;
							nodeCount--;
							head = tail = current = prev = nullptr;
							flag2 = true;
							break;
						}
						else
						{
							updateArray(current, j);
							break;
						}
					}
					else
					{
						if ((head->len == 1) && (head->next != nullptr))
						{
							head = head->next;
							current = nullptr;
							len--;
							nodeCount--;
							flag2 = true;
							break;
						}
						else
						{
							updateArray(current, j);
							break;
						}
					}
				}
				//for the case of last node
				else if (current->next == nullptr)
				{
					if (current->len == 1)
					{
						tail = prev;
						current = nullptr;
						prev->next = nullptr;
						len--;
						nodeCount--;
						flag2 = true;
						break;
					}
					else
					{
						updateArray(current, j);
						break;
					}
				}
				//for the case of intermediate nodes
				else
				{
					if (current->len == 1)
					{
						prev->next = current->next;
						current = nullptr;
						len--;
						nodeCount--;
						flag2 = true;
						break;
					}
					else
					{
						updateArray(current, j);
						break;
					}
				}
			}
		}
		if (!flag2)
		{
			prev = current;
			current = current->next;
		}
	}
}