#include "Node.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Node::Node()
{
	Node::degree = 0;
	Node::data;
	//Node* firstNode = nullptr;
	Node::links;
	Node::count = 0;
	Node::values;
	Node::isLeaf = false;
	
}

bool Node::insert(int value, std::string data)
{
	if (isLeaf && Node::count < Node::degree) {
		bool inserted = false;
		int pos = 0;
		for (auto i = Node::values.begin(); i != Node::values.end(); ++i) {
			if (value < *i) {
				Node::values.insert(Node::values.begin() + pos, value);
				Node::data.insert(Node::data.begin() + pos, data);
				inserted = true;
				break;
			}
			pos++;
		}
		if (!inserted) {
			Node::values.push_back(value);
			Node::data.push_back(data);
		}
		Node::count++;

		return true;
	}
	else if (!isLeaf) {
		bool inserted = false;
		int pos = 0;
		for (auto i = Node::values.begin(); i != Node::values.end(); ++i) {
			if (value < *i) {
				inserted = Node::links.at(pos)->insert(value, data);
				// TODO: Node splitting calls can be placed in this block
				inserted = true;
				break;
			}
			pos++;
		}
		if (!inserted) {
			inserted = Node::links.at(pos + 1)->insert(value, data);
			// It appears node splitting calls will be needed here as well
		}
		Node::count++;

		return true;
	}
	return false;
}

bool Node::checkLeaf()
{
	return Node::isLeaf;
}

void Node::setLeaf(bool isLeaf)
{
	Node::isLeaf = isLeaf;
}

void Node::setDegree(int degree)
{
	Node::degree = degree;
}

int Node::getDegree()
{
	return Node::degree;
}

int Node::getValue(int position)
{
	return Node::values.at(position);
}

void Node::setValue(int value, int position)
{
	Node::values[position] = value;
}

int Node::valueInsertion(int value)
{
	int i;
	bool inserted = false;
	if (Node::count == 0) Node::count = 1;
	for (i = 0; i < Node::count; ++i) {
		if (Node::values.at(i) > value) {
			Node::values.insert(Node::values.begin() + i, value);
			Node::count++;
			inserted = true;
			break;
		}
	}
	if (Node::count == 1) Node::count--;

	if (!inserted && Node::count < Node::degree) {
		Node::values.push_back(value);
		Node::count++;
	}

	return i;
}

void Node::setData(std::string data, int position)
{
	Node::data[position] = data;
}

int Node::getCount()
{
	return Node::count;
}

std::string Node::getData(int position)
{
	return Node::data[position];
}

void Node::setLink(Node* node, int position)
{
	Node::links[position] = node;
}

void Node::addLink(Node* node, int position)
{
	if (position == -1) {
		Node::links.push_back(node);
	}
	else {
		Node::links.insert(Node::links.begin() + position, node);
	}
}

int Node::arrangeLink(Node* node)
{
	int firstVal = node->getValue(0);
	int pos = 0;
	bool inserted = false;
	for (auto i = Node::values.begin(); i != Node::values.end(); ++i) {
		if (*i > firstVal) {
			Node::links.insert(Node::links.begin() + pos, node);
			inserted = true;
			break;
		}

		pos++;
	}

	if (!inserted) {
		Node::links.insert(Node::links.begin() + pos, node);
		inserted = true;
	}

	return pos;
}

void Node::pushValue(int value)
{
	Node::values.push_back(value);
	Node::count++;
	sort(Node::values.begin(), Node::values.end());
}

Node* Node::getLink(int position)
{
	return Node::links[position];
}

void Node::linkInsertion(int value, int position, Node* left, Node* right)
{
	Node::values.insert(Node::values.begin() + position, value);
	Node::links.insert(Node::links.begin() + position, left);
	Node::links.insert(Node::links.begin() + position + 1, right);
}

void Node::pushBack(int ind)
{
	for (int i = Node::degree - 2; i >= ind; --i) {
		Node::values[i + 1] = Node::values[i];
	}

	if (Node::checkLeaf()) {
		for (int i = Node::degree - 2; i >= ind; --i) {
			Node::data[i + 1] = Node::data[i];
		}
	}
	else {
		for (int i = Node::degree - 1; i >= ind; --i) {
			Node::links[i + 1] = Node::links[i];
		}
	}
}

dataSplit splitDataNode(Node* node, int value, std::string data, int rootValue)
{
	Node* first = new Node();
	Node* second = new Node();
	int middlePos = (int)node->getCount() / 2;
	int pivotValue = node->getValue(middlePos);
	int degree = node->getDegree();

	first->setDegree(degree);
	first->setLeaf(true);
	second->setDegree(degree);
	second->setLeaf(true);

	for (int i = 0; i <= degree; ++i) {
		if (i == degree) {
			if (value > pivotValue) {
				second->insert(value, data);
			}
			else if (value == pivotValue && pivotValue >= rootValue) {
				second->insert(value, data);
			}
			else {
				first->insert(value, data);
			}
		}
		else {
			if (node->getValue(i) < pivotValue) {
				first->insert(node->getValue(i), node->getData(i));
			}
			else if (node->getValue(i) == pivotValue && pivotValue < rootValue) {
				first->insert(node->getValue(i), node->getData(i));
			}
			else {
				second->insert(node->getValue(i), node->getData(i));
			}
		}
	}

	dataSplit result;

	result.nodes.push_back(first);
	result.nodes.push_back(second);
	result.middleValue = pivotValue;

	return result;
}
internalSplit splitInternalNode(Node* parent, Node* left, Node* right, int newValue, int oldLink)
{
	return internalSplit();
}
/*
internalSplit splitInternalNode(Node* parent, Node* left, Node* right, int newValue, int oldLink) {
	Node* first = new Node();
	Node* second = new Node();
	int degree = parent->getDegree();
	vector<int> allVals = orderValues(parent, newValue, parent->getCount() + 1);
	int middlePos = (int)allVals.size() / 2;
	int pivotValue = parent->getValue(middlePos);

	first->setDegree(degree);
	first->setLeaf(false);
	second->setDegree(degree);
	second->setLeaf(false);

	//first->pushValue(-1);
	//second->pushValue(-1);

	for (int i = 0; i <= degree; ++i) {
		cout << "In the body for iteration #" << i << endl;
		if (i == degree) {
			if (newValue > pivotValue) {
				int valPos = second->valueInsertion(newValue);
				second->addLink(left, valPos);
				second->addLink(right, valPos + 1);
			}
			else {
				int valPos = first->valueInsertion(newValue);
				first->addLink(left, valPos);
				first->addLink(right, valPos + 1);
			}
		}
		else if (i == oldLink) {
			if (parent->getValue(i) < pivotValue) {
				first->valueInsertion(parent->valueInsertion(i));
			}
			else {
				second->valueInsertion(parent->getValue(i));
			}
		}
		else {
			if (parent->getValue(i) < pivotValue) {
				int valPos = first->valueInsertion(parent->getValue(i));
				first->addLink(parent->getLink(valPos), valPos);
			}
			else {
				int valPos = second->valueInsertion(parent->getValue(i));
				second->addLink(parent->getLink(valPos), valPos);
			}
		}
	}

	internalSplit result;
	result.nodes.push_back(first);
	result.nodes.push_back(second);
	result.value = pivotValue;
	return result;
}
*/

vector<Node*> arrangeLinks(vector<Node*> nodes) {
	vector<int> firstVals;
	int nSize = nodes.size();

	for (int i = 0; i < nSize; ++i) {
		firstVals.push_back(nodes.at(i)->getValue(0));
	}

	for (int i = 0; i < nSize; ++i) {
		for (int j = i+1; j < nSize; ++j) {
			if (firstVals.at(j) < firstVals.at(i)) {
				iter_swap(firstVals.begin() + i, firstVals.begin() + j);
				iter_swap(nodes.begin() + i, nodes.begin() + j);
			}
		}
	}

	return nodes;
}

/*internalSplit splitInternalNode(Node* parent, Node* left, Node* right, int newValue, int oldLink) {
	Node* first = new Node();
	Node* second = new Node();
	int degree = parent->getDegree();
	vector<int> allVals = orderValues(parent, newValue, degree + 1);
	int middlePos = (int)allVals.size() / 2;
	vector<Node*> allLinks;
	
	// filling allLinks
	for (int i = 0; i <= degree; ++i) {
		if (i != oldLink) {
			allLinks.push_back(parent->getLink(i));
		}
	}
	allLinks.push_back(left);
	allLinks.push_back(right);
	vector<Node*> arrangedLinks = arrangeLinks(allLinks);

	first->setDegree(degree);
	first->setLeaf(false);
	second->setDegree(degree);
	second->setLeaf(false);

	int i;
	for (i = 0; i < middlePos; ++i) {
		first->pushValue(allVals.at(i));
		first->addLink(arrangedLinks.at(i), -1);

	}
	first->addLink(arrangedLinks.at(i + 1), -1);

	int j;
	for (j = middlePos + 1; j < allVals.size(); ++j) {
		second->pushValue(allVals.at(j));
		second->addLink(arrangedLinks.at(j), -1);
	}
	second->addLink(arrangedLinks.at(j + 1), -1);

	internalSplit result;
	result.nodes.push_back(first);
	result.nodes.push_back(second);
	result.value = allVals.at(middlePos);

	return result;
}
*/

vector<int> orderValues(Node* n, int newValue, int total)
{
	vector<int> cumulative;
	for (int i = 0; i < total; ++i) {
		if (i != total - 1) {
			cumulative.push_back(n->getValue(i));
		}
		else {
			cumulative.push_back(newValue);
		}
	}
	sort(cumulative.begin(), cumulative.end());
	return cumulative;
}
