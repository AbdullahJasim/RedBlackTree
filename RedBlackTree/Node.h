#pragma once

class Node {
public:
	Node ();
	Node (int input);
	int data;
	Node* parent;
	Node* left;
	Node* right;
	bool black;
};

