#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
	root = nullptr;
	leaf = new Node();
	size = 0;
}

RedBlackTree::~RedBlackTree() {
	DeleteTree(root);
	delete(leaf);
}

bool RedBlackTree::Insert(int input) {
	if (root == nullptr) { //empty tree
		root = new Node(input);
		root->left = root->right = leaf;
		root->left->parent = root->right->parent = root;
		root->parent = nullptr;
		root->black = true;
		size++;
		return true;
	}

	Node* temp = FindParent(input);
	if (temp == nullptr) return false; //node already exists

	if (temp->data > input) {
		temp->left = new Node(input);
		temp->left->parent = temp;
		temp = temp->left;
		temp->left = temp->right = leaf;
	} else {
		temp->right = new Node(input);
		temp->right->parent = temp;
		temp = temp->right;
		temp->left = temp->right = leaf;
	}

	BalanceInsertion(temp);
	size++;
	return true;
}

bool RedBlackTree::Remove(int target) {
	Node* temp = FindTarget(target);
	if (temp == nullptr) return false; //node does not exist
	
	Node* temp2;
	Node* fixNode;
	if (temp == root && root->left == leaf && root->right == leaf) { //last node in the tree
		delete(root);
		root = nullptr;
		size--;
		return true;
	}

	if (temp->right == leaf || temp->left == leaf) { //has only one child
		temp2 = temp;
	} else { //has 2 children
		temp2 = FindPred(temp->left);
	}

	if (temp2->left != leaf) {
		fixNode = temp2->left;
	} else {
		fixNode = temp2->right;
	}

	fixNode->parent = temp2->parent;

	if (temp2 == root) {
		root = fixNode;
	} else {
		if (temp2 == temp2->parent->left) {
			temp2->parent->left = fixNode;
		} else {
			temp2->parent->right = fixNode;
		}
	}

	if (temp2 != temp) temp->data = temp2->data;
	if (temp2->black) BalanceDeletion(temp2, fixNode);
	size--;
	return true;
}

vector<int> RedBlackTree::GetList() {
	result.clear();
	if (root == nullptr) return result; //empty tree
	TraverseTree(root);
	return result;
}

//Recurse in order
void RedBlackTree::TraverseTree(Node* current) {
	if (current->left != leaf) TraverseTree(current->left);
	result.push_back(current->data);
	if (current->right != leaf) TraverseTree(current->right);
}

//Recurse post order
void RedBlackTree::DeleteTree(Node* current) {
	if (current->left != leaf) DeleteTree(current->left);
	if (current->right != leaf) DeleteTree(current->right);
	delete(current);
}

Node* RedBlackTree::FindTarget(int target) {
	if (root == nullptr) return nullptr; //empty tree
	Node* temp = root;
	while (temp != leaf) {
		if (temp->data == target) return temp; //node found
		if (temp->data > target) {
			temp = temp->left;
		} else {
			temp = temp->right;
		}
	}
	return nullptr; //node not found
}

Node* RedBlackTree::FindParent(int target) {
	Node* temp = root;
	while (temp != leaf) {
		if (temp->data == target) return nullptr; //node already exists, not parent
		if (temp->data > target) {
			if (temp->left == leaf) return temp;
			temp = temp->left;
		} else {
			if (temp->right == leaf) return temp;
			temp = temp->right;
		}
	}
	return temp->parent;
}

Node* RedBlackTree::FindPred(Node* node) {
	Node* temp = node;
	while (temp->right != leaf) {
		temp = temp->right;
	}
	return temp;
}

void RedBlackTree::RotateLeft(Node* target) {
	Node* temp = target->right;
	target->right = temp->left;
	if (temp->left != leaf) temp->left->parent = target;
	temp->parent = target->parent;
	if (target->parent == nullptr) {
		root = temp;
	} else {
		if (target == target->parent->left) {
			target->parent->left = temp;
		} else {
			target->parent->right = temp;
		}
	}
	temp->left = target;
	target->parent = temp;
}

void RedBlackTree::RotateRight(Node* target) {
	Node* temp = target->left;
	target->left = temp->right;
	if (temp->right != nullptr) temp->right->parent = target;
	temp->parent = target->parent;
	if (target->parent == nullptr) {
		root = temp;
	}
	else {
		if (target == target->parent->right) {
			target->parent->right = temp;
		}
		else {
			target->parent->left = temp;
		}
	}
	temp->right = target;
	target->parent = temp;
}

void RedBlackTree::BalanceInsertion(Node* target) {
	Node* temp;
	target->black = false;
	while (target != root && target->parent->black == false) {
		if (target->parent == target->parent->parent->left) { //parent is a left child
			temp = target->parent->parent->right;
			if (!temp->black) {
				target->parent->black = true;
				temp->black = true;
				target->parent->parent->black = false;
				target = target->parent->parent;
			} else {
				if (target == target->parent->right) {
					target = target->parent;
					RotateLeft(target);
				}
				target->parent->black = true;
				target->parent->parent->black = false;
				RotateRight(target->parent->parent);
			}
		} else { //parent is a right child, mirror the if
			temp = target->parent->parent->left;
			if (!temp->black) {
				target->parent->black = true;
				temp->black = true;
				target->parent->parent->black = false;
				target = target->parent->parent;
			}
			else {
				if (target == target->parent->left) {
					target = target->parent;
					RotateRight(target);
				}
				target->parent->black = true;
				target->parent->parent->black = false;
				RotateLeft(target->parent->parent);
			}
		}
	}
	root->black = true;
}

void RedBlackTree::BalanceDeletion(Node* target, Node* child) {
	Node* sibling;

	while (child != root && child->black) {
		if (child == child->parent->left) { //left child
			sibling = child->parent->right;
			if (!sibling->black) {
				sibling->black = true;
				child->parent->black = false;
				RotateLeft(child->parent);
				sibling = child->parent->right;
			}

			if (sibling->left->black && sibling->right->black) {
				sibling->black = false;
				child = child->parent;
			}
			else {
				if (sibling->right->black) {
					sibling->left->black = true;
					sibling->black = false;
					RotateRight(sibling);
					sibling = child->parent->right;
				}

				if (child->parent->black) {
					sibling->black = true;
				}
				else {
					sibling->black = false;
				}

				child->parent->black = true;
				sibling->right->black = true;
				RotateLeft(child->parent);
				child = root;
			}
		}
		else { //right child, mirror the if
			sibling = child->parent->left;
			if (!sibling->black) {
				sibling->black = true;
				child->parent->black = false;
				RotateRight(child->parent);
				sibling = child->parent->left;
			}

			if (sibling->left->black && sibling->right->black) {
				sibling->black = false;
				child = child->parent;
			}
			else {
				if (sibling->left->black) {
					sibling->right->black = true;
					sibling->black = false;
					RotateLeft(sibling);
					sibling = child->parent->left;
				}

				if (child->parent->black) {
					sibling->black = true;
				}
				else {
					sibling->black = false;
				}

				child->parent->black = true;
				sibling->left->black = true;
				RotateRight(child->parent);
				child = root;
			}
		}
	}
		child->black = true;
		leaf->black = true;
}

int RedBlackTree::GetSize() {
	return size;
}

int RedBlackTree::GetHeight() {
	return log2(size);  //root not counted as a level
}