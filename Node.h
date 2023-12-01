#pragma once
#include <string>
#include <vector>

using namespace std;
class Node
{
public:
	Node();
	bool insert(int value, std::string data);
	void delKey(int value);
	string search(int value);
	bool checkLeaf();
	void setLeaf(bool isLeaf);
	void setDegree(int degree);
	int getDegree();
	int getValue(int position);
	void setValue(int value, int position);
	int valueInsertion(int value);
	void setData(std::string data, int position);
	int getCount();
	string getData(int position);
	void setLink(Node* node, int position);
	void addLink(Node* node, int position);
	int arrangeLink(Node* node);
	void pushValue(int value);
	Node* getLink(int position);
	void linkInsertion(int value, int position, Node* left, Node* right);
private:
	int degree;
	vector<string> data;
	vector<Node*> links;
	vector<int> values;
	int count;
	bool isLeaf;
	void pushBack(int ind);
};

struct dataSplit {
	vector<Node*> nodes;
	int middleValue;
};

struct internalSplit {
	vector<Node*> nodes;
	int value;
};

vector<Node*> arrangeLinks(vector<Node*> nodes);
dataSplit splitDataNode(Node* node, int value, string data, int rootValue);
internalSplit splitInternalNode(Node* parent, Node* left, Node* right, int newValue, int oldLink);
vector<int> orderValues(Node* n, int newValue, int total);

