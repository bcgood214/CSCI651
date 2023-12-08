#include <iostream>
#include "BPlusTree.h"

using namespace std;

void BPlusTree::insert(int value, string data)
{
	if (BPlusTree::root->isLeaf) {
		BPlusTree::root->insertDataKey(value, data);
		if (BPlusTree::root->keys.size() > BPlusTree::maxLeafDegree) {
			Node* temp = BPlusTree::root;
			BPlusTree::root = new Node();
			BPlusTree::root->isLeaf = false;
			temp->parent = BPlusTree::root;
			temp->splitDataNode();
		}
	}
	else {
		BPlusTree::insertInternal(BPlusTree::root, value, data);
		while (BPlusTree::root->parent != nullptr) {
			BPlusTree::root = BPlusTree::root->parent;
		}
	}
}

void BPlusTree::insertInternal(Node* n, int key, string data)
{
	if (n->isLeaf) {
		n->insertDataKey(key, data);
		if (n->keys.size() > BPlusTree::maxLeafDegree) {
			n->splitDataNode();
		}
		return;
	}
	cout << "Size: " << n->links.size() << endl;
	int i;
	for (i = 0; i < n->links.size(); ++i) {
		if (n->links.at(i).key > key || n->links.at(i).rightNeighborKey < 0) {
			cout << "Inserting internal #1" << endl;
			BPlusTree::insertInternal(n->links.at(i).rightPtr, key, data);
		}
		else if (key < n->links.at(i).key) {
			cout << "Inserting internal #2" << endl;
			BPlusTree::insertInternal(n->links.at(i).leftPtr, key, data);

		}
		if (n->keys.size() > maxInternalDegree) {
			if (n->parent == nullptr) {
				n->parent = new Node();
				n->parent->isLeaf = false;
			}
			n->splitInternalNode();
		}
	}
}
