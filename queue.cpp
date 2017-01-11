
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>

const int QUEUE_EMPTY = 0;

using namespace std;

struct Queue {
	int data;
	Queue *next;
};

int irand() {
	return rand() % 51 - 25;
}
void push(Queue *&first, Queue *&last, int val) {
	if (first) {
		last->next = new Queue;
		last->next->data = val;
		last->next->next = 0;
		last = last->next;
	} else {
		first = new Queue;
		first->data = val;
		first->next = 0;
		last=first;			
	}
}

int pop(Queue *&first, Queue *&last) {
	if (first) {
		int result = first->data;
		if (first->next) {
			Queue *temp = first;
			first = first->next;
			delete temp;
		} else {
			delete first;
			first = last = 0;
		}
		return result;
	} else {
		throw QUEUE_EMPTY;
	}
}

void printQueue(Queue *a) {
	while (a) {
		cout << a->data << " ";
		a = a->next;
	}
	cout << endl;
}

void ui(Queue *&first, Queue *&last) {
	int num = 1, n;
	while (num) {
		try {
			cout << "\n========================\n  0 -- exit; \n  1 -- push; \n  2 -- pop; \n  3 -- printQueue;";
			cout << "\n========================\ninput: ";
			cin >> num;
			cout << endl;
			switch (num) {
			case 0: break;
			case 1: cout << "val: "; cin >> n; push(first, last, n); break;
			case 2: cout << pop(first, last) << endl; break;
			case 3: printQueue(first); break;
			default: cout << "error" << endl;
			}
		}
		catch (int ex) {
			switch (ex) {
			case QUEUE_EMPTY: cout << "STACK IS EMPTY" << endl; break;
			}
		}
	}
}

int main() {
	Queue *first = 0;
	Queue *last = 0;
	ui(first, last);
	return 0;
}