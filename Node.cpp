#include "Node.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template<class T>
inline Link<T>::Link()
{
	Link::leftPtr = nullptr;
	Link::leftPtr = nullptr;
	Link::leftNeighborKey = -1;
	Link::leftNeighborPos = -1;
	Link::leftNeighborKey = -1;
	Link::leftNeighborKey = -1;
}

Node::Node()
{
	Node::isLeaf = false;
	Node::parent = nullptr;
}

void Node::insertDataKey(int key, string data)
{
	BPlusData* d = new BPlusData();
	d->key = key;
	d->data = data;
	Node::data.push_back(d);
	Node::keys.push_back(key);
	sort(Node::keys.begin(), Node::keys.end());
}

void Node::insertInternalKey(int key, Node* left, Node* right, bool keyEntered)
{
	Link<Node> newLink;
	newLink.key = key;
	newLink.leftPtr = left;
	newLink.rightPtr = right;

	newLink.leftPtr->parent = this;
	newLink.rightPtr->parent = this;

	if (Node::keys.size() < 1) {
		Node::keys.push_back(key);
		Node::links.push_back(newLink);
		return;
	}

	Node::placeInternalKey(newLink);

	if (!keyEntered) {
		Node::keys.push_back(key);
		sort(Node::keys.begin(), Node::keys.end());
	}
}

void Node::placeInternalKey(Link<Node> newLink)
{
	int leftNeighbor = -1;
	int leftPos = 0;

	for (auto i = Node::keys.begin(); i != Node::keys.end(); ++i) {
		if (*i > leftNeighbor && *i <= newLink.key) {
			leftNeighbor = *i;
		}
		leftPos++;
	}

	int j;
	for (j = 0; j < Node::links.size(); ++j) {
		if (Node::links.at(j).key == leftNeighbor) {
			int temp = Node::links.at(j).rightNeighborKey;
			int tempPos = Node::links.at(j).rightNeighborPos;
			newLink.leftNeighborKey = leftNeighbor;
			newLink.leftNeighborPos = leftPos;
			newLink.rightNeighborKey = Node::links.at(j).rightNeighborKey;
			newLink.rightNeighborPos = Node::links.at(j).rightNeighborPos;
			Node::links.at(j).rightNeighborKey = newLink.key;
			Node::links.at(j).rightNeighborPos = Node::links.size() + 1;
			Node::links.at(j).rightPtr = newLink.leftPtr;

			if (temp > -1) {
				newLink.rightNeighborKey = temp;
				newLink.rightNeighborPos = tempPos;
				Node::links.at(tempPos).leftNeighborKey = newLink.key;
				Node::links.at(tempPos).leftNeighborPos = Node::links.size() + 1;
				Node::links.at(tempPos).leftPtr = newLink.rightPtr;

			}
		}
	}

	Node::links.push_back(newLink);
}

void Node::splitInternalNode()
{
	cout << "Split called" << endl;
	int middlePos = (int)Node::keys.size() / 2;
	int middleValue = Node::keys.at(middlePos);

	Node* second = new Node();
	second->isLeaf = false;

	// Place keys in new Node
	int i;
	for (i = 0; i < Node::keys.size(); ++i) {
		int temp = Node::keys.at(i);
		if (temp > middleValue) {
			second->keys.push_back(temp);
		}
	}

	// Place links in new node
	for (i = 0; i < second->keys.size(); ++i) {
		int temp = second->keys.at(i);
		int j;
		for (j = 0; j < Node::links.size(); ++j) {
			if (Node::links.at(j).key == i) {
				second->insertInternalKey(Node::links.at(j).key, Node::links.at(j).leftPtr, Node::links.at(j).rightPtr, true);
			}
		}
	}

	Node::keys.resize(middlePos);
	Node::pruneLinks();
	Node::setEndLink();

	if (Node::parent != nullptr) {
		Node::parent->insertInternalKey(middleValue, this, second, false);
	}
}

void Node::splitDataNode()
{
	int middlePos = (int)Node::keys.size() / 2;
	int middleValue = Node::keys.at(middlePos);

	Node* second = new Node();
	second->isLeaf = true;

	int i;
	for (i = 0; i < Node::keys.size(); ++i) {
		int temp = Node::keys.at(i);
		if (temp >= middleValue) {
			for (int j = 0; j < Node::data.size(); ++j) {
				if (Node::data.at(j)->key == temp) {
					second->insertDataKey(temp, Node::data.at(j)->data);
				}
			}
		}
	}

	Node::keys.resize(middlePos);
	Node::pruneData();

	if (Node::parent != nullptr) {
		Node::parent->insertInternalKey(middleValue, this, second, false);
	}
}

void Node::pruneLinks()
{
	int i;
	vector<int> deadNodes;
	for (i = 0; i < Node::links.size(); ++i) {
		int linkKey = Node::links.at(i).key;
		bool present = false;
		for (int j = 0; j < Node::keys.size(); ++j) {
			if (Node::keys.at(j) == linkKey) {
				present = true;
				break;
			}
		}
		if (!present) {
			deadNodes.push_back(i);
		}
	}

	for (auto p = deadNodes.begin(); p != deadNodes.end(); ++p) {
		Node::links.erase(Node::links.begin() + *p);
	}
}

void Node::setEndLink()
{
	int i;
	for (i = 0; i < Node::links.size(); ++i) {
		if (Node::links.at(i).key == Node::keys.back()) {
			Node::links.at(i).rightNeighborKey = -1;
			Node::links.at(i).rightNeighborPos = -1;
			break;
		}
	}
}

void Node::pruneData()
{
	int i;
	vector<int> deadNodes;
	for (i = 0; i < Node::data.size(); ++i) {
		int temp = Node::data.at(i)->key;
		bool present = false;
		for (int j = 0; j < Node::keys.size(); ++j) {
			if (Node::keys.at(j) == temp) {
				present = true;
				break;
			}
		}
		if (!present) {
			deadNodes.push_back(temp);
		}
	}

	int j;
	for (j = 0; j < deadNodes.size(); ++j) {
		int p;
		int value = deadNodes.at(j);
		int deadIndex = -1;
		for (p = 0; p < Node::data.size(); ++p) {
			if (Node::data.at(p)->key == value) {
				deadIndex = p;
				break;
			}
		}
		if (deadIndex != -1) {
			Node::data.erase(Node::data.begin() + deadIndex);
		}
	}
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
/*
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
*/
