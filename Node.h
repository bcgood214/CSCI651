#pragma once
#include <string>
#include <vector>

using namespace std;

class BPlusData {
public:
	int key;
	string data;
};

template <class T>
class Link {
public:
	Link();
	int leftOf;
	int rightOf;
	T* ptr;
};

class Node
{
public:
	Node();
	vector<int> keys;
	vector<BPlusData*> data;
	vector<Link<Node>> links;
	bool isLeaf;
};

struct dataSplit {
	vector<Node*> nodes;
	int middleValue;
};

struct internalSplit {
	vector<Node*> nodes;
	int value;
};
struct newValues {
	vector<int> values;
	int pivot;
};

vector<int> sortNewKey(vector<int> keys, int newKey);
dataSplit splitDataNode(Node* node, int key, string data);
void assignLinks(Node* left, Node* right, vector<Link<Node>> links, int pivotValue);
internalSplit splitInternalNode(Node* node, Node* left, Node* right, int value);

