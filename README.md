# CSCI651
Project for CSCI 651

Node Method/Function Descriptions:

insert(int value, string data)
- takes the value and data to be associated with a new key. The end result should be a key that is in-line the with the format of a B+ tree.

splitDataNode(Node* node, int value, string data, int rootValue)
- takes the current node, the new value and data to be inserted, and the value of the root that points to the leaf.
- used to split data nodes when the value count has reached the degree of the node

newValues getPivot(vector<int> values)
- used to find the value at the middle position of an internal node
- the key at the middle position is meant to be placed at the level above the rest of the node and point to the other keys
- returns a struct containing a vector for the new values, as well as the value of the pivot key

  vector<Node*> getNewLinks(Node* n, Node* left, Node* right, int oldLink)
  - returns a vector of the links to be used in a new internal node
  - takes the oldLink argument so the point to the node at the lower level causing the split is removed
  - takes the _left_ and _right_ arguments so the links the new key are accounted for
