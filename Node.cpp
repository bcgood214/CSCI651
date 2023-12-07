#include "Node.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template<class T>
inline Link<T>::Link()
{
	Link::leftOf = -1;
	Link::rightOf = -1;
	Link::ptr = nullptr;
}

Node::Node()
{
	Node::isLeaf = false;
}

Node* Node::getNext(int value)
{
	for (auto i = Node::links.begin(); i != Node::links.end(); ++i) {
		if (value <= i->leftOf && i->rightOf == -1) {
			return i->ptr;
		}
		else if (value < i->leftOf && value >= i->rightOf) {
			return i->ptr;
		}
		else if (value >= i->rightOf && i->leftOf == -1) {
			return i->ptr;
		}
	}
	return nullptr;
}

void Node::setLinks(int key)
{
	int prior = -1;
	int latter = -1;

	int i;
	for (i = 0; i < Node::keys.size(); ++i) {
		if (Node::keys.at(i) == key) {
			if (i > 0) {
				prior = Node::keys.at(i - 1);
			}
			if (i < Node::keys.size() - 1) {
				latter = Node::keys.at(i + 1);
			}
		}
	}

	for (i = 0; i < Node::links.size(); ++i) {
		if (Node::links.at(i).leftOf == key) {
			Node::links.at(i).rightOf = prior;
		}
		else if (Node::links.at(i).rightOf == key) {
			Node::links.at(i).leftOf = latter;
		}
	}
}

void Node::removeOldLinks(int key)
{
	int v1 = -1;
	int v2 = -1;

	int i;

	for (i = 0; i < Node::keys.size(); ++i) {
		if (Node::keys.at(i) == key) {
			if (i > 0) {
				v1 = Node::keys.at(i - 1);
			}
			if (i < Node::keys.size() - 1) {
				v2 = Node::keys.at(i + 1);
			}
		}
	}

	for (i = 0; i < Node::links.size(); ++i) {
		Link<Node> l = Node::links.at(i);
		if (l.leftOf == v2 && l.rightOf == v1) {
			break;
		}
	}

	Node::links.erase(Node::links.begin() + i);
}

void Node::addLinks(int key, Node* left, Node* right)
{
	int prior = -1;
	int latter = -1;

	int i;
	for (i = 0; i < Node::keys.size(); ++i) {
		if (Node::keys.at(i) == key) {
			if (i > 0) {
				prior = Node::keys.at(i - 1);
			}
			if (i < Node::keys.size() - 1) {
				latter = Node::keys.at(i + 1);
			}
		}
	}

	for (i = 0; i < Node::links.size(); ++i) {
		if (Node::links.at(i).leftOf == latter && Node::links.at(i).rightOf == prior) {
			Node::links.at(i).leftOf = key;
			Node::links.at(i).ptr = left;
		}
	}

	Link<Node> l;
	l.ptr = right;
	l.leftOf = latter;
	l.rightOf = key;
	Node::links.push_back(l);
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

	vector<Link<Node>> links;

	for (auto i = node->links.begin(); i != node->links.end(); ++i) {
		links.push_back(*i);
	}

	Link<Node> linkLeft;
	Link<Node> linkRight;

	linkLeft.leftOf = key;
	linkLeft.ptr = left;
	linkRight.rightOf = key;
	linkRight.ptr = right;

	links.push_back(linkLeft);
	links.push_back(linkRight);

	Node* first = new Node();
	Node* second = new Node();

	first->isLeaf = false;
	second->isLeaf = false;
	first->keys = left->keys;
	second->keys = right->keys;

	assignLinks(first, second, links, middleValue);

	internalSplit is;
	is.nodes.push_back(first);
	is.nodes.push_back(second);
	is.value = middleValue;


	return is;
}

void assignLinks(Node* left, Node* right, vector<Link<Node>> links, int pivotValue)
{
	int i;
	for (i = 0; i < links.size(); ++i) {
		if (links.at(i).leftOf == -1) {
			right->links.push_back(links.at(i));
		}
		else if (links.at(i).leftOf <= pivotValue) {
			left->links.push_back(links.at(i));

		}
		else if (links.at(i).leftOf > pivotValue) {
			right->links.push_back(links.at(i));
		}
	}
}
