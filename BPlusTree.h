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
	void insert(int value, string data);
	void insertInternal(Node* n, int key, string data);
};

