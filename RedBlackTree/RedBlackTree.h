#pragma once
#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

class RedBlackTree {
public:
	Node* root;
	Node* leaf;
	int size;
	vector<int> result;

	RedBlackTree();
	~RedBlackTree();
	
	//Creates a node in the tree with the passed value,
	//returns false if the value already exists
	bool Insert(int input);
	
	//Removes the node with the passed value from the tree,
	//returns false if such node does not exist
	bool Remove(int target);
	
	//Gets a list of all values in the tree in an ascending order
	vector<int> GetList();
	int GetSize();
	int GetHeight();

private:
	void RotateLeft(Node* target);
	void RotateRight(Node* target);
	Node* FindTarget(int target);
	Node* FindParent(int target);
	Node* FindPred(Node* node);
	void BalanceInsertion(Node* x);
	void BalanceDeletion(Node* target, Node* child);
	void TraverseTree(Node* current);
	void RedBlackTree::DeleteTree(Node* current);
};