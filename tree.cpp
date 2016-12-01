#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>

const int TREE_EMPTY = 0;
const int TREE_SHORT = 1;

using namespace std;

struct BinTree {
	int data;
	BinTree *left;
	BinTree *right;

};

int irand() {
	return rand() % 41 - 20;
}

BinTree* insert(BinTree *root, int val) {
	if (!root) {
		root = new BinTree;
		root->data = val;
		root->left = root->right = 0;
	}
	else if (val < root->data) {
		root->left = insert(root->left, val);
	}
	else if (val > root->data) {
		root->right = insert(root->right, val);
	}
	return root;
}

void printTreeInARow(BinTree *a) {
	BinTree *temp= a;
	if (temp) {
		cout << temp->data << "  ";
		printTreeInARow(temp->left);
		printTreeInARow(temp->right);
	}
}

BinTree* createTree(BinTree *&a, int n) {
	for (int i = 0; i < n; i++)	{
		a = insert(a, irand());
	}
	return a;
}


void ui(BinTree *&first) {
	int num = 1, n;
	while (num) {
		try {
			cout << "\n========================\n  0 -- exit; \n  1 -- createTree; \n  2 -- insert; \n  3 -- printTreeInARow;";
			cout << "\n========================\ninput: ";
			cin >> num;
			cout << endl;
			switch (num) {
			case 0: break;
			case 1: cout<< "n: "; cin >> n; first = createTree(first, n); break;
			case 2: cout << "val: "; cin >> n; first = insert(first, n); break;
			case 3: printTreeInARow(first); cout << endl; break;
			default: cout << "error" << endl;
			}
		}
		catch (int ex) {
			switch (ex) {
			case TREE_EMPTY: cout << "TREE IS EMPTY" << endl; break;
			case TREE_SHORT: cout << "ELEMENT DOES NOT EXIST" << endl; break;
			}
		}
	}
}


int main() {
	BinTree *first = 0;
	ui(first);
	return 0;
}