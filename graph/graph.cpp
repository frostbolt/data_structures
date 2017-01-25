#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <conio.h>

const int MATRIX_EMPTY = 0;
const int WRONG_FILE = 1;

using namespace std;

template <typename T>
struct list {
	T inf;
	list* next;
};

class AdjacencyMatrix {
	short dim;
	bool **data;
public:
	AdjacencyMatrix(const char pathToFile[256]){ // инициализация с помощью файла.
		ifstream file(pathToFile);
		if (file.is_open())	{
			file >> dim;
			data = new bool *[dim]; // кв. матрица.
			for (int i = 0; i < dim; i++) {
				data[i] = new bool[dim];
				for (int j = 0; j < dim; j++) file >> data[i][j];
			}
		} else throw(WRONG_FILE);
	}
	~AdjacencyMatrix(){ // очистка динамической памяти в деструкторе.
		for (int i = 0; i < dim; i++) delete[] data[i];
		delete data;
	}

	int getDim() {
		return dim;
	}

	int getCell(int i, int j) {
		return data[i][j];
	}

	void print() {
		cout << "dimention: "<<dim<<"x"<<dim<<endl;
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) cout << data[i][j] << "\t";
			cout << endl;
		}
	}	
};

class IncidenceMatrix {
	int dimV, dimE;
	int **data;
public:
	IncidenceMatrix(AdjacencyMatrix a){
		dimV = a.getDim();
		dimE = 0;
		for (int i = 0; i < dimV; i++)
			for (int j = i; j < dimV; j++)
				if (a.getCell(i,j)) dimE++;

		data = new int *[dimV]; 
		for (int i = 0; i < dimV; i++) {
			data[i] = new int[dimE];
		}

		int currentEdge = 0;
		for (int i = 0; i < dimV; i++)
			for (int j = i+1; j < dimV; j++)
				if (a.getCell(i,j)){
					data[i][currentEdge]=data[j][currentEdge]=1;
					currentEdge++;
				}
	}

	~IncidenceMatrix(){ // очистка динамической памяти в деструкторе.
		for (int i = 0; i < dimV; i++) delete[] data[i];
		delete data;
	}

	void print() {
		cout << "dimention: "<<dimV<<"x"<<dimE<<endl;
		for (int i = 0; i < dimV; i++) {
			for (int j = 0; j < dimE; j++) cout << data[i][j] << "\t";
			cout << endl;
		}
	}	
};

class EdgesMatrix {
	int dimE;
	short **data;
public:
	EdgesMatrix(AdjacencyMatrix a){
		dimE = 0;
		int aDim=a.getDim();
		for (int i = 0; i <aDim; i++) {
			for (int j = i+1; j < aDim; j++) {
				dimE += a.getCell(i,j);
			}
		}

		data = new short * [dimE];
		for (int i = 0; i < dimE; i++)  data[i] = new short[2];

		short edge = 0;
		for (int i = 0; i <aDim; ++i)
			for (int j = i+1; j < aDim; j++)
				if (a.getCell(i,j)) {
					data[edge][0]= i+1;
					data[edge][1]= j+1;
					edge++;
				}
	}

	~EdgesMatrix(){ // очистка динамической памяти в деструкторе.
		for (int i = 0; i < dimE; i++) delete[] data[i];
		delete data;
	}

	void print() {
		cout << "dimention: "<<dimE<<"x"<<2<<endl;
		for (int i = 0; i < dimE; i++) {
			for (int j = 0; j < 2; j++) cout << data[i][j] << "\t";
			cout << endl;
		}
	}	
};

class ListOfLinks {
	list<list<short>*> *data;
public:
	ListOfLinks(AdjacencyMatrix a){
		short aDim = a.getDim();
		list<list<short>*> *temp = 0;
		list<short> *tempH = 0;
		
		bool first = true;
		for (int i = 0; i < aDim; i++){
			if (first) {
				first = false;
				temp = new list<list<short>*>;
				data = temp;
			}
			else {
				temp->next = new list<list<short>*>;
				temp = temp->next;
			}

			tempH = new list<short>;
			temp->inf = tempH;
			tempH->inf = i+1;
			for (short j = 0; j < aDim; j++) {
				if (a.getCell(i,j)) {
					tempH->next = new list<short>;
					tempH = tempH->next;
					tempH->inf = j+1;
				}
			}
			tempH->next = 0;
		}
		temp->next = 0;
	}
	void print() {
		list<list<short>*> *temp = data;
		while (temp){
			list<short> *tempH = temp->inf;
			while (tempH){
				cout << tempH->inf << " ";
				tempH = tempH->next;
			}
			cout << endl;
			temp = temp->next;
		}

	}
	~ListOfLinks(){}
};

void ui(AdjacencyMatrix first) {
	IncidenceMatrix second(first);
	EdgesMatrix third(first);
	ListOfLinks fourth(first);
	int num = 1, n;
	while (num) {
		try {
			cout << "\n========================\n  0 -- exit; \n  1 -- (AdjacencyMatrix) print; \n  2 -- (IncidenceMatrix) print; \n  3 -- (EdgesMatrix) print; \n  4 -- (ListOfLinks) print;";
			cout << "\n========================\ninput: ";
			cin >> num;
			cout << endl;
			switch (num) {
				case 0: break;
				case 1: first.print(); break;
				case 2: second.print(); break;
				case 3: third.print(); break;
				case 4: fourth.print(); break;
				default: cout << "error" << endl;
			}
		}
		catch (int ex) {
			switch (ex) {
				case MATRIX_EMPTY: cout << "MATRIX IS EMPTY" << endl; break;
				case WRONG_FILE: cout << "FILE IS DAMAGED OR COULD NOT BE OPENED" << endl; break;

			}
		}
	}
}


int main() {
	AdjacencyMatrix first("adj.txt");
	ui(first);
	return 0;
}
