#pragma once
using namespace std;

template <class KeyType, class ItemType>
struct Node {
	KeyType key;
	ItemType item;
	Node<KeyType, ItemType>* left;
	Node<KeyType, ItemType>* right;
};

template <class KeyType, class ItemType>
class TreeT
{
public:
	TreeT();
	~TreeT();
	ItemType x;

	void Add(KeyType newKey, ItemType newItem);
	bool Remove(KeyType newKey);
	bool Contains(KeyType key);
	bool IsEmpty();
	ItemType getItem(KeyType key);

	int Size();
	void Traverse(void visit(ItemType& item, ofstream& ), ofstream& myout) const;

private:
	Node<KeyType, ItemType>* root;
	int len;
	void Destroy(Node<KeyType, ItemType>* node);
	bool RemoveHelper(Node<KeyType, ItemType>* node, KeyType newKey);void preorder(void visit(ItemType&, ofstream&), Node<KeyType, ItemType>* node, ofstream& myout) const;
};

template <class KeyType, class ItemType>
TreeT<KeyType, ItemType>::TreeT()
{
	len = 0;
	root = 0;
}

template <class KeyType, class ItemType>
TreeT<KeyType, ItemType>::~TreeT()
{
	Destroy(root);
}

template <class KeyType, class ItemType>
void TreeT<KeyType, ItemType>::Add(KeyType newKey, ItemType newItem)
{
	Node<KeyType, ItemType>* newNode = new Node<KeyType, ItemType>;
	newNode->key = newKey;
	newNode->item = newItem;
	newNode->left = newNode->right = nullptr;

	if (IsEmpty()) {
		root = newNode;
		len = 1;
		return;
	}

	Node<KeyType, ItemType>* cur = root;
	while (cur)
	{
		if (newKey < cur->key)
		{			// left
			if (cur->left == nullptr)
			{
				cur->left = newNode;
				break;
			}
			cur = cur->left;
		}
		else if (newKey > cur->key) {	// right
			if (cur->right == nullptr) {
				cur->right = newNode;
				break;
			}
			cur = cur->right;
		}
		else if (newKey == cur->key && newItem != cur->item)
		{
			cur->item = newItem;
		}
		else
		{		// Equal
			delete newNode;		// Didn't use the node, so delete it...
			return;
		}
	}
	len++;
}

template <class KeyType, class ItemType>
bool TreeT<KeyType, ItemType>::Remove(KeyType newKey)
{
	return RemoveHelper(root, newKey);
}

template <class KeyType, class ItemType>
bool TreeT<KeyType, ItemType>::Contains(KeyType key)
{
	if (!root)
		return false;
	Node<KeyType, ItemType>* cur = root;
	while (cur) {
		if (key < cur->key)        // left
			cur = cur->left;
		else if (key > cur->key)   // right
			cur = cur->right;
		else 		               // equal... Found it!
			return true;
	}
	return false;
}

template <class KeyType, class ItemType>
bool TreeT<KeyType, ItemType>::IsEmpty()
{
	return len == 0;
}

template <class KeyType, class ItemType>
int TreeT<KeyType, ItemType>::Size()
{
	return len;
}

template<class KeyType, class ItemType>
inline void TreeT<KeyType, ItemType>::Traverse(void visit(ItemType& item, ofstream&), ofstream& myout) const
{
	preorder(visit, root, myout);
}

/*
template <class KeyType, class ItemType>
void TreeT<KeyType, ItemType>::Traverse(void visit(ItemType&)) const
{
	preorder(visit, root);
}*/

template <class KeyType, class ItemType>
void TreeT<KeyType, ItemType>::Destroy(Node<T>* node)
{
	if (node == nullptr)
		return;

	Destroy(node->left);
	Destroy(node->right);
	delete node;
}

template <class KeyType, class ItemType>
bool TreeT<KeyType, ItemType>::RemoveHelper(Node<KeyType, ItemType>* node, KeyType newKey)
{
	bool flag = false;

	Node<KeyType, ItemType>* par = nullptr;		// No parent initially
	Node<KeyType, ItemType>* cur = node;		// Start at provided node
	while (cur) {
		if (newKey == cur->key) {	// Remove Case...
			if (!cur->left && !cur->right) {	// Leaf (no children)
				if (!par) // Node is root
				{
					cur->key = 0;
					node = nullptr;
				}
				else if (par->left == cur)
					par->left = nullptr;
				else
					par->right = nullptr;
				len--;
				flag = true;
			}
			else if (!cur->left && cur->right) { // Child on right
				if (!par) // Node is root
					node = cur->right;
				else if (par->left == cur)
					par->left = cur->right;
				else
					par->right = cur->right;
				len--;
				flag = true;
			}
			else if (cur->left && !cur->right) { // Child on Left
				if (!par) // Node is root
					node = cur->left;
				else if (par->left == cur)
					par->left = cur->left;
				else
					par->right = cur->left;
				len--;
				flag = true;
			}
			else {								// Two Children
				Node<KeyType, ItemType>* suc = cur->right;		// On the right branch...
				while (suc->left)				// travel as left as possible
					suc = suc->left;
				KeyType suckey = suc->key;			// Remember the value of the successor
				ItemType sucitem = suc->item;			// Remember the value of the successor
				RemoveHelper(node, suckey);	// Remove the successor node
				cur->key = suckey;			// Copy the value of the successor node back
				cur->item = sucitem;
				flag = true;	// Copy the value of the successor node back
			}
			return flag;
		}
		else if (newKey < cur->key) {
			par = cur;
			cur = cur->left;
		}
		else {
			par = cur;
			cur = cur->right;
		}
	}
	return flag;
}

//to print the binary tree in the pre order 
template <class KeyType, class ItemType>
void TreeT<KeyType, ItemType>::preorder(void visit(ItemType&, ofstream&), Node<KeyType, ItemType>* node, ofstream& myout) const
{
	if (node == nullptr)
		return;

	visit(node->item, myout);
	preorder(visit, node->left, myout);
	preorder(visit, node->right, myout);
}
template<class KeyType, class ItemType>
ItemType TreeT<KeyType, ItemType>::getItem(KeyType key)
{
	Node<KeyType, ItemType>* cur = root;
	while (cur)
	{
		if (key < cur->key)			// left
			cur = cur->left;
		else if (key > cur->key)	// right
			cur = cur->right;
		else
		{			// equal... Found it!
			x = cur->item;
			return x;
		}
	}
	string y = "null";
	return y;
}