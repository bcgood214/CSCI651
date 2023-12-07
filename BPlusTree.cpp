#include "BPlusTree.h"

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
	for (auto i = n->links.begin(); i != n->links.end(); ++i) {
		if (i->key > key || i->rightNeighborKey < 0) {
			BPlusTree::insertInternal(i->rightPtr, key, data);
		}
		else if (key < i->key) {
			BPlusTree::insertInternal(i->leftPtr, key, data);

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
