#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "CError.h"
using namespace std;

static const int DEFAULT_ROW = 4;
static const int DEFAULT_COLUMN = 4;
static const double DEFAULT_VALUE = 0.0;

template <typename T> 
class CMatrix
{
public:
	CMatrix();
	CMatrix(int rows, int columns, CError* error);
	CMatrix(const CMatrix& cOther);
	CMatrix(CMatrix&& cOther);
	~CMatrix();

	bool bReadFile(string fName, CError* error);
	bool bNotNumber(string value);
	int igetRow() { return irow; };
	int igetColumn() { return icolumn; };

	bool bSetValue(int row, int column, T value);
	T tGetValue(int row, int column, CError* error);
	void newMatrix(int rows, int columns, CError* error);
	CMatrix<T> add(const CMatrix<T>& cOther, CError* error);
	CMatrix<T> subtract(const CMatrix<T>& cOther, CError* error);
	CMatrix<T> multiply(const CMatrix<T>& cOther, CError* error);
	CMatrix<T> multiply(T number);
	T scalarProduct(const CMatrix<T>& cOther, CError* error);
	CMatrix<T> transpose();
	bool bInvert();
	CMatrix<T> vectorFromColumn(int column, CError* error);
	CMatrix<T> vectorFromRow(int row, CError* error);
	bool bIdentityMatrix();
	
	void operator=(CMatrix<T>&& cOther);
	CMatrix<T> operator+(const CMatrix<T>& cOther);
	CMatrix<T> operator-(const CMatrix<T>& cOther);
	CMatrix<T> operator*(const CMatrix<T>& cOther);
	CMatrix<T> operator*(T number);


	void fillMatrix();
	void show();
private:
	int irow;
	int icolumn;
	T** pcMatrix;
};



//konstruktory//////////////////////////////////////////
template <typename T>
CMatrix<T> :: CMatrix() {
	irow = DEFAULT_ROW;
	icolumn = DEFAULT_COLUMN;
	pcMatrix = new T * [irow];
	for (int i = 0; i < irow; i++){
		pcMatrix[i] = new T[icolumn];
	}
}

template <typename T>
CMatrix<T> :: CMatrix(int row, int column, CError* error) {
	error->setError(NO_ERROR);
	if (row < 1 || column < 1) {
		error->setError(INVALID_SIZE);
		irow = 0;
		icolumn = 0;
		pcMatrix = nullptr;
	}
	else {
		irow = row;
		icolumn = column;
		pcMatrix = new T * [irow];
		for (int i = 0; i < irow; i++)
		{
			pcMatrix[i] = new T[icolumn];
		}
	}
}

template <typename T> 
CMatrix<T> ::CMatrix(const CMatrix& cOther) {
	irow = cOther.irow;
	icolumn = cOther.icolumn;
	pcMatrix = new T * [irow];
	for (int i = 0; i < cOther.irow; i++){
		pcMatrix[i] = new T[icolumn];
		for (int j = 0; j < cOther.icolumn; j++) {
			pcMatrix[i][j] = cOther.pcMatrix[i][j];
		}
	}
}

template <typename T> 
CMatrix<T> :: CMatrix(CMatrix&& cOther) {
	*this = move(cOther);			//wywolanie operatora przenoszenia
	/*irow = cOther.irow;
	icolumn = cOther.icolumn;
	cOther.irow = 0;
	cOther.icolumn = 0;
	pcMatrix = cOther.pcMatrix;
	cOther.pcMatrix = nullptr;*/
}

template <typename T>
CMatrix<T> :: ~CMatrix() {
	for (int i = 0; i < igetRow(); i++) {
		delete[] pcMatrix[i];
	}
	delete[] pcMatrix;
}

//metody/////////////////////////////////////////
template <typename T>
void  CMatrix<T>::newMatrix(int rows, int columns, CError* error) {
	error->setError(NO_ERROR);
	if (rows < 1 || columns < 1) {
		error->setError(INVALID_SIZE);
		irow = 0;
		icolumn = 0;
		pcMatrix = nullptr;
	}
	for (int i = 0; i < irow; i++) {
		delete[] pcMatrix[i];
	}
	delete[] pcMatrix;
	
	pcMatrix = new T * [rows];
	for (int i = 0; i < rows; i++)
	{
		pcMatrix[i] = new T[columns];
	}
	irow = rows;
	icolumn = columns;
}
/*
template <typename T>
void  CMatrix<T>::newMatrix(int rows, int columns, CError* error) {
	T** newMatrix;
	newMatrix = new T * [rows];
	for (int i = 0; i < rows; i++)
	{
		newMatrix[i] = new T[columns];
	}
	for (int i = 0; i < irow && i < rows; i++) {
		for (int j = 0; j < icolumn && j < columns; j++) {
			cout << pcMatrix[i][j];
			newMatrix[i][j] = pcMatrix[i][j];
		}
	}
	for (int i = 0; i < irow; i++) {
		delete[] pcMatrix[i];
	}
	delete[] pcMatrix;
	irow = rows;
	icolumn = columns;
	pcMatrix = newMatrix;
}*/

template <typename T>
CMatrix<T>  CMatrix<T>::add(const CMatrix<T>& cOther, CError* error) {
	error->setError(NO_ERROR);
	CMatrix<T> cNew(irow, icolumn, error);
	if (cOther.icolumn != icolumn || cOther.irow != irow) {
		error->setError(INVALID_DIMENSION);
		return move(cNew);
	}
	for (int i = 0; i < irow; i++) {
		for (int j = 0; j < icolumn; j++) {
			cNew.pcMatrix[i][j] = cOther.pcMatrix[i][j] + pcMatrix[i][j];
		}
	}
	return move(cNew);
}

template <typename T>
CMatrix<T>  CMatrix<T>::subtract(const CMatrix<T>& cOther, CError* error) {
	error->setError(NO_ERROR);
	CMatrix<T> cNew(irow, icolumn, error);
	if (cOther.icolumn != icolumn || cOther.irow != irow) {
		error->setError(INVALID_DIMENSION);
		return move(cNew);
	}
	for (int i = 0; i < irow; i++) {
		for (int j = 0; j < icolumn; j++) {
			cNew.pcMatrix[i][j] =  pcMatrix[i][j] - cOther.pcMatrix[i][j];
		}
	}
	return move(cNew);
}

template <typename T>
CMatrix<T>  CMatrix<T>::multiply(T number) {
	CError error;
	CMatrix<T> cNew(irow, icolumn, &error);
	for (int i = 0; i < irow; i++) {
		for (int j = 0; j < icolumn; j++) {
			cNew.pcMatrix[i][j] = pcMatrix[i][j] * number;
		}
	}
	return move(cNew);
}
template <typename T>
CMatrix<T> CMatrix<T>::multiply(const CMatrix<T>& cOther, CError* error) {
	error->setError(NO_ERROR);
	CMatrix<T> cNew(irow, cOther.icolumn, error);
	if (icolumn != cOther.irow) {
		error->setError(INVALID_DIMENSION);
		return move(cNew);
	}
	for (int i = 0; i < cNew.irow; i++) {
		for (int j = 0; j < cNew.icolumn; j++) {
			cNew.pcMatrix[i][j] = 0;
			for (int k = 0; k < icolumn; k++) {
				cNew.pcMatrix[i][j] += pcMatrix[i][k] * cOther.pcMatrix[k][j];
			}
		}				
	}
	return move(cNew);
	
}

template <typename T>
CMatrix<T> CMatrix<T>::transpose() {
	CError error;
	CMatrix<T> CNew(icolumn, irow, &error);
	for (int i = 0; i < CNew.igetRow(); i++) {
		for (int j = 0; j < CNew.igetColumn(); j++) {
			CNew.pcMatrix[i][j] = pcMatrix[j][i];
		}
	}
	return move(CNew);
}

template <typename T>
CMatrix<T> CMatrix<T>::vectorFromColumn(int column, CError* error) {
	error->setError(NO_ERROR);
	CMatrix<T> CNew(1, irow, error);
	if (column >= 0 && column < icolumn) {
		for (int i = 0; i < CNew.igetColumn(); i++) {
			CNew.pcMatrix[0][i] = pcMatrix[i][column];
		}
		return move(CNew);
	}
	error->setError(INVALID_VALUE);
	return move(CNew);
}

template <typename T>
CMatrix<T> CMatrix<T>::vectorFromRow(int row, CError* error) {
	error->setError(NO_ERROR);
	CMatrix<T> CNew(1, icolumn, error);
	if (row >= 0 && row < irow) {
		for (int i = 0; i < icolumn; i++) {
			CNew.pcMatrix[0][i] = pcMatrix[row][i];
		}
		return move(CNew);
	}
	error->setError(INVALID_VALUE);
	return move(CNew);
}

template <typename T>		
bool CMatrix<T>::bSetValue(int row, int column, T value) {
	if (row < irow && row >= 0 && column < icolumn && column >= 0) {
		pcMatrix[row][column] = value;
		return true;
	}
	return false;
}

template <typename T> 
T CMatrix<T>::tGetValue(int row, int column, CError* error) {
	error->setError(NO_ERROR);
	if (row < irow && row >= 0 && column < icolumn && column >= 0) {
		return pcMatrix[row][column];
	}
	error->setError(INVALID_VALUE);
	return NULL;
}

template <typename T>
T CMatrix<T>::scalarProduct(const CMatrix<T>& cOther, CError* error) {
	error->setError(NO_ERROR);
	if (irow != 1 || cOther.irow != 1 || icolumn != cOther.icolumn) {
		error->setError(INVALID_DIMENSION);
		return NULL;
	}

	T product = 0;
	for (int i = 0; i < icolumn; i++) {
		product += pcMatrix[0][i] * cOther.pcMatrix[0][i];
	}	
	return product;
}

template <typename T>
bool CMatrix<T>::bIdentityMatrix() {
	if (irow != icolumn) return false;
	for (int i = 0; i < irow; i++) {
		for(int j = 0; j < icolumn; j++){
			if (i != j) pcMatrix[i][j] = 0;
			else pcMatrix[i][j] = 1;
		}
	}
	return true;
}

template <typename T>
bool CMatrix<T>::bInvert() {
	if (irow != icolumn) return false;

	double ratio = 0;
	int column = 2 * icolumn;
	T** matrix = new T* [irow];
	for (int i = 0; i < irow; i++) {
		matrix[i] = new T[column];
	}

	for (int i = 0; i < irow; i++) {
		for (int j = 0; j < icolumn; j++) {
			matrix[i][j] = pcMatrix[i][j];
			if (i == j) matrix[i][j + irow] = 1;
			else matrix[i][j + irow] = 0;
		}
	}

	for (int i = 0; i < irow; i++) {
		if(matrix[i][i] == 0) return false;
		for (int j = 0; j < icolumn; j++) {
			if (i != j) {
				ratio = matrix[j][i] / matrix[i][i];
				for (int k = 0; k < column; k++) {
					matrix[j][k] = matrix[j][k] - ratio * matrix[i][k];
				}
			}
		}
	}
	
	for (int i = 0; i < irow; i++) {
		for (int j = irow; j < column; j++) {
			matrix[i][j] = matrix[i][j] / matrix[i][i];
		}
	}
	
	for (int i = 0; i < irow; i++) {
		for (int j = 0; j < icolumn; j++) {
			pcMatrix[i][j] = matrix[i][j + irow];
		}
		delete[] matrix[i];
	}
	delete[] matrix;
	return true;
}
	template <typename T>			
	bool CMatrix<T> ::bNotNumber(string value) {
		for (char i : value) {
			if (((int)i < 48 || (int)i > 57) && (int)i != 44 && (int)i != 46) return true;
		}
		return false;
	}

	template <typename T>
	bool CMatrix<T>::bReadFile(string fName, CError * error) {
		error->setError(NO_ERROR);
		vector<int> newRow;
		ifstream file;
		stringstream sStream;
		string matrixRow;
		T found;

		file.open(fName);
		if (!file.good()) {
			error->setError(INVALID_FILE);
			return false;
		}

		string row;
		while (getline(file, row)) {
			sStream << row;

			int numberOfRows = 0;
			while (!sStream.eof()) {
				sStream >> matrixRow;
				numberOfRows++;
				matrixRow = "";
			}
			newRow.push_back(numberOfRows);
			sStream.clear();
		}
		file.close();

		int newColumn = 0;
		for (int x : newRow) {
			if (newColumn < x) newColumn = x;
		}

		for (int i = 0; i < irow; i++) {
			delete[] pcMatrix[i];
		}
		delete[] pcMatrix;
		irow = newRow.size();
		icolumn = newColumn;
		pcMatrix = new T * [irow];
		for (int i = 0; i < irow; i++)
			pcMatrix[i] = new T[icolumn];

		file.open(fName);
		int actualRow = 0;
		while (getline(file, row)) {
			sStream << row;

			for (int i = 0; i < icolumn; i++) {
				if (!sStream.eof()) {
					sStream >> matrixRow;
					if (!bNotNumber(matrixRow)) {
						stringstream(matrixRow) >> found;
						pcMatrix[actualRow][i] = found;
					}
					else {
						pcMatrix[actualRow][i] = (T)DEFAULT_VALUE;
						matrixRow = "";
					}
				}
				else {
					pcMatrix[actualRow][i] = (T)DEFAULT_VALUE;
				}
			}
			actualRow++;
			sStream.clear();
		}
		file.close();
		return true;
	}

	//operatory/////////////////////////////////
	template <typename T>
	void CMatrix<T>::operator=(CMatrix<T> && cOther) {
		if (this != &cOther) {
			irow = cOther.irow;
			icolumn = cOther.icolumn;
			cOther.irow = 0;
			cOther.icolumn = 0;
			pcMatrix = cOther.pcMatrix;
			cOther.pcMatrix = nullptr;
		}
	}

	template <typename T>
	CMatrix<T> CMatrix<T>::operator+(const CMatrix<T> & cOther) {
		CError error;
		CMatrix<T> cNew = add(cOther, &error);
		error.check();
		return move(cNew);
	}

	template <typename T>
	CMatrix<T> CMatrix<T>::operator-(const CMatrix<T> & cOther) {
		CError error;
		CMatrix<T> cNew = subtract(cOther, &error);
		error.check();
		return move(cNew);
	}

	template <typename T>
	CMatrix<T> CMatrix<T>::operator*(T number) {
		return move(this->multiply(number));
	}

	template <typename T>
	CMatrix<T> CMatrix<T>::operator*(const CMatrix<T> & cOther) {
		CError error;
		CMatrix<T> cNew = multiply(cOther, &error);
		error.check();
		return move(cNew);
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
				cout << pcMatrix[i][j] << " ";
			}
		}
	}
