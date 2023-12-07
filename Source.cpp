#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "BPlusTree.h"

using namespace std;

bool testBPlusTree() {
	Node* kernel = new Node();
	kernel->isLeaf = true;
	
	BPlusTree tree;
	tree.root = kernel;
	tree.maxInternalDegree = 4;
	tree.maxLeafDegree = 4;
	tree.minInternalDegree = 0;
	tree.minLeafDegree = 0;

	tree.insert(1, "Hello");
	tree.insert(3, "How is it going?");
	tree.insert(5, "Hello?");
	tree.insert(7, "Are you still there?");

	tree.insert(9, "Let's try this again.");

	tree.insert(2, "Hey!");
	tree.insert(11, "Okay");
	tree.insert(13, "Thank you for participating.");
	tree.insert(4, "That is cool.");


	cout << tree.root->links.at(2).ptr->keys.at(2) << endl;

	return true;

}
int main() {
	Node* n = new Node();
	n->isLeaf = false;

	/*
	for (int i = 0; i < 5; ++i) {
		n->keys.push_back(i);
		BPlusData* data = new BPlusData();
		data->key = i;
		data->data = "Hello World";
		n->data.push_back(data);
	}

	dataSplit ds = splitDataNode(n, 5, "Goodbye");
	*/

	// cout << ds.nodes.at(1)->data.at(2)->data << endl;

	/*
	int i;
	for (i = 0; i < 5; ++i) {
		n->keys.push_back(i);
		Link<Node> l;
		l.leftOf = i;
		l.ptr = nullptr;
		if (i > 0) {
			l.rightOf = i - 1;
		}
		n->links.push_back(l);
	}

	Node* left = new Node();
	Node* right = new Node();
	left->isLeaf = false;
	right->isLeaf = false;

	internalSplit is = splitInternalNode(n, left, right, 6);

	is.nodes.at(1)->setLinks(6);

	cout << is.value << endl;
	*/

	testBPlusTree();

	return 0;
}