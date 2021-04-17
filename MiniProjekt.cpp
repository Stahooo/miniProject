#include <iostream>
#include "CMatrix.h"

void test() {
    CError error;
    CMatrix<int> matrix(2, 4, &error);
    CMatrix<int> matrix2(2, 4, &error);
    matrix.fillMatrix();
    matrix2.fillMatrix();
    cout << "matrix ";
    matrix.show();
    matrix = (matrix2 + matrix2) * (-1);
    cout << endl << "(matrix + matrix) * (-1)";
    matrix.show();
    cout << endl << "wektor z kolumny ";
    matrix2 = matrix.vectorFromColumn(0, &error);
    matrix2.show();
    cout << endl << "mnozenie skalarne";
    cout << endl << matrix2.scalarProduct(matrix2, &error);
    matrix = matrix * matrix.transpose();
    cout << endl << "matrix * matrix.transpose()";
    matrix.show();
    cout << endl << "macierz jednostkowa";
    matrix.newMatrix(4, 4, &error);
    matrix.bIdentityMatrix();
    matrix.show();
}

void test2() {
    CError error;
    CMatrix<double> matrix2(3, 3, &error);
    matrix2.fillMatrix();
    matrix2.bSetValue(1, 1, 10);
    matrix2.show();
    matrix2.bInvert();
    
    cout << endl << "macierz odwrotna";
    matrix2.show();
    cout << endl << "wczytywanie z pliku ";
    matrix2.bReadFile("double.txt", &error);
    matrix2.show();
}
int main()
{
    CError error;
    CMatrix<double> matrix2(3, 3, &error);
    CMatrix<double> matrix(4, 6, &error);
    matrix = matrix2 + matrix;
}
/*CMatrix<int> matrix2(2, 4, &error);
    matrix2.breadFile("double.txt", &error);
    error.check();
    matrix2.show();
    CError error;
    CMatrix<int> matrix(2, 5, &error);
    matrix.fillMatrix();
    matrix.show();
    CMatrix<int> matrix2 = std::move(matrix);
    matrix2.show();
    matrix.fillMatrix();
    matrix.show();
    cout << "ooooooo" << endl;;
    matrix2 = matrix2 + matrix2 + matrix2;
    matrix2.show();
    cout << endl << "transpose" << endl;
    matrix2 = matrix2.transpose();
    matrix2.show();
    cout << endl << "transpose" << endl;
    
    cout << endl << "transpose" << endl;
    
    // matrix2.show();
    // matrix2 = matrix2 - matrix2;
    matrix2.show();
    CMatrix<int> matrix3 = matrix2.vectorFromRow(1);
    CMatrix<int> matrix4 = matrix2.vectorFromColumn(1);
    matrix3.show();
    matrix4.show();
    cout << endl<< matrix3.scalarProduct(matrix3);
    (matrix2 * matrix2.transpose()).show();
 */


