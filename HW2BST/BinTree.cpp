/* -------------------binTree.cpp-------------------------
Dongkyu Daniel Kim, CSS343A, ##
Creation: April 16th, 2017
Last Accessed: April 21th, 2017

----------------------------------------------------------
Purpose:

Implements BinTree functions. Among these:
	- Copy Construction and Assignment
	- << Overloading
	- Single Insertion
	- Whole Tree Deletion
	- BST-to-Array and Array-to-BST conversion
	- (In)Equality Operator Overloading

---------------------------------------------------------------*/
#include "bintree.h"

//------------------------------------------------
// CONSTRUCTORS/DESTRUCTOR

/*----------BinTree
Purpose:
	Creates an empty tree with a root of NULL.
	Tree can be built with subsequent inserts.
Preconditions:
	none
Postconditions:
	none
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
	this BinTree will have an identical structure
	with identical values to the tree that was copied.
*/
BinTree::BinTree(const BinTree &toCopy)
{
	root = NULL;
	*this = toCopy;
}

/*----------~BinTree
Purpose:
	Empties allocated NodeData and Nodes.
Preconditions:
	None
Postconditions:
	Emptied tree, root pointer with value of NULL.
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
	root must exist
Postconditions:
	does not change BinTree
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
	none
Postconditions:
	Empties tree of Nodes and associated NodeData.
	Root is emptied and set to NULL. If root is already
	null, no action takes place.
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
Deallocates children memory -- both the NodeData
and the Node itself -- left and right
pointers set to Null.
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

/*---------- copyHelper
Purpose:
	Called by either the copy constructor or assignment
	operator to clone the structure and values of another
	binTree. Inserts new Nodes in prefix order to preserve
	structure of the tree.
Preconditions:
	Tree must be empty / root = NULL.
Postconditions:
	Creates identical tree with deep-copy NodeData values.
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
	Copies the second BinTree in structure and values to
	the BinTree that called the = operator.
Preconditions:
	None
Postconditions:
	Returns an identical BinTree of toCopy. 
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
	None
Postconditions:
	Neither tree is changed after the operation is executed.
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
	None.
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

/*---------- ostream operator <<
Purpose:
	Allows the object to be printed to console output.
Preconditions:
	None
Postconditions:
	None
*/
ostream& operator<<(ostream &os, const BinTree &toPrint)
{
	toPrint.inorderHelper(toPrint.root, os);
	os << endl;
	return os;
}

/*---------- inOrderHelper
Purpose:
	Prints the tree inOrder to output a sorted list of terms.
Preconditions:
	The tree must be a sorted BST.
Postconditions:
	None.
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
	None.
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
	None
Postconditions:
	One additional node will be added to the BST in its appropriate sorted position.
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
	None
Postconditions:
	Returns a found result in result. If there is no found result, result is unchanged.
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
	None
Postconditions:
	Returns
		1) the found result in toReturn and returns true
		2) the parent of the lass node traversed and returns false
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

/*---------- bstreeToArray
Purpose:
	Places all nodes into a predefined array inOrder. After btaHelper
	executes, the tree still exists, so makeEmpty() is called at the end
	of the function to deallocate the memory.
Preconditions:
	Sorted Tree, empty array.
Postconditions:
	Empty Tree, Sorted Array.
*/
void BinTree::bstreeToArray(NodeData* outArray[])
{
	int arrayIndex = 0;
	btaHelper(root, arrayIndex, outArray);

	makeEmpty();
}

/*---------- btaHelper
Purpose:
	is passed an index of where to insert into the array
	and a particular node. Traverses the tree and inserts values
	to outArray in order. 
Preconditions:
	Sorted tree, empty array value at index.
Postconditions:
	Newly created nodeData at outArray[index].
*/
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
	delete outArray[index];
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

/*---------- arrayToBSTree
Purpose:
	Converts a sorted array of values into a new BST
Preconditions:
	Sorted Array, empty tree.
Postconditions:
	Empty array, Sorted Balanced BST.
*/
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

/*---------- atbHelper
Purpose:
	Assists arrayToBST by recursively dividing the array into two groups
	and inserting the midpoint into the tree. Deallocates NodeData as
	it progresses through the array, as new instances are being created
	in insert().
Preconditions:
	Empty BinTree.
Postconditions:
	Empty Array. 
*/
void BinTree::atbHelper(const int lowerLim, const int upperLim, NodeData* toMove[])
{
	// if the limits are the same, there is only one cell.
	if (lowerLim == upperLim)
	{
		insert(toMove[lowerLim]);
		delete toMove[lowerLim];
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
	delete toMove[midway];
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

/*---------- getHeight
Purpose:
	First finds the node if it exists in the tree. If the node does not exist
	return 0. If it exists, calls heightHelper to determine the longest branch
	to a leaf to return as the height.
Preconditions:
	The tree does not have to be sorted, so nothing I suppose.
Postconditions:
	Returns the longest branch, with no traversal being a length of 1.
*/
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
Purpose:
	Recursive function that searches through an unsorted tree for a specific value.
Precondition:
	None
Postcondition:
	Returns cumulative length of longest branch in subtree.
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