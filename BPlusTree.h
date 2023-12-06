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

void insertInternal(int value, string data, Node* node);

