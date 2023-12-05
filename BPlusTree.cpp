#include "BPlusTree.h"

Node* BPlusTree::newNode(int key, Node* left, Node* right)
{
	Node* n = new Node();
	n->isLeaf = false;
	n->keys.push_back(key);
	Link<Node> l1;
	Link<Node> l2;
	l1.leftOf = key;
	l1.ptr = left;
	l2.rightOf = key;
	l2.ptr = right;
	n->links.push_back(l1);
	n->links.push_back(l2);

	return n;
}

void BPlusTree::insert(int value, string s)
{
	if (BPlusTree::root->isLeaf) {
		if (BPlusTree::root->keys.size() >= BPlusTree::maxLeafDegree) {
			dataSplit ds = splitDataNode(BPlusTree::root, value, s);
			BPlusTree::root = BPlusTree::newNode(ds.middleValue, ds.nodes.at(0), ds.nodes.at(1));
			BPlusTree::insert(value, s);
		}
		else {
			BPlusTree::root->keys.push_back(value);
			BPlusData* data = new BPlusData();
			data->key = value;
			data->data = s;
			BPlusTree::root->data.push_back(data);
		}
	}
	else {
		// TODO: internal node insertion
	}
}
