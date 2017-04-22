#include "BinTree.h"

//------------------------------------------------
// CONSTRUCTORS/DESTRUCTOR

/*----------BinTree
Purpose:

Preconditions:

Postconditions:

*/
BinTree::BinTree()
{
	root = NULL;
}

/*----------BinTree (copy)
Purpose:
	Creates the same tree 
Preconditions:
	The BinTree to be copied must be a sorted
	Binary Search Tree. Creates a perfect copy
	rather than performing node-wise insertions.
Postconditions:

*/
BinTree::BinTree(const BinTree &toCopy)
{
	root = NULL;
	*this = toCopy;
}

/*----------~BinTree
Purpose:

Preconditions:

Postconditions:

*/
BinTree::~BinTree()
{
	makeEmpty();
}							


//-------------------------------------
// MEMBER FUNCTIONS


/*----------isEmpty
Purpose:
	Checks if Tree currently holds any
	data nodes. Returns true if a root
	node exists, returns false otherwise.

Preconditions:

Postconditions:

*/
bool BinTree::isEmpty() const
{
	if (root == NULL)
	{
		return true;
	}
	return false;
}

/*---------- makeEmpty
Purpose:
	Moves through the tree, deallocating
	leaf nodes before deallocating parents.
	Post-order structure. If tree is empty,
	return leave the function.

	Passes root node to emptyHelper to perform
	a recursive deletion, if not empty.

Preconditions:

Postconditions:

*/
void BinTree::makeEmpty()
{
	if (isEmpty())
	{
		return;
	}

	emptyHelper(root);
}

/*---------- emptyHelper
Purpose:
Recursive function to delete nodes.
Calls itself on left and right children
before deleting itself (postorder).

Preconditions:
toDelete must not have a NULL value.

Postconditions:
Deallocates children memory, left and right
pointers and actual NodeData memory.
*/
void BinTree::emptyHelper(Node* &toDelete)
{
	if (toDelete->left != NULL)
	{
		emptyHelper(toDelete->left);
	}
	if (toDelete->right != NULL)
	{
		emptyHelper(toDelete->right);
	}

	delete toDelete->data;
	toDelete->left = NULL;
	toDelete->right = NULL;
	delete toDelete;
	toDelete = NULL;
}

/*---------- copyHelper
Purpose:
	Called by either the copy constructor or assignment
	operator to clone the structure and values of another
	binTree.
Preconditions:
	
Postconditions:
	
*/
void BinTree::copyHelper(const Node* toCopy)
{
	// if the node exists, allocate new memory and add to
	// the tree.
	if (toCopy == NULL)
	{
		return;
	}
	else
	{
		insert(toCopy->data);
		copyHelper(toCopy->left);
		copyHelper(toCopy->right);
		return;
	}
}


/*---------- Assignment Operator
Purpose:

Preconditions:

Postconditions:

*/
BinTree& BinTree::operator=(const BinTree &toCopy)
{
	// If the binTree is assigned to itself, just return
	// "this"
	if (root == toCopy.root)
	{
		return *this;
	}

	// else, empty tree and use copyHelper to populate tree.
	makeEmpty();

	// if the to-copy tree is empty, return empty tree.
	if (toCopy.isEmpty())
	{
		return *this;
	}

	copyHelper(toCopy.root);
	return *this;
}

/*---------- Equality Operator
Purpose:
	Checks two BinTrees for structual and value equivalence.
	Passes the root nodes of both trees to the equalityHelper, which
	iterates through the trees in prefix order and returns false
	at the first discrepancy.
Preconditions:

Postconditions:

*/
bool BinTree::operator==(const BinTree &toCompare) const
{
	// if both roots are empty, return true.
	if (this->isEmpty() && toCompare.isEmpty())
	{
		return true;
	}

	// if at least one root is empty, return false.
	if (this->isEmpty() || toCompare.isEmpty())
	{
		return false;
	}

	// If both have non-empty trees, pass to equalityHelper.
	return (equalityHelper(root, toCompare.root));
}

/*---------- equalityHelper
Purpose:
Checks equality by performing an prefix traversal of two trees and
comparing NodeData at every step. Recursive function, breaks traversal
and cascades false up to the first call if an inequality is found.
Preconditions:
Neither thisNode nor toCompare can be a pointer with the value NULL.
Postconditions:

*/
bool BinTree::equalityHelper(const Node* thisNode, const Node* toCompare) const
{
	// if both pointers are NULL, return true.
	if (thisNode == NULL && toCompare == NULL)
	{
		return true;
	}
	// if only one pointer points to a NULL address, return false.
	if (thisNode == NULL || toCompare == NULL)
	{
		return false;
	}

	// Check if current nodes are equal.
	if (*thisNode->data == *toCompare->data)
	{
		// Check if left children of the two trees are equal (if both of them are non-null pointers)
		// if an inequality is found, cascade false.
		if (!equalityHelper(thisNode->left, toCompare->left))
		{
			return false;
		}

		// Check if right children of the two trees are equal (if both of them are non-null pointers)
		// if an inequality is found, cascade false.
		if (!equalityHelper(thisNode->right, toCompare->right))
		{
			return false;
		}

		// if the subtrees are equivalent, return true.
		return true;
	}

	// if current nodes are not equal, return false.
	return false;
}

ostream& operator<<(ostream &os, const BinTree &toPrint)
{
	os << endl;
	toPrint.inorderHelper(toPrint.root, os);
	return os;
}

/*---------- inOrderHelper
Purpose:

Preconditions:

Postconditions:

*/
ostream& BinTree::inorderHelper(const Node *toPrint, ostream &output) const
{
	if (toPrint->left != NULL)
	{
		inorderHelper(toPrint->left, output);
	}

	output << *toPrint->data << " ";

	if (toPrint->right != NULL)
	{
		inorderHelper(toPrint->right, output);
	}

	return output;
}



/*---------- Inequality Operator
Purpose:
	Inequality checker.
Preconditions:

Postconditions:
	Returns the negated value of the equality
	operator.
*/
bool BinTree::operator!=(const BinTree &toCompare) const
{
	return !(*this == toCompare);
}

/*---------- Insert
Purpose:
	Creates a new Node and performs a search for the appropriate position for
	insertion. If the program finds an identical NodeData value, no insertion
	is performed and returns false. If finds a suitable leaf location, performs
	the insertion and returns true.

Preconditions:

Postconditions:

*/
bool BinTree::insert(NodeData* toInsert)
{
	// if root is NULL, perform special case insertion.
	if (root == NULL)
	{
		root = new Node;
		root->left = NULL;
		root->right = NULL;
		NodeData *rootData = new NodeData(*toInsert);
		root->data = rootData;
		rootData = NULL;
	}

	Node *parent = NULL;

	// if the tree does not already contain the value, perform insertion
	if (!findNode(*toInsert, parent))
	{
		Node *child = new Node;
		child->left = NULL;
		child->right = NULL;
		NodeData *childData = new NodeData(*toInsert);
		child->data = childData;
		childData = NULL;
		
		// if the parent is grater than value, insert left
		if (*toInsert < *parent->data)
		{
			parent->left = child;
		}
		// else insert right (assumes findNode did its job properly)
		else
		{
			parent->right = child;
		}

		child = NULL;
		return true;
	}

	// if a node already exists in the tree with the given value, return false.
	return false;
}

/*---------- Retrieve
Purpose:
	Given an identically constructed piece of NodeData, search the tree
	and, if found, store the address of the found data in result and return true.
	If the data is not found, return false.


Preconditions:

Postconditions:

*/
bool BinTree::retrieve(const NodeData &toRetrieve, NodeData *&result) const
{
	Node *foundNode = NULL;
	if (findNode(toRetrieve, foundNode))
	{
		result = foundNode->data;
		foundNode = NULL;
		return true;
	}
	return false;
}

/*---------- findNode
Purpose:
	Due to the strange nature of returning a nodeData object in retrieve,
	findNode finds the tree node itself to return to functions for purposes
	of injection or search.

	If the node is found, return true and update toReturn to point at specified
	node.

	If node is not found, return false but also update toReturn so that it reflects
	the last node traversed. This pointer will hold the parent node of a node to be
	inserted.

Preconditions:

Postconditions:

*/
bool BinTree::findNode(const NodeData &value, Node* &toReturn) const
{
	// empty case.
	if (isEmpty())
	{
		return false;
	}
	
	Node *index = root;
	while (value != *index->data)
	{
		// left traversal
		if (value < *index->data)
		{
			if (index->left != NULL)
			{ 
				index = index->left;
			}
			// if left is null, return parent and false.
			else
			{
				toReturn = index;
				return false;
			}
		}

		// right traversal
		else if (value > *index->data)
		{
			if (index->right != NULL)
			{
				index = index->right;
			}
			// if right is null, return parent and false.
			else
			{
				toReturn = index;
				return false;
			}
		}
	}

	// otherwise, return found.
	toReturn = index;
	index = NULL;
	return true;
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side; 
// hard coded displaying to standard output. 
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

void BinTree::bstreeToArray(NodeData* outArray[])
{
	int arrayIndex = 0;
	btaHelper(root, arrayIndex, outArray);

	makeEmpty();
}

void BinTree::btaHelper(const Node* toMove, int &index, NodeData* outArray[])
{
	if (toMove == NULL)
	{
		return;
	}

	// traverse left
	if (toMove->left != NULL)
	{
		btaHelper(toMove->left, index, outArray);
	}

	//copies data into array
	NodeData *temp = new NodeData(*toMove->data);
	outArray[index] = temp;
	temp = NULL;
	//increments index
	index++;

	//traverse right
	if (toMove->right != NULL)
	{
		btaHelper(toMove->right, index, outArray);
	}
}

void BinTree::arrayToBSTree(NodeData *toMove[])
{
	// if the array is empty, don't construct a tree.
	if (toMove[0] == NULL)
	{
		return;
	}

	int sizeOfArray = 0;
	while (toMove[sizeOfArray] != NULL)
	{
		sizeOfArray++;
	}

	// if array is empty, don't build anything.
	if (sizeOfArray == 0)
	{
		return;
	}

	atbHelper(0, sizeOfArray-1, toMove);

}

void BinTree::atbHelper(const int lowerLim, const int upperLim, NodeData* toMove[])
{
	// if the limits are the same, there is only one cell.
	if (lowerLim == upperLim)
	{
		insert(toMove[lowerLim]);
		toMove[lowerLim] = NULL;
		return;
	}

	// if the limits are off by 1, insert in order.
	if (upperLim - lowerLim == 1)
	{
		insert(toMove[lowerLim]);
		delete toMove[lowerLim];
		toMove[lowerLim] = NULL;

		insert(toMove[upperLim]);
		delete toMove[upperLim];
		toMove[upperLim] = NULL;

		return;
	}

	// otherwise, insert midpoint between lowerLim and upperLim, then separate into
	// two new halves with new boundaries.
	int midway = (lowerLim + upperLim) / 2;
	insert(toMove[midway]);
	toMove[midway] = NULL;

	// new bounds do not include the recently included midway. 1 cell offsets for both.
	// Left branch
	atbHelper(lowerLim, (midway - 1), toMove);
	atbHelper((midway + 1), upperLim, toMove);

}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged. 
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

int BinTree::getHeight(const NodeData &toFind) const
{
	Node *temp = NULL;
	
	// if found, perform height check
	if (findNode(toFind, temp))
	{
		return heightHelper(temp);
	}

	// if not found, return 0
	return 0;
}

/* ------------------------------heightHelper
	Recursive function that searches through an unsorted tree for a specific value.
	Is given the parent height and the current node in the tree to compare to toFind.
	Cascades the height at which toFind was found to root call, otherwise cascades 0.

*/
int BinTree::heightHelper(const Node* source) const
{	
	// if the node is a leaf, return 1.

	if (source->left == NULL
		&& source->right == NULL)
	{
		return 1;
	}

	int leftsub = 0;
	int rightsub = 0;

	// traverse subtrees
	if (source->left != NULL)
	{
		leftsub = heightHelper(source->left);
	}

	if (source->right != NULL)
	{
		rightsub = heightHelper(source->right);
	}

	// return the "taller" of the two subtrees
	if (leftsub > rightsub)
	{
		return (leftsub + 1);
	}

	else
	{
		return (rightsub + 1);
	}
}