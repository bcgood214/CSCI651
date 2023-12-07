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
	int key;
	T* leftPtr;
	T* rightPtr;
	int leftNeighborKey;
	int leftNeighborPos;
	int rightNeighborKey;
	int rightNeighborPos;
};

class Node
{
public:
	Node();
	vector<int> keys;
	vector<BPlusData*> data;
	vector<Link<Node>> links;
	bool isLeaf;
	void insertDataKey(int key, string data);
	void insertInternalKey(int key, Node* left, Node* right, bool keyEntered);
	void placeInternalKey(Link<Node> newLink);
	Node* parent;
	void splitInternalNode();
	void splitDataNode();
	void pruneLinks();
	void setEndLink();
	void pruneData();
};

struct dataSplit {
	vector<Node*> nodes;
	int middleValue;
};

