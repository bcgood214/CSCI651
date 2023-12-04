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
internalSplit splitInternalNode(Node* node, Node* left, Node* right, int value);

