/*
#include "CMatrix.h"
using namespace std;
#include <iostream> //usunac pozniej


//konstruktory//////////////////////////////////////////
template <typename T>
CMatrix<T> :: CMatrix() {
	irow = 2;
	icolumn = 2;
	pcMatrix = new T* [irow];
	for (int i = 0; i < irow; i++)
	{
		pcMatrix[i] = new T [icolumn];
	}
}

template <typename T>
CMatrix<T> :: CMatrix(int row,int column) {
	irow = row;
	icolumn = column;
	pcMatrix = new T* [irow];
	for (int i = 0; i < irow; i++)
	{
		pcMatrix[i] = new T [icolumn];
	}
}
//destruktor/////////////////////////////////
template <typename T>
CMatrix<T> :: ~CMatrix<T>() {
	for (int i = 0; i < igetRow(); i++) {
		delete[] pcMatrix[i];
	}
	delete[] pcMatrix;
}

template <typename T> // konstruktor kopiujacy
CMatrix<T> :: CMatrix(const CMatrix& cOther) {
	irow = cOther.irow;
	icolumn = cOther.icolumn;
	pcMatrix = new T * [irow];
	for (int i = 0; i < cOther.irow; i++) {
		pcMatrix[i] = new T[icolumn];
		for (int j = 0; j < cOther.icolumn; j++) {
			pcMatrix[i][j] = cOther.pcMatrix[i][j];
		}
	}
}

template <typename T> // konstruktor przenoszacy
CMatrix<T> :: CMatrix(CMatrix&& cOther) {
	irow = cOther.irow;
	icolumn = cOther.icolumn;
	cOther.irow = 0;
	cOther.icolumn = 0;
	pcMatrix = cOther.pcMatrix;
	cOther.pcMatrix = nullptr;
}

//metody/////////////////////////////////////////
template <typename T>
CMatrix<T>  CMatrix<T>::newMatrix(int rows, int columns) {
	CMatrix<T> CNew(rows, columns);
}


//operator przenoszacy
template <typename T> 
CMatrix<T> CMatrix<T>::operator=(CMatrix&& cOther) {
	irow = cOther.irow;
	icolumn = cOther.icolumn;
	cOther.irow = 0;
	cOther.icolumn = 0;
	pcMatrix = cOther.pcMatrix;
	cOther.pcMatrix = nullptr;
	return *this;
}

/////////////////////////////////////////////////////////////

template <typename T>
void CMatrix<T>::fillMatrix() {
	for (int i = 0; i < irow; i++) {
		for (int j = 0; j < icolumn; j++) {
			pcMatrix[i][j] = i + j + 1;
		}
	}
}

template <typename T>
void CMatrix<T>::show() {
	for (int i = 0; i < irow; i++) {
		cout << endl;
		for (int j = 0; j < icolumn; j++) {
			cout << pcMatrix[i][j] << " "; //usunac pozniej
		}
	}
}
*/

/*template <typename T>
bool CMatrix<T>::bSetColumn(int newColumn) {
	if (newColumn < 1) return false;

	CMatrix<T> cNew(irow, newColumn);

	for (int i = 0; i < cNew.irow; i++) {
		for (int j = 0; j < icolumn && j < newColumn; j++) {
			cNew.pcMatrix[i][j] = pcMatrix[i][j];
		}
	}

	for (int i = 0; i < irow; i++) {
		delete[] pcMatrix[i];
	}
	delete[] pcMatrix;

	icolumn = newColumn;
	*this = move(cNew);
	return true;
}

template <typename T>
bool CMatrix<T>::bSetRow(int newRow) {
	if (newRow <= 0) return false;

	CMatrix<T> cNew(newRow, icolumn);

	pcMatrix
	for (int i = 0; i < this.irow && i < newRow; i++) {
		cNew.pcMatrix[i] = pcMatrix[i];
	}

	for (int i = 0; i < irow; i++) {
		pcMatrix[i] = nullptr;
	}
	pcMatrix = nullptr;
	irow = newRow;
	return true;
}*/