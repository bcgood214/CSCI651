#include "BPlusTree.h"

Node* BPlusTree::newNode(int key, Node* left, Node* right)
{
	Node* n = new Node();
	n->isLeaf = false;
	n->keys.push_back(key);
	Link<Node> l1;
	Link<Node> l2;
	l1.leftOf = key;
	l1.rightOf = -1;
	l1.ptr = left;
	l2.rightOf = key;
	l2.leftOf = -1;
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
			//BPlusTree::insert(value, s);
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
		internalSplit is = insertInternal(value, s, BPlusTree::root, BPlusTree::maxInternalDegree, BPlusTree::maxLeafDegree, true, this);
		if (is.value != -10) {
			if (BPlusTree::root->keys.size() < maxInternalDegree) {
				BPlusTree::root->keys = sortNewKey(BPlusTree::root->keys, is.value);
				BPlusTree::root->addLinks(is.value, is.nodes.at(0), is.nodes.at(1));
			}
			else {
				internalSplit nextNode = splitInternalNode(BPlusTree::root, is.nodes.at(0), is.nodes.at(1), is.value);
				BPlusTree::root = BPlusTree::newNode(nextNode.value, nextNode.nodes.at(0), nextNode.nodes.at(1));
			}
		}
	}
}

internalSplit insertInternal(
	int value, string data, Node* node, int maxInternalDegree, int maxLeafDegree, bool isRoot, BPlusTree* tree
)
{
	Node* next = node->getNext(value);
	if (next->isLeaf) {
		// TODO: insert key/data in leaf and handle the splitting case
		if (next->keys.size() < maxLeafDegree) {
			next->keys = sortNewKey(next->keys, value);
			BPlusData* s = new BPlusData();
			s->data = data;
			s->key = value;
			next->data.push_back(s);

			internalSplit is;
			is.value = -10;
			return is;
		}
		else {
			dataSplit ds = splitDataNode(next, value, data);
			internalSplit is;
			is.nodes.push_back(ds.nodes.at(0));
			is.nodes.push_back(ds.nodes.at(1));
			is.value = ds.middleValue;

			return is;
		}
	} else {
		internalSplit is = insertInternal(value, data, next, maxInternalDegree, maxLeafDegree, false, tree);

		if (is.value != -10) {
			if (node->keys.size() < maxInternalDegree) {
				node->keys = sortNewKey(node->keys, is.value);
				node->addLinks(is.value, is.nodes.at(0), is.nodes.at(1));

				internalSplit is;
				is.value = -10;
				return is;
			}
			else {
				internalSplit nextNode = splitInternalNode(node, is.nodes.at(0), is.nodes.at(1), is.value);
				if (isRoot) {
					tree->root = tree->newNode(nextNode.value, nextNode.nodes.at(0), nextNode.nodes.at(1));
				}
				return nextNode;
			}
		}
	}

	internalSplit is;
	is.value = -10;
	return is;
}


// open file, read info, push into tree
int main() {
    BPTree node;

    FILE *pf;
    char id[10], description[80];
    int count = 0;

    pf = fopen("test.txt", "r");

    while (!feof(pf) && count < 10) {
        if (fscanf(pf, " %s %[^\n]\n", id, description) < 1)
            break;
        node.insert(id);
        printf("Part ID: %s\n", id);
        count += 1;
    }
    fclose(pf);
    // string searchKey = "AAA-196";
    node.search("AAA-07");
    return 0;
}

// search function
void BPTree::search(string x) { 
    string searchKey = x;
  if (root == NULL) {
    cout << "\nTree Is Empty\n";
  } else {
    cout << "\nSearching For ID: " + x + "\n";
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }


    int foundIndex = -1;
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == x) {
                foundIndex = i;
                cout << "\nFound\n";
                // cout << "Found at index " << i << ": " << cursor->key[i] << "\n";
                break;
            }
        }

        if (foundIndex != -1) {
            cout << "\nNext 10 items:\n";
            for (int i = foundIndex + 1; i < min(cursor->size, foundIndex + 11); i++) {
                cout << cursor->key[i] << "\n";
            }
        } else {
            cout << "\nNot Found\n";
        }
  	}
}