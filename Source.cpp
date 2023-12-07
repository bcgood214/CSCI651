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

	tree.insert(11, "a");
	tree.insert(13, "b");
	tree.insert(15, "c");
	tree.insert(2, "It is nice to see you again.");

	tree.insert(16, "Would you kindly...");
	tree.insert(19, "Would you kindly...");
	tree.insert(22, "Would you kindly...");
	tree.insert(25, "Would you kindly...");
	tree.insert(28, "Would you kindly...");
	tree.insert(21, "Hello, World");
	tree.insert(18, "Hello, World");
	tree.insert(32, "Hello, World");
	tree.insert(35, "Hello, World");

	cout << tree.root->keys.size();


	return true;

}
int main() {
	/*
	Node* n = new Node();
	n->isLeaf = false;

	Node* left = new Node();
	left->isLeaf = false;

	Node* right = new Node();
	right->isLeaf = false;

	left->insertDataKey(1, "Hello, World");
	left->insertDataKey(3, "Hello, World");
	left->insertDataKey(5, "Hello, World");
	left->insertDataKey(7, "Hello, World");

	right->insertDataKey(18, "Hello, World");
	right->insertDataKey(21, "Hello, World");
	right->insertDataKey(27, "Hello, World");
	right->insertDataKey(24, "Hello, World");

	n->insertInternalKey(1, left, right, false);
	*/

	testBPlusTree();

	return 0;
}