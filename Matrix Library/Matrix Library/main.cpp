#include<iostream>
#include "Matrix.h"
using namespace std;




int main()
{
	//Matrix<int> a;
	
	Matrix <float> matrix1(3);

	// displaying the matrix on console [try-catch controls boundary exception]
	cout << "\nDisplaying the matrix on console\n";
	try { matrix1.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }
	
	// Filling the matrix from user defined values
	matrix1.takeMatrixFromUser();
	cout << "\nDisplaying filled matrix\n";
	try { matrix1.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }

	// Separating row of a matrix
	std::vector <float> row;
	row = matrix1.getRow(1); // get row 1 of matrix1
	cout << "\n\n Required row 1 is : ";
	display_vector(row);

	// Separating column of a matrix
	std::vector <float> column;
	column = matrix1.getColumn(1); // get row 1 of matrix1
	cout << "\n\n Requiredcolumn 1 is : ";
	display_vector(column);

	// Calculating transpose of a matrix
	Matrix <float> transposeMatrix(3, 3); // matrix row,col will update w.r.t matrix1
	transposeMatrix = matrix1.getTranspose();
	cout<<"\n\nCalculated transpose of a matrix is\n";
	try { transposeMatrix.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }

	// Calculating Minor of a square matrix
	Matrix <float> minorMatrix(3); // matrix order will update w.r.t called matrix
	try { minorMatrix = matrix1.getMinor(0, 1); } // minor of row=1, column=1
	catch (const char* msg) { cout << msg << endl; }
	cout << "\n\nCalculated Minor of a square matrix is\n";
	try { minorMatrix.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }

	// Calculating determinant of a square matrix
	cout<<"Calculated determinant of a square matrix is : "<< matrix1.calculateDeterminant(); // minor of row=1, column=1


	// Calculating inverse of a  square matrix
	Matrix <float> invertedMatrix(3);
	try { invertedMatrix = matrix1.getInverted(); }
	catch (const char* msg) { cout << msg << endl; }
	cout << "\n\nCalculated inverse of a square matrix is\n";
	try { invertedMatrix.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }


	// multiplecation of matries
	Matrix <float> matrix_A(2, 3);
	Matrix <float> matrix_B(3, 4);
	cout << "\n\nEnter matrix A \n";
	matrix_A.takeMatrixFromUser();
	cout << "\n\nEnter matrix B \n";
	matrix_B.takeMatrixFromUser();

	Matrix <float> matrix_multi(2, 4);
	matrix_multi = matrix_A * matrix_B;
	cout << "\n\n multiplicated matrix is \n";
	matrix_multi.displayMatrix();



	/*
	// checking square matrix
	Matrix <int> matrix2(3);
	try { matrix2.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }

	// checking copy constructor
	Matrix<int> matrix3 = matrix1;
	try { matrix3.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }

	// checking copy operator
	Matrix<int> matrix4(3,4);
	matrix4 = matrix1;
	try { matrix4.displayMatrix(); }
	catch (const char* msg) { cout << msg << endl; }
	*/
	
	
	return 0;
}