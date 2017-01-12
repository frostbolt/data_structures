#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>

const int DEQUE_EMPTY = 0;

using namespace std;

struct Deque {
	int data;
	Deque *next;
	Deque *prev;
};

int irand() {
	return rand() % 51 - 25;
}

void push(Deque *&first, Deque *&last, int val) { // в конец
	if (first) {
		last->next = new Deque;
		last->next->data = val;
		last->next->next = 0;
		last->next->prev = last;
		last = last->next;
	}
	else {
		first = new Deque;
		first->data = val;
		first->next = first->prev = 0;
		last = first;
	}
}

void unshift(Deque *&first, Deque *&last, int val) { // в начало
	if (first) {
		first->prev = new Deque;
		first->prev->data = val;
		first->prev->next = first;
		first->prev->prev = 0;
		first = first->prev;
	}
	else {
		first = new Deque;
		first->data = val;
		first->next = first->prev = 0;
		last = first;
	}
}

int pop(Deque *&first, Deque *&last) { // извлечение из конца.
	if (first) {
		int result = last->data;
		if (last->prev) {
			Deque *temp = last;
			last = last->prev;
			last->next = 0;
			delete temp;
		}
		else {
			delete last;
			first = last = 0;
		}
		return result;
	}
	else {
		throw DEQUE_EMPTY;
	}
}

int shift(Deque *&first, Deque *&last) { // сдвиг. извлечение из начала.
	if (first) {
		int result = first->data;
		if (first->next) {
			Deque *temp = first;
			first = first->next;
			first->prev = 0;
			delete temp;
		}
		else {
			delete first;
			first = last = 0;
		}
		return result;
	}
	else {
		throw DEQUE_EMPTY;
	}
}




void printDeque(Deque *a) {
	while (a) {
		cout << a->data << " ";
		a = a->next;
	}
	cout << endl;
}

void ui(Deque *&first, Deque *&last) {
	int num = 1, n;
	while (num) {
		try {
			cout << "\n========================\n  0 -- exit; \n  1 -- push; \n  2 -- pop; \n  3 -- unshift; \n  4 -- shift; \n  5 -- printDeque;";
			cout << "\n========================\ninput: ";
			cin >> num;
			cout << endl;
			switch (num) {
			case 0: break;
			case 1: cout << "val: "; cin >> n; push(first, last, n); break;
			case 2: cout << pop(first, last) << endl; break;
			case 3: cout << "val: "; cin >> n; unshift(first, last, n); break;
			case 4: cout << shift(first, last) << endl; break;
			case 5: printDeque(first); break;
			default: cout << "error" << endl;
			}
		}
		catch (int ex) {
			switch (ex) {
			case DEQUE_EMPTY: cout << "STACK IS EMPTY" << endl; break;
			}
		}
	}
}

int main() {
	Deque *first = 0;
	Deque *last = 0;
	ui(first, last);
	return 0;
}