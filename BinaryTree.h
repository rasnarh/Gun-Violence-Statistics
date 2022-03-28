// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Rasna Husain and Amrita Kohli
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"
#include "Stack.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	virtual ~BinaryTree() { destroyTree(rootPtr); }
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	void levelOrder(void visit(ItemType &)) const;
	void indentPrint(void visit(ItemType &), int level) { _indentprint(visit, rootPtr, level); } //wrapper function for printing w/ indentation
	bool writeFile(void write(ItemType &, ofstream &obj)) const;

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData, int compare(const ItemType &one, const ItemType &two)) = 0;
	virtual bool remove(const ItemType & data, int compare(const ItemType &one, const ItemType &two)) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType* returnedItems, int &i, int compare(const ItemType &one, const ItemType &two)) const = 0;
	virtual void theSmallest(ItemType &item) = 0;
	virtual void theLargest(ItemType &item) = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	// prints tree with indentation based on their level
	void _indentprint(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level);
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);		
	}
}  

template<class ItemType> 
void BinaryTree<ItemType>::levelOrder(void visit(ItemType &)) const
{	//prints tree in level order (breadth first)
	//BinaryNode<ItemType>* nodePtr = rootPtr;
	if (nodePtr != 0)
	{
		Queue<BinaryNode<ItemType>*> Q;
		Q.enqueue(rootPtr);

		while (Q.isEmpty() == false)
		{
			BinaryNode<ItemType>* newNodePtr;
			Q.queueFront(newNodePtr);
			ItemType item = newNodePtr->getItem();
			visit(item);
			Q.dequeue(newNodePtr);

			if (newNodePtr->getLeftPtr() != 0)
				Q.enqueue(newNodePtr->getLeftPtr());

			if (newNodePtr->getRightPtr() != 0)
				Q.enqueue(newNodePtr->getRightPtr());
		}
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_indentprint(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level)
{	//prints tree with indentation based on level
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();

		for (int indent = 0; indent < level; indent++)
		{
			cout << "\t";
		}

		cout << ++level << ". ";
		visit(item);
		cout << endl;

		_indentprint(visit, nodePtr->getRightPtr(), level);
		_indentprint(visit, nodePtr->getLeftPtr(), level);

		level--;
	}
}

/* Writes all of the binary search tree's data to newdata.txt. 
   Returns true if successful, otherwise returns false. */
template<class ItemType>
bool BinaryTree<ItemType>::writeFile(void write(ItemType &, ofstream &obj)) const //iterative inorder
{
	BinaryNode<ItemType>* nodePtr;
	nodePtr = rootPtr;
	ofstream out;
	out.open("newdata.txt");

	if (out.fail())
		return false;

	if (nodePtr != 0)
	{
		Stack<BinaryNode<ItemType>*> s; //creating a stack
		s.push(nodePtr); //pushing root onto stack
		
		while (s.isEmpty() == false)
		{
			s.pop(nodePtr); //popping top of stack
			ItemType item = nodePtr->getItem();
			write(item, out);
			if (nodePtr->getRightPtr() != 0)
			{
				s.push(nodePtr->getRightPtr()); //pushing right child of nodePtr
			}
			if (nodePtr->getLeftPtr() != 0)
			{
				s.push(nodePtr->getLeftPtr()); //pushing left child of nodePtr
			}
		}
	}
	out.close();
	return true;
}

#endif

