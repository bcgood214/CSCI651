#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "BPlusTree.h"

using namespace std;

void printRoot(Node* r) {
	int i;
	for (i = 0; i < r->keys.size(); ++i) {
		cout << r->keys.at(i) << endl;
	}
	cout << "Beginning to print link values" << endl;
	for (i = 0; i < r->links.size(); ++i) {
		cout << r->links.at(i).leftOf << ", " << r->links.at(i).rightOf << endl;
	}
	cout << "End of print function" << endl;
}

void printTree(Node* n) {
	if (n->isLeaf) {
		int i;
		for (i = 0; i < n->keys.size(); ++i) {
			cout << n->keys.at(i) << ". ";
		}
		cout << endl;
	}
	else {
		int i;
		for (i = 0; i < n->keys.size(); ++i) {
			cout << n->keys.at(i) << ". ";
		}
		cout << endl;
		
		int j;
		for (j = 0; j < n->links.size(); ++j) {
			cout << "Left of " << n->links.at(j).leftOf << " and right of " << n->links.at(j).rightOf << ": ";
			printTree(n->links.at(j).ptr);
		}

	}
}

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
	printTree(tree.root);

	tree.insert(11, "a");
	tree.insert(13, "b");
	tree.insert(15, "c");
	tree.insert(2, "It is nice to see you again.");

	cout << "Now printing tree: " << endl;
	printTree(tree.root);

	tree.insert(16, "Would you kindly...");
	tree.insert(19, "Would you kindly...");
	tree.insert(22, "Would you kindly...");
	tree.insert(25, "Would you kindly...");
	tree.insert(28, "Would you kindly...");
	tree.insert(21, "Hello, World");
	tree.insert(18, "Hello, World");
	tree.insert(32, "Hello, World");
	tree.insert(35, "Hello, World");

	cout << "Now printing tree: " << endl;
	printTree(tree.root);


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
	*/

	/*
	Link<Node> l;
	l.leftOf = -1;
	l.rightOf = n->keys.back();
	l.ptr = nullptr;
	n->links.push_back(l);

	n->delKey(4);
	printRoot(n);
	*/

	/*
	Node* left = new Node();
	Node* right = new Node();
	left->isLeaf = false;
	right->isLeaf = false;

	internalSplit is = splitInternalNode(n, left, right, 6);

	is.nodes.at(1)->setLinks(6);

	cout << is.nodes.at(1)->keys.at(0) << endl;
	*/

	

	testBPlusTree();

	return 0;
}