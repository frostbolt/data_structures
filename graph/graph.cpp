#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <conio.h>

const int MATRIX_EMPTY = 0;
const int WRONG_FILE = 1;

using namespace std;

class AdjacencyMatrix {
	int dim;
	int **data;
public:
	AdjacencyMatrix(const char pathToFile[256]){ // инициализация с помощью файла.
		ifstream file(pathToFile);
		if (file.is_open())	{
			file >> dim;
			data = new int *[dim]; // кв. матрица.
			for (int i = 0; i < dim; i++) {
				data[i] = new int[dim];
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
	int dimV;
	int dimE;
	int **data;
public:
	IncidenceMatrix(AdjacencyMatrix a){
		dimV = a.getDim();
		dimE = 0;
		for (int i = 0; i < dimV; i++)
			for (int j = i+1; j < dimV; j++)
				if (a.getCell(i,j)) dimE++;

		data = new int *[dimV]; 
		for (int i = 0; i < dimV; i++) {
			data[i] = new int[dimE];
		}
		for (int i = 0; i < dimV; ++i) {
			for (int i = 0; i < dimE; ++i)
			{
				/* code */
			}
		}

	}
	~IncidenceMatrix(){ // очистка динамической памяти в деструкторе.
		for (int i = 0; i < dim; i++) delete[] data[i];
		delete data;
	}

	void print() {
		cout << "dimention: "<<dim<<"x"<<dim<<endl;
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) cout << data[i][j] << "\t";
			cout << endl;
		}
	}	
};

void ui(AdjacencyMatrix first) {
	int num = 1, n;
	while (num) {
		try {
			cout << "\n========================\n  0 -- exit; \n  1 -- (AdjacencyMatrix) print;";
			cout << "\n========================\ninput: ";
			cin >> num;
			cout << endl;
			switch (num) {
				case 0: break;
				case 1: first.print(); break;
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
	AdjacencyMatrix first("incidence.txt");
	ui(first);
	return 0;
}
