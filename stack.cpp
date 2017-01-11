#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>

const int STACK_EMPTY = 0;

using namespace std;

struct Stack {
	int data;
	Stack *next;
};

int irand() {
	return rand() % 51 - 25;
}

void push(Stack *&a, int val) {
	Stack *temp = new Stack;
	temp->data = val;
	temp->next = a;
	a = temp;
}

int pop(Stack *&a) {
	if (a) {
		int result = a->data;
		Stack *temp = a;
		a = a->next;
		delete temp;
		return result;
	}
	else {
		throw STACK_EMPTY;
	}
}

void reverse(Stack *&a) {
	Stack *temp = 0;
	while (a) push(temp, pop(a));
	a = temp;
}

void printStack(Stack *a) {
	reverse(a);
	while (a) {
		cout << a->data << " ";
		a = a->next;
	}
	cout << endl;
}

void reversePrint(Stack *&a) {
	Stack *temp = 0;
	reverse(a);
	while (a) {
		cout << a->data << " ";
		push(temp, pop(a));
	}
	a = temp;
	cout << endl;
}

void createDemoStack(Stack *&a, int size) {
	for (int i = 0; i < size; i++) push(a, irand());
}

void ui(Stack *&first) {
	int num = 1, n;
	while (num) {
		try {
			cout << "\n========================\n  0 -- exit; \n  1 -- push; \n  2 -- pop; \n  3 -- reverse; \n  4 -- reversePrint; \n  5 -- createDemoStack";
			cout << "\n========================\ninput: ";
			cin >> num;
			cout << endl;
			switch (num) {
			case 0: break;
			case 1: cout << "val: "; cin >> n; push(first, n); break;
			case 2: cout << pop(first) << endl; break;
			case 3: reverse(first); break;
			case 4: reversePrint(first); break;
			case 5: cout << "n: "; cin >> n; createDemoStack(first, n); break;
			default: cout << "error" << endl;
			}
		}
		catch (int ex) {
			switch (ex) {
			case STACK_EMPTY: cout << "STACK IS EMPTY" << endl; break;
			}
		}
	}
}

int main() {
	Stack *first = 0;
	ui(first);
	return 0;
}