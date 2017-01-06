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
	for (int i = 0; i < n; i++) {
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

BinTree* searchTwo(BinTree *a, int val) {
    if (!a || a->data == val) {
		return a;
	} else {
	    BinTree* right = searchTwo(a->right, val);
	    return (right)?right:searchTwo(a->left, val);
	}
}

int level(BinTree *a, int val) {
	if (!a) {
        throw(TREE_SHORT);
	} else if (a->data == val) {
	    return 0;
	} else if (val > a->data) {
		return 1 + level(a->right, val);
	} else {
		return 1 + level(a->left, val);
	}
}

int count(BinTree *a) {
	int counter = 0;
	if (a) {
		counter += count(a->left);
		counter += count(a->right);
		return counter+1;
	}
	return 0;
}

int countLeaves(BinTree *a) {
	int counter = 0;
	if (a) {
		counter += countLeaves(a->left);
		counter += countLeaves(a->right);
		return ((a->left || a->right)?counter:counter+1);
	}
	return 0;
}

int degree(BinTree *a, int val) {
	// not a mistake in the line below...
	if (a = search(a, val)){
		if (a->left && a->right) {
			return 2;
		} else if (a->left || a->right) {
			return 1;
		}
		return 0;
	}
	return -1;
}

BinTree* searchForParent(BinTree *a, int val) {
    if ((a->left)->data == val || (a->right)->data == val) {
        return a;
	} else {
	     return ((a->data > val)? searchForParent(a->right, val) : searchForParent(a->left, val));
	}
}

void delTree(BinTree *a) {
	if (!a) return;
    delTree(a->left);
    delTree(a->right);
    delete a;
}

void delSubtree(BinTree *a, int val) {
    a = searchForParent(a,val);
    if ((a->left)->data == val) {
        delTree(a->left);
        a->left = 0;
    } else {
        delTree(a->right);
        a->right = 0;
    }
}

void delNode(BinTree *a, int val) {
    a = searchForParent(a,val);
    BinTree* temp = ((a->left)->data == val)? a->left : a->right;
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
			cout << "\n  6 -- countLeaves; \n  7 -- degree; \n  8 -- height; \n  9 -- level; \n 10 -- searchTwo; \n 11 -- delSubtree; \n 12 -- delTree;";
			cout << "\n 13 -- delNode;";
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
				case 9: cout << "val: "; cin >> n; cout << level(first, n) << endl; break;
				case 10: cout << "val: "; cin >> n; cout << searchTwo(first, n) << endl; break;
				case 11: cout << "val: "; cin >> n; delSubtree(first, n); break;
				case 12: delTree(first); break;
				case 13: cout << "val: "; cin >> n; delNode(first, n); break;
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
