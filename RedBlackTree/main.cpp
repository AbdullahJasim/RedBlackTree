#include <iostream>
#include "RedBlackTree.h"

using namespace std;

int main() {
	RedBlackTree* tree = new RedBlackTree();
	vector<int> elements;
	int input = 99;
	
	//Interactive loop to let the user use the functions of the tree
	while (input != 0) {
		cout << "0-Exit\t1-Insert\t2-Remove\t3-Print List\t4-Empty List\t5-Tree Size\t6-Tree Height\n";
		cin >> (input);

		switch (input) {
			case 0:
				return 0;
			case 1:
				cout << "Insert the new value\n";
				cin >> (input);
				if (tree->Insert(input)) {
					cout << "Node inserted succesfully\n";
				}
				else {
					cout << "Node already exists\n";
				}
				input = 1;
				break;
			case 2:
				cout << "Insert the value to be removed\n";
				cin >> (input);
				if (tree->Remove(input)) {
					cout << "Node removed successfully\n";
				} else {
					cout << "Node does not exist\n";
				}
				input = 2;
				break;
			case 3:
				elements = tree->GetList();
				for (unsigned int i = 0; i < elements.size(); i++) {
					cout << elements[i];
					cout << " ";
				}
				cout << "\n";
				input = 3;
				break;
			case 4:
				delete(tree);
				tree = new RedBlackTree();
				break;
			case 5:
				input = tree->GetSize();
				cout << "There are " << input << " nodes in the tree\n";
				input = 5;
				break;
			case 6:
				input = tree->GetHeight();
				cout << "The tree is " << input << " levels high\n";
				input = 5;
				break;
		}
	}
	return 0;
}