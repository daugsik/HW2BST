#pragma once
#include "nodedata.h"

class BinTree {				// you add class/method comments and assumptions

	friend ostream& operator<<(ostream&, const BinTree&);

public:
	BinTree();								// constructor
	BinTree(const BinTree &);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree &);
	bool operator==(const BinTree &) const;
	bool operator!=(const BinTree &) const;
	bool insert(NodeData*);
	bool retrieve(const NodeData &, NodeData* &) const;
	int getHeight(const NodeData &) const;
	void bstreeToArray(NodeData*[]);
	void arrayToBSTree(NodeData*[]);
	void displaySideways() const;			// provided below, displays the tree sideways
	
private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

	// utility functions
	ostream& inorderHelper(const Node*, ostream&) const;
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()
	void emptyHelper(Node* &);
	bool equalityHelper(const Node*, const Node*) const;
	void copyHelper(const Node* toCopy);
	bool findNode(const NodeData &value, Node* &toReturn) const;
	int heightHelper(const Node* source) const;
	void btaHelper(const Node* toMove, int &index, NodeData*[]);
	void atbHelper(const int lowerLim, const int upperLim, NodeData* toMove[]);
};

