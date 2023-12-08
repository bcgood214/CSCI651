#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "BPlusTree.h"

using namespace std;

void printTree(Node* n) {
	if (n->isLeaf) {
		int i;
		for (i = 0; i < n->keys.size(); ++i) {
			cout << n->keys.at(i) << " . ";
		}
	}
	else {
		int i;
		for (i = 0; i < n->links.size(); ++i) {
			printTree(n->links.at(i).leftPtr);
			printTree(n->links.at(i).rightPtr);
		}
	}
	cout << endl;
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

	tree.insert(11, "a");
	tree.insert(6, "b");
	tree.insert(2, "b");
	tree.insert(4, "b");
	tree.insert(9, "d");
	//tree.insert(6, "c");
	//tree.insert(2, "It is nice to see you again.");

	//tree.insert(16, "Would you kindly...");
	//tree.insert(19, "Would you kindly...");
	//tree.insert(22, "Would you kindly...");
	//tree.insert(25, "Would you kindly...");
	//tree.insert(28, "Would you kindly...");
	//tree.insert(21, "Hello, World");
	//tree.insert(18, "Hello, World");
	//tree.insert(32, "Hello, World");
	//tree.insert(35, "Hello, World");

	printTree(tree.root);


	return true;

}

Node* genLeafNode(int d) {
	Node* n = new Node();
	n->isLeaf = true;

	for (int i = 0; i < d; ++i) {
		BPlusData* d = new BPlusData;
		d->key = i;
		d->data = "Hello, world";
		n->data.push_back(d);
		n->keys.push_back(i);
	}

	return n;
}
int main() {
	
	Node* n = new Node();
	n->isLeaf = false;

	Node* left = new Node();
	left->isLeaf = false;

	Node* right = new Node();
	right->isLeaf = false;

	Node* l1 = genLeafNode(4);
	Node* l2 = genLeafNode(4);
	Node* l3 = genLeafNode(4);
	Node* l4 = genLeafNode(4);
	Node* l5 = genLeafNode(4);
	Node* l6 = genLeafNode(4);
	Node* l7 = genLeafNode(4);
	Node* l8 = genLeafNode(4);

	n->insertInternalKey(1, l1, l2, false);
	n->insertInternalKey(15, l3, l4, false);
	n->insertInternalKey(21, l5, l6, false);
	n->insertInternalKey(19, l7, l8, false);

	Node* father = new Node();
	father->isLeaf = false;

	n->parent = father;

	n->splitInternalNode();

	//cout << father->keys.at(0) << endl;
	//cout << father->links.at(0).leftPtr->keys.at(1) << endl;

	//cout << n->keys.at(1) << endl;

	printTree(father);
	

	return 0;
}