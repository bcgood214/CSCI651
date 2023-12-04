#include "Node.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Node::Node()
{
	Node::isLeaf = false;
}

vector<int> sortNewKey(vector<int> keys, int newKey)
{
	keys.push_back(newKey);
	sort(keys.begin(), keys.end());
	return keys;
}

dataSplit splitDataNode(Node* node, int key, string data)
{
	vector<int> allKeys = sortNewKey(node->keys, key);
	int middlePos = (int)allKeys.size() / 2;
	int middleValue = allKeys.at(middlePos);
	int degree = node->keys.size();

	Node* left = new Node();
	Node* right = new Node();
	left->isLeaf = true;
	right->isLeaf = true;

	bool* inserted = new bool[node->data.size()];
	for (int i = 0; i < node->data.size(); ++i) {
		inserted[i] = false;
	}

	int pos = 0;
	for (auto i = node->keys.begin(); i != node->keys.end(); ++i) {
		if (*i < middleValue && pos < degree) {
			left->keys.push_back(*i);
			for (int j = 0; j < degree; ++j) {
				if (node->data.at(j)->key == *i && !inserted[pos]) {
					/*
					BPlusData* data = new BPlusData();
					data->key = *i;
					data->data = node->data.at(j)->data;
					*/
					left->data.push_back(node->data.at(j));
					inserted[pos] = true;
				}
			}
		}
		else {
			right->keys.push_back(*i);
			for (int j = 0; j < degree; ++j) {
				if (node->data.at(j)->key == *i && !inserted[pos]) {
					/*
					BPlusData* data = new BPlusData();
					data->key = *i;
					data->data = node->data.at(j)->data;
					*/
					right->data.push_back(node->data.at(j));
					inserted[pos] = true;
				}
			}
		}
		pos++;
	}

	if (key < middleValue) {
		left->keys.push_back(key);
		BPlusData* newData = new BPlusData();
		newData->key = key;
		newData->data = data;
		left->data.push_back(newData);
	}
	else {
		right->keys.push_back(key);
		BPlusData* newData = new BPlusData();
		newData->key = key;
		newData->data = data;
		right->data.push_back(newData);
	}

	dataSplit ds;
	ds.nodes.push_back(left);
	ds.nodes.push_back(right);
	ds.middleValue = middleValue;

	return ds;
}

internalSplit splitInternalNode(Node* node, Node* left, Node* right, int key)
{
	vector<int> allKeys = sortNewKey(node->keys, key);
	int middlePos = (int)allKeys.size() / 2;
	int middleValue = allKeys.at(middlePos);
	int degree = node->keys.size();

	int i;
	for (i = 0; i < allKeys.size(); ++i) {
		if (allKeys.at(i) < middleValue) {
			left->keys.push_back(allKeys.at(i));
		}
		else if (allKeys.at(i) > middleValue) {
			right->keys.push_back(allKeys.at(i));
		}
	}

	return internalSplit();
}
