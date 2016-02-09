#include "Node.h"

//Leaf node with no value, used instead of a null pointer for better rotations
Node::Node() {
	black = true;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

Node::Node(int input) {
	data = input;
	black = true;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}