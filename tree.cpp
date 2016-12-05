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

int factorial(int a) {
	return (a==1 || a == 0)?1:a*factorial(a-1);
}

void insert(BinTree *&root, int val) {
	if (!root) {
		root = new BinTree;
		root->data = val;
		root->left = root->right = 0;
	} else if (val < root->data) {
		insert(root->left, val);
	} else if (val > root->data) {
		insert(root->right, val);
	}
}

void printTreeInARow(BinTree *a) {
	if (a) {
		cout << a->data << "  ";
		printTreeInARow(a->left);
		printTreeInARow(a->right);
	}
}

void createTree(BinTree *&a, int n) {
	for (int i = 0; i < n; i++)	{
		insert(a, irand());
	}
}

BinTree* search(BinTree *a, int val) {
	if (!a || a->data == val) {
		return a;
	} else if (val > a->data) {
		return search(a->right, val);
	} else {
		return search(a->left, val);
	}
}

int count(BinTree *a) {
	int counter = 0;
	if (a) {
		counter+= count(a->left);
		counter+= count(a->right);
		return counter+1;
	}
	return 0;
}

int countLeaves(BinTree *a) {
	int counter = 0;
	if (a) {
		counter+= countLeaves(a->left);
		counter+= countLeaves(a->right);
		return ((a->left || a->right)?counter:counter+1);
	}
	return 0;
}

int degree(BinTree *a, int val) {
	// not a mistake in the line below...
	if (a = search(a, val)){ 
		int n = countLeaves(a); int degree=0;
		if (a->left || a->right){
			for (int k = n; k > 0; k--) {
				degree += factorial(n)/(factorial(k)*factorial(n-k));
			}
		}
		return degree;
	}
	return -1;
}

int height(BinTree *a) {
	if (a) {
		int l = height(a->left);
		int r = height(a->right);
		return 1 + ((l>r)?l:r);
	}
	return 0;
}

void ui(BinTree *&first) {
	int num = 1, n;
	while (num) {
		try {
			cout << "\n========================\n  0 -- exit; \n  1 -- createTree; \n  2 -- insert; \n  3 -- printTreeInARow; \n  4 -- search; \n  5 -- count;";
			cout << "\n  6 -- countLeaves; \n  7 -- degree; \n  8 -- height;";
			cout << "\n========================\ninput: ";
			cin >> num;
			cout << endl;
			switch (num) {
				case 0: break;
				case 1: cout << "n: "; cin >> n; createTree(first, n); break;
				case 2: cout << "val: "; cin >> n; insert(first, n); break;
				case 3: printTreeInARow(first); cout << endl; break;
				case 4: cout << "val: "; cin >> n; cout << (bool) search(first, n) << endl; break;
				case 5: cout << count(first) << endl; break;
				case 6: cout << countLeaves(first) << endl; break;
				case 7: cout << "val: "; cin >> n; cout << degree(first, n) << endl; break;
				case 8: cout << height(first) << endl; break;
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