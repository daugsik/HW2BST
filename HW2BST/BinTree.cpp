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

Preconditions:

Postconditions:

*/
BinTree::BinTree(const BinTree &)
{

}

/*----------~BinTree
Purpose:

Preconditions:

Postconditions:

*/
BinTree::~BinTree()
{

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
	delete toDelete;
	toDelete = NULL;
}

/*---------- Assignment Operator
Purpose:

Preconditions:

Postconditions:

*/
BinTree& BinTree::operator=(const BinTree &)
{

}

/*---------- Equality Operator
Purpose:

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
		return true;
	}

	// If both have non-empty trees, pass to equalityHelper.
	return (equalityHelper(root, toCompare.root));
}

/*---------- equalityHelper
Purpose:

Preconditions:
	Neither thisNoder nor toCompare can be a pointer with the value NULL.
Postconditions:

*/
bool BinTree::equalityHelper(const Node* thisNode, const Node* toCompare) const
{
	// if both pointers are NULL, return true.
	// NOTE: this code should never execute.
	if (thisNode == NULL && toCompare == NULL)
	{
		cout << "Warning: Comparing Null Nodes" << endl;
		return true;
	}
	// if either pointer points to a NULL address, break out of function.
	// NOTE: this code should never execute.
	if (thisNode == NULL || toCompare == NULL)
	{
		cout << "Warning: Comparing Null Nodes" << endl;
		return false;
	}

	// Check if current nodes are equal.

	// Check if left children of the two trees are equal (if both of them are non-null pointers)

	// Check if right children of the two trees are equal (if both of them are non-null pointers)

	// if the subtree is equivalent, return true.
	return true;
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

}

/*---------- Display Sideways
Purpose:

Preconditions:

Postconditions:

*/
void BinTree::displaySideways() const
{

}

/*---------- inOrderHelper
Purpose:

Preconditions:

Postconditions:

*/
void BinTree::inorderHelper(...) const
{

}

/*---------- sideways
Purpose:

Preconditions:

Postconditions:

*/
void BinTree::sideways(Node*, int) const
{

}
