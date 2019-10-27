#pragma once

#include "TreeT.h"
#include<string>
#include<unordered_map>
using namespace std;

void display1(string& anItem, ofstream& myout)
{
	cout << "Displaying item - " << anItem << endl;
}

template<class KeyType, class ItemType>
class HashTable
{
public:
	HashTable();
	HashTable(int numBuckets);

	void Add(KeyType newKey, ItemType newItem);
	bool Remove(KeyType newKey);
	bool Contains(KeyType key);
	ItemType getItem(KeyType key);
	int Size();
	void traverse(void visit(ItemType&, ofstream&), ofstream&);
	int getHashIndex(const KeyType& key);

private:
	const int DEFAULT_BUCKET_NUM = 20;		// How many buckets by default
	TreeT<KeyType, ItemType>** buckets;
	int numBuckets;
	int numElems;							// How many elements stored in entire table
};

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable()
{
	buckets = new TreeT<KeyType, ItemType>* [DEFAULT_BUCKET_NUM];
	numBuckets = DEFAULT_BUCKET_NUM;
	numElems = 0;

	// for each bucket, set the i-th bucket equal to a new DictTree of type <KeyType, ItemType>
	for (int i = 0; i < DEFAULT_BUCKET_NUM; i++)
		buckets[i] = new TreeT<KeyType, ItemType>;
}

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(int numBucks)
{
	buckets = new TreeT<KeyType, ItemType>* [numBucks];
	numBuckets = numBucks;
	numElems = 0;
	// See previous constructor.  Use numBucks instead of DEFAULT_BUCKET_NUM.
	for (int i = 0; i < numBucks; i++)
		buckets[i] = new TreeT<KeyType, ItemType>;
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::Size()
{
	return numElems;
}

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::Add(KeyType key, ItemType item)
{
	// Get the hash bucket Index
	int index = getHashIndex(key);

	// If the hash table does not already contain key
	//    increase numElems by one
	if (!Contains(key))
		numElems++;

    // add key,item to the DictTree at a buckets index
	buckets[index]->Add(key, item);
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::Remove(KeyType key)
{
	// Get the hash Index
	int index = getHashIndex(key);

	if (Contains(key))
	{
		numElems--;
		buckets[index]->Remove(key);
		return true;
	}
	else
		return false;
}

template<class KeyType, class ItemType>
ItemType HashTable<KeyType, ItemType>::getItem(KeyType key)
{
	// Get the hash bucket Index
	int index = getHashIndex(key);
	return buckets[index]->getItem(key);
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::Contains(KeyType key)
{
	// Get the hash bucket Index
	int index = getHashIndex(key);
	if (buckets[index]->Contains(key))
		return true;
	else
		return false;
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getHashIndex(const KeyType& key)
{
	// We are creating a hash function type called hashFunction that hashes "KeyType."
	// First we create an an unordered_map object for our KeyType and ItemType
	unordered_map<KeyType, ItemType> mapper;

	// Then we call the hash_function method to return the hash function
	// for the KeyType and assign it to 'hashFunction'
	typename unordered_map<KeyType, ItemType>::hasher hashFunction = mapper.hash_function();

	// static_cast needed since hashFunction returns an unsigned long
	return static_cast<int>(hashFunction(key) % numBuckets);
}

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::traverse(void visit(ItemType&, ofstream&), ofstream& myout)
{
	for (int i = 0; i < DEFAULT_BUCKET_NUM; i++)
		if (buckets[i]->Size() > 0)
			buckets[i]->Traverse(visit, myout);
}