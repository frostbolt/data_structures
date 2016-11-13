#include <stdlib.h> 
#include <time.h> 
#include <iostream> 
#include <conio.h> 

using namespace std;

struct list {
	int inf;
	list * next;
};

void fillInRand(list *&b, int n) {
	list *a =new list;
	b = a;

	for (int i = 0; i < n - 1; i++) {
		a->inf = rand() % 101 - 50;
		a->next = new list;
		a = a->next;
	}

	a->inf = rand() % 101 - 50;
	a->next = 0;
}

void printList(list *a) {
	while (a) {
		cout << a->inf << " ";
		a = a->next;
	}
	cout << endl;
}

list* pushFront(int varible, list *a) {
	list *first = new list;
	first->inf = varible;
	first->next = a;
	return first;
}

void pushBack(int varible, list *a) {
	list *temp = a;
	list *element = new list;
	element->next = 0;
	element->inf = varible;
	if (temp){
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = element;
	} else {
		pushFront(varible, a);
	}
}

void insertAfter(int varible, int pos, list *a) {
	bool enougthElements=true;
	list *temp = a;
	list *element = new list;
	element->inf = varible;
	if (temp){
		for (int i = 0; i < pos; i++) {
			if (!temp->next) { cout << "Error. list is too short." << endl; enougthElements=false; break; }
			temp = temp->next;
		}
		if (enougthElements) {
			element->next = temp->next;
			temp->next = element;
		}
	} else {
		cout << "Error. list is empty." << endl;
	}
}

void insertBefore(int varible, int pos, list *a) {
	bool enougthElements=true;
	list *temp = a;
	if (temp){
		if (!pos) {
			pushFront(varible, a);
		} else if (pos == 1) {
			insertAfter(varible, 0, a);
		} else {
			for (int i = 0; i < pos - 1; i++) {
				if (!temp->next) { cout << "Error. list is too short." << endl; enougthElements=false; break; }
				temp = temp->next;
			}
			if (enougthElements) {
				list *element = new list;
				element->next = temp->next;
				temp->next = element;
				element->inf = varible;
			}
		}
	} else {
		cout << "Error. list is empty." << endl;
	}
}

void del(int pos, list *a) {
	bool enougthElements=true;
	list *temp = a;
	if (temp) {
		for (int i = 0; i < pos - 1; i++) {
			if (!temp->next) { cout << "Error. list is too short." << endl; enougthElements=false; break; }
			temp = temp->next;
		}
		if (enougthElements) {
			list *temp1 = temp->next;
			temp->next = temp1->next;
			delete temp1;
		}
	} else {
		cout << "Error. list is empty." << endl;
	}
}

int shift(list *&a) {
	list* prev = 0;
	int val;
	if (!a) {
		cout << "Error. list is empty." << endl;
		return -1;
	}
	prev = a;
	val = prev->inf;
	a = a->next;
	delete prev;
	return val;
}

int pop(list *&a) {
	list* prev = 0;
	int val;
	if (!a) {
		cout << "Error. list is empty." << endl;
		return -1;
	}
	prev = a;
	while ((prev->next)->next) {
		prev = prev->next;
	}
	val = (prev->next)->inf;
	delete (prev->next)->next;
	prev->next = 0;
	return val;
}

void memfree(list *&a) {
	while(a) {
		list* prev = a;
		a = a->next;
		delete prev;
	}
	delete a;
}

int countElements(list *a) {
	int amount=0;
	while(a) {
		a = a->next;
		amount++;
	}
	return amount;
}

int nthElement(int pos, list *a) {
	bool enougthElements=true;
	list *temp = a;
	if (temp) {
		for (int i = 0; i < pos - 1; i++) {
			if (!temp->next) { cout << "Error. list is too short." << endl; enougthElements=false; break; }
			temp = temp->next;
		}
		if (enougthElements) {
			return (temp->next)->inf;
		}
	} else {
		cout << "Error. list is empty." << endl;
		return -1;
	}
	return -1;
}

// list* addressByValue(int val, list *a) {
// 	list *temp = a;
// 	list *result;

// 	while (temp) {
// 		if (temp->inf == val) {
// 			result->inf = val;
// 			result->next = new list;
// 		}
// 	}
// 	return result;
// }

void copyList(list *first, list *&second){
	list *p = first;
	if (p) {
		second->inf = p->inf;
		p = p->next;
		list *newfirst = second;
		while(p) {
			second->next = new list;
			second = second->next;
			second->inf = p->inf;
			p = p->next;
		}
		second->next = 0;
	} else {
		cout << "Error. list is empty." << endl;
	}
}


void fragmentation(list *first, list *&second, list *&third) {
	list *p = first;
	list *p1 = second;
	list *p2 = third;
	list *w1 = p1;
	list *w2 = p2;
	while (p) {
		if (p->inf % 2) {
			p2->inf = p->inf;
			p2->next = new list;
			w2 = p2;
			p2 = p2->next;
		} else {
			p1->inf = p->inf;
			p1->next = new list;
			w1 = p1;
			p1 = p1->next;
		}
		p = p->next;
	}
	w1->next = 0;
	w2->next = 0;
}


void quicksort(int a, int b, int *arr){ 
	int center = arr[(a + b) / 2]; 
	int na = a; int nb = b; 
	while (na <= nb) { 
		while (arr[na] < center) na++; 
		while (arr[nb] > center) nb--; 
		if (na <= nb) { 
			int cup; 
			cup=arr[na]; 
			arr[na]=arr[nb]; 
			arr[nb]=cup; 
			na++; 
			nb--; 
		} 
	} 
	if (na<b) quicksort(na, b, arr); 
	if (a<nb) quicksort(a, nb, arr); 
} 

void sortList(list *first) {
	list *temp = first;
	int listSize = Count(temp);
	int *a = new int[listSize];
	for (int i = 0; i < listSize; i++) {
		a[i] = temp->inf;
		temp = temp->next;
	}
	quicksort(0, listSize - 1, a);
	for (int i = 0; i < listSize; i++) {
		first->inf = a[i];
		first= first->next;
	}
}



void ui(list *first) {
	int num = 1;
	while (num) {
		cout << "\n========================\n 1 -- fillInRand; \n 2 -- printList; \n 3 -- pushFront 3333; \n 4 -- insertAfter 4444; \n 0 -- exit; \n 5 -- del 5;\n";
		cout << " 6 -- pushBack 6666; \n 7 -- insertBefore 7; \n 8 -- shift; \n 9 -- pop; \n 10 -- memfree; \n";
		cout << "========================\ninput: ";
		cin >> num;
		cout << endl;
		switch (num) {
		case 0: break;
		case 1: fillInRand(first, 10); break;
		case 2: printList(first); break;
		case 3: first = pushFront(3333, first); break;
		case 4: insertAfter(4444, 4, first); break;
		case 5: del(5, first); break;
		case 6: pushBack(6666, first); break;
		case 7: insertBefore(7777, 7, first); break;
		case 8: cout << shift(first) << endl; break;
		case 9: cout << pop(first) << endl; break;
		case 10: memfree(first); break;
		case 11: countElements(first); break;
		default: cout << "error" << endl;
		}
	}
}

int main() {
	srand((unsigned)time(0));

	list *first = 0;

	ui(first);

	return 0;
}
