#pragma once
#include <string>
#include "Node.h"

using namespace std;

class BPlusTree
{
public:
	int maxInternalDegree;
	int minInternalDegree;
	int maxLeafDegree;
	int minLeafDegree;
	Node* root;
	Node* newNode(int key, Node* left, Node* right);
	void insert(int value, string data);
};

internalSplit insertInternal(
	int value, string data, Node* node, int maxInternalDegree, int maxLeafDegree, bool isRoot, BPlusTree* tree
);

