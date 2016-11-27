#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>

const int LIST_TOO_SHORT = 0;
const int LIST_EMPTY = 1;

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

void pushFront(list *&a, int varible) {
	list *first = new list;
	first->inf = varible;
	first->next = a;
	a = first;
}

void pushBack(list *&a, int varible) {
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
		pushFront(a, varible);
	}
}

void insertAfter(list *&a, int pos, int varible) {
	bool enougthElements=true;
	list *temp = a;
	list *element = new list;
	element->inf = varible;
	if (temp){
		for (int i = 0; i < pos; i++) {
			if (!(temp->next)) { throw(LIST_TOO_SHORT); enougthElements=false; break;
			}else {
                temp = temp->next;
            }
        }
		if (enougthElements) {
			element->next = temp->next;
			temp->next = element;
		}
	} else {
		throw(LIST_EMPTY);
	}
}

void insertBefore(list *&a, int pos, int varible) {
	bool enougthElements=true;
	list *temp = a;
	if (temp){
		if (!pos) {
			pushFront(a, varible);
		} else if (pos == 1) {
			insertAfter(a,0, varible);
		} else {
			for (int i = 0; i < pos - 1; i++) {
				if (!((temp->next)->next)) { throw(LIST_TOO_SHORT); enougthElements=false; break;
				} else {
                    temp = temp->next;
                }
			}
			if (enougthElements) {
				list *element = new list;
				element->next = temp->next;
				temp->next = element;
				element->inf = varible;
			}
		}
	} else {
		throw(LIST_EMPTY);
	}
}

int shift(list *&a) { // èçâëå÷ü ïåðâûé
	list* prev = 0;
	int val;
	if (!a) {
		throw(LIST_EMPTY);
		return -1;
	}
	prev = a;
	val = prev->inf;
	a = a->next;
	delete prev;
	return val;
}
void del(list *&a, int pos) {
	bool enougthElements=true;
	list *temp = a;
	if (temp) {
        if (pos){
             for (int i = 0; i < pos - 1; i++) {
                if (!((temp->next)->next)) { throw(LIST_TOO_SHORT); enougthElements=false; break;
                } else {
                    temp = temp->next;
                }
             }
            if (enougthElements) {
                list *temp1 = temp->next;
                temp->next = temp1->next;
                delete temp1;
            }
		} else {
		    shift(a);
		}
	} else {
		throw(LIST_EMPTY);
	}
}

int pop(list *&a) {
	list* prev = 0;
	int val;
	if (!a) {
		throw(LIST_EMPTY);
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
	if (!a) a = new list;
}

int countElements(list *a) {
	int amount=0;
	while(a) {
		a = a->next;
		amount++;
	}
	return amount;
}

int nthElement(list *a, int pos) {
	bool enougthElements=true;
	list *temp = a;
	if (temp) {
        if(pos){
            for (int i = 0; i < pos - 1; i++) {
                if (!((temp->next)->next)) { throw(LIST_TOO_SHORT); enougthElements=false; break;
                } else {
                    temp = temp->next;
                }
            }
            if (enougthElements) {
                return (temp->next)->inf;
            }
        } else {
            return temp->inf;
        }
	} else {
		throw(LIST_EMPTY);
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

void copyList(list *&first, list *&second){
	memfree(second);
	list *p = first;
	list *s = second;
	if (p) {
		s->inf = p->inf;
		p = p->next;
		while(p) {
			s->next = new list;
			s = s->next;
			s->inf = p->inf;
			p = p->next;
		}
		s->next = 0;
	} else {
		throw(LIST_EMPTY);
	}
}


void fragmentation(list *&first, list *&second, list *&third) {
	memfree(second);
	memfree(third);
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
	int listSize = countElements(temp);
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
	list *second = 0;
	list *third = 0;
	int n;
	int pos;
	while (num) {
        try {
            cout << "\n========================\n  0 -- exit; \n  1 -- fillInRand; \n  2 -- printList; \n  3 -- pushFront; \n  4 -- insertAfter; \n  5 -- del;\n";
            cout << "  6 -- pushBack; \n  7 -- insertBefore; \n  8 -- shift; \n  9 -- pop; \n 10 -- memfree; \n 11 -- countElements; \n 12 -- nthElement; \n";
            cout << " 13 -- copyList; \n 14 -- fragmentation; \n 15 -- sortList; \n";
            cout << "========================\ninput: ";
            cin >> num;
            cout << endl;
            switch (num) {
                case 0: break;
                case 1: cout << "size: "; cin >> n; fillInRand(first,n); break;
                case 2: printList(first); break;
                case 3: cout << "num: ";  cin >> n; pushFront(first,n); break;
                case 4: cout << "pos: "; cin >> pos; cout << "num: ";  cin >> n; insertAfter(first, pos, n); break;
                case 5: cout << "pos: "; cin >> pos; del(first, pos); break;
                case 6: cout << "num: ";  cin >> n; pushBack(first,n); break;
                case 7: cout << "pos: "; cin >> pos; cout << "num: ";  cin >> n; insertBefore(first,pos,n); break;
                case 8: cout << shift(first) << endl; break;
                case 9: cout << pop(first) << endl; break;
                case 10: memfree(first); break;
                case 11: cout<< countElements(first) << endl; break;
                case 12: cout << "pos: "; cin >> pos; cout<< nthElement(first, pos) << endl; break;
                case 13: copyList(first, second); cout<< "copied list:" << endl; printList(second); break;
                case 14: fragmentation(first, second, third); cout<< "fragments:" << endl; printList(second); cout<< "and:" << endl;printList(third); break;
                case 15: sortList(first);  break;
                default: cout << "error" << endl;
            }
		}
		catch(int ex) {
		    switch (ex){
                case LIST_EMPTY: cout << "LIST EMPTY" << endl; break;
                case LIST_TOO_SHORT: cout << "LIST IS TOO SHORT" << endl; break;
		    }

		}
	}
}

int main() {
	srand((unsigned)time(0));

	list *first = 0;

	ui(first);

	return 0;
}