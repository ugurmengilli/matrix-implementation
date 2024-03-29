/*
 * MatrixTest.cpp
 *
 *      Author: Gary Hui Zhang (gary.zhang@ucl.ac.uk)
 */

#include "Matrix.h"
#include "SquareMatrix.h"
#include <cstdlib>

using namespace std;

void ConstructorsTesting () {
	cout << "Testing the Matrix constructors:" << endl;

	cout << "Case 1.1: Creating a 2x4 matrix of zeros with the standard constructor:" << endl;
    {
        Matrix matrix(2, 4);
        cout << matrix << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
    cout << "Case 1.2: Creating a 4x4 square matrix of zeros with the standard constructor:" << endl;
    {
        SquareMatrix sqmatrix(4);
        cout << sqmatrix << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
    
	cout << "Case 2.1: Creating a 2x4 matrix of zeros with the static Zeros:" << endl;
	{
		Matrix matrix = Matrix::Zeros(2, 4);
		cout << matrix << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    cout << "Case 2.2: Creating a 4x4 matrix of zeros with the static Zeros:" << endl;
    {
        SquareMatrix sqmatrix = SquareMatrix::Zeros(4);
        cout << sqmatrix << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }

	cout << "Case 3.1: Creating a 2x4 matrix of ones with the static Ones:" << endl;
	{
		Matrix matrix = Matrix::Ones(2, 4);
		cout << matrix << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    cout << "Case 3.2: Creating a 4x4 matrix of ones with the static Ones:" << endl;
    {
        SquareMatrix sqmatrix = SquareMatrix::Ones(4);
        cout << sqmatrix << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
    cout << "Case 3.3: Creating a 4x4 identity matrix of ones with the static Identity:" << endl;
    {
        SquareMatrix eye = SquareMatrix::Identity(4);
        cout << eye << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
    
	cout << "Case 4.1: Copying a 2x4 matrix of ones with the copy constructor:" << endl;
	{
		Matrix matrix = Matrix::Ones(2, 4);
		cout << "The input matrix = " << endl;
		cout << matrix << endl;
		Matrix copy = matrix;
		cout << "The copy = " << endl;
		cout << copy << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    cout << "Case 4.2: Copying a 4x4 matrix of ones with the copy constructor:" << endl;
    {
        SquareMatrix matrix = SquareMatrix::Identity(4);
        cout << "The input matrix = " << endl;
        cout << matrix << endl;
        SquareMatrix copy = matrix;
        cout << "The copy = " << endl;
        cout << copy << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
}

void AssignmentTesting () {
	cout << "Testing the assignment operator:" << endl;
	cout << endl;
    cout << "The input matrix = " << endl;
    Matrix matrix = Matrix::Ones(2, 4);
    cout << matrix << endl;

    cout << "The copy = " << endl;
    Matrix copy = matrix;   // Copy constructor
    cout << copy << endl;
    cout << "Assigning a 3x3 zero matrix to the copy:" << endl;
    copy = Matrix::Zeros(3, 3);     // Assignment operation. Performs deep copy
    cout << copy << endl;
    cout << "Check input matrix for changes:" << endl;
    cout << matrix << endl;  // Therefore, any change to the copy does not affect original matrix.
}

void ToeplitzTestingHelper (const double *column, const int noOfRows, const double *row, const int noOfColumns, const double *expected) {
    if (noOfColumns != noOfRows)
    {
        cout << "Matrix class:" << endl;
        cout << "The 1st column = " << endl;
        Matrix::Print(column, noOfRows, 1);
        cout << endl;
        cout << "The 1st row = " << endl;
        Matrix::Print(row, 1, noOfColumns);
        cout << endl;
        cout << "The matrix created by the toeplitz function in MATLAB = " << endl;
        Matrix::Print(expected, noOfRows, noOfColumns);
        cout << endl;
        Matrix toeplitz = Matrix::Toeplitz(column, noOfRows, row, noOfColumns);
        cout << "The matrix created by Matrix::Toeplitz = " << endl;
        cout << toeplitz << endl;
    }
    else if (noOfRows == noOfColumns)
    {
        cout << "Square Matrix class:" << endl;
        cout << "The 1st column = " << endl;
        SquareMatrix::Print(column, noOfRows, 1);
        cout << endl;
        cout << "The 1st row = " << endl;
        SquareMatrix::Print(row, 1, noOfColumns);
        cout << endl;
        cout << "The matrix created by the toeplitz function in MATLAB = " << endl;
        SquareMatrix::Print(expected, noOfRows, noOfColumns);
        cout << endl;
        SquareMatrix toeplitz = SquareMatrix::Toeplitz(column, row, noOfColumns);
        cout << "The matrix created by Matrix::Toeplitz = " << endl;
        cout << toeplitz << endl;
    }
}

void ToeplitzTesting () {
	cout << "Testing the static function Matrix::Toeplitz:" << endl;

	cout << "Case 1: When the number of columns is larger than the number of rows" << endl;
	{
		double column[4] = {2, 1, 0, -1};
		double row[3] = {2, 0, -1};
		// matrix should be stored, in 1-D, column-wise
		//  2     0    -1
		//  1     2     0
		//  0     1     2
		// -1     0     1
		double expected[12] = {2, 1, 0, -1, 0, 2, 1, 0, -1, 0, 2, 1};
		ToeplitzTestingHelper(column, 4, row, 3, expected);
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}

	cout << "Case 2: When the number of columns is less than the number of rows" << endl;
	{
		double column[3] = {2, 0, -1};
		double row[4] = {2, 1, 0, -1};
		// matrix should be stored, in 1-D, column-wise
		//  2     1     0    -1
		//  0     2     1     0
		// -1     0     2     1
		double expected[12] = {2, 0, -1, 1, 2, 0, 0, 1, 2, -1, 0, 1};
		ToeplitzTestingHelper(column, 3, row, 4, expected);
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}

	cout << "Case 3: When the 1st entries of the 1st column and row are different:" << endl;
	{
		double column[4] = {2, 1, 0, -1};
		double row[3] = {1, 0, -1};
		// matrix should be stored, in 1-D, column-wise
		//  2     0    -1
		//  1     2     0
		//  0     1     2
		// -1     0     1
		double expected[12] = {2, 1, 0, -1, 0, 2, 1, 0, -1, 0, 2, 1};
		ToeplitzTestingHelper(column, 4, row, 3, expected);
	}

    cout << "Case 4: When the number of columns is equal to the number of rows" << endl;
    {
        double column[4] = { 1, 2, 3, 4 };
        double row[4] = { 4, 3, 2, 1 };
        cout << "With two vectors:" << endl;
        double expected1[16] = { 1, 2, 3, 4, 3, 1, 2, 3, 2, 3, 1, 2, 1, 2, 3, 1 };
        ToeplitzTestingHelper(column, 4, row, 4, expected1);

        cout << "With one vector:" << endl;
        double expected2[16] = { 4, 3, 2, 1, 3, 4, 3, 2, 2, 3, 4, 3, 1, 2, 3, 4 };
        ToeplitzTestingHelper(row, 4, row, 4, expected2);
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
}

void TransposeTesting () {
	cout << "Testing the Transpose functions:" << endl;

	cout << "Case 1.1: the static Transpose function" << endl;
	{
        // the same matrix as in ToeplitzTesting
        double column[4] = { 2, 1, 0, -1 };
        double row[3] = { 2, 0, -1 };
        Matrix matrix = Matrix::Toeplitz(column, 3, row, 4);
		cout << "The original Matrix = " << endl;
		cout << matrix << endl;
		Matrix transpose = Matrix::Transpose(matrix);
		cout << "The transposed version = " << endl;
		cout << transpose << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    cout << "Case 1.2: the static Square Transpose function" << endl;
    {
        double column[4] = { 1, 2, 3, 4 };
        double row[4] = { 4, 3, 2, 1 };
        SquareMatrix matrix = SquareMatrix::Toeplitz(column, row, 4);
        cout << "The original Matrix = " << endl;
        cout << matrix << endl;
        SquareMatrix transpose = SquareMatrix::Transpose(matrix);
        cout << "The transposed version = " << endl;
        cout << transpose << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
    
	cout << "Case 2.1: the non-static Transpose function" << endl;
	{
		// the same matrix as in ToeplitzTesting
		double column[4] = {2, 1, 0, -1};
		double row[3] = {2, 0, -1};
		Matrix matrix = Matrix::Toeplitz(column, 4, row, 3);
		cout << "The original Matrix = " << endl;
		cout << matrix << endl;
		matrix.Transpose();
		cout << "The transposed version = " << endl;
		cout << matrix << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    cout << "Case 2.2: the non-static Square Transpose function" << endl;
    {
        // the same matrix as in ToeplitzTesting
        double column[4] = { 1, 2, 3, 4 };
        double row[4] = { 4, 3, 2, 1 };
        SquareMatrix matrix = SquareMatrix::Toeplitz(column, row, 4);
        cout << "The original Matrix = " << endl;
        cout << matrix << endl;
        matrix.Transpose();
        cout << "The transposed version = " << endl;
        cout << matrix << endl;
        cout << "Press any key to continue ..." << flush;
        system("read");
        cout << endl;
    }
}

void MultiplicationTesting () {
	cout << "Testing the multiplication functions:" << endl;

	cout << "Case 1: the non-member multiplication function" << endl;
	{
		// the same matrix as in ToeplitzTesting
		double column[4] = {2, 1, 0, -1};
		double row[3] = {2, 0, -1};
		Matrix lhs = Matrix::Toeplitz(column, 4, row, 3);
		cout << "The L.H.S. Matrix = " << endl;
		cout << lhs << endl;
		Matrix rhs = Matrix::Transpose(lhs);
		cout << "The R.H.S. version = " << endl;
		cout << rhs << endl;
		cout << "The expected product = " << endl;
		//  5     2    -2    -3
		//  2     5     2    -1
		// -2     2     5     2
		// -3    -1     2     2
		double expected[16] = {5, 2, -2, -3, 2, 5, 2, -1, -2, 2, 5, 2, -3, -1, 2, 2};
		Matrix::Print(expected, 4, 4);
		cout << "The actual product = " << endl;
		cout << lhs * rhs << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    
	cout << "Case 2: the member multiplication function" << endl;
	{
		// the same matrix as in ToeplitzTesting
		double column[4] = {2, 1, 0, -1};
		double row[3] = {2, 0, -1};
		Matrix lhs = Matrix::Toeplitz(column, 4, row, 3);
		cout << "The L.H.S. Matrix = " << endl;
		cout << lhs << endl;
		Matrix rhs = Matrix::Transpose(lhs);
		cout << "The R.H.S. version = " << endl;
		cout << rhs << endl;
		cout << "The expected product = " << endl;
		//  5     2    -2    -3
		//  2     5     2    -1
		// -2     2     5     2
		// -3    -1     2     2
		double expected[16] = {5, 2, -2, -3, 2, 5, 2, -1, -2, 2, 5, 2, -3, -1, 2, 2};
		Matrix::Print(expected, 4, 4);
		cout << "The actual product = " << endl;
		lhs *= rhs;
		cout << lhs << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}

}

void RowColumnExchangeTesting () {
	cout << "Testing the Row or Column Exchange functions:" << endl;

	cout << "Case 1: the row exchange function" << endl;
	{
		// the same matrix as in ToeplitzTesting
		double column[4] = {2, 1, 0, -1};
		double row[3] = {2, 0, -1};
		Matrix matrix = Matrix::Toeplitz(column, 4, row, 3);
		cout << "The original Matrix = " << endl;
		cout << matrix << endl;
		cout << "Exchange the 2nd and 4th rows gives" << endl;
		cout << matrix.ExchangeRows(1, 3) << endl;
		cout << "Exchange the 1st and 4th rows, but only from the 2nd to the 3rd columns, gives" << endl;
		cout << matrix.ExchangeRows(0, 3, 1, 2) << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    
	cout << "Case 2: the column exchange function" << endl;
	{
		// the same matrix as in ToeplitzTesting
		double column[4] = {2, 1, 0, -1};
		double row[3] = {2, 0, -1};
		Matrix matrix = Matrix::Toeplitz(column, 4, row, 3);
		cout << "The original Matrix = " << endl;
		cout << matrix << endl;
		cout << "Exchange the 1st and 2nd columns gives" << endl;
		cout << matrix.ExchangeColumns(0, 1) << endl;
		cout << "Exchange the 2nd and 3rd columns, but only from the 2nd to the 4th rows, gives" << endl;
		cout << matrix.ExchangeColumns(1, 2, 1, 3) << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
}

void OtherTesting () {
	cout << "Testing the miscellaneous functions:" << endl;

	cout << "The function that sets every entry to zero" << endl;
	{
		Matrix ones = Matrix::Ones(2, 4);
		cout << "The input matrix =" << endl;
		cout << ones << endl;
		ones.Zeros();
		cout << "After setting every entry to zero, we have" << endl;
		cout << ones << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    
	cout << "The function that sets every entry to one" << endl;
	{
		Matrix zeros = Matrix::Zeros(2, 4);
		cout << "The input matrix =" << endl;
		cout << zeros << endl;
		zeros.Ones();
		cout << "After setting every entry to one, we have" << endl;
		cout << zeros << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    
	cout << "Find out the number of rows and columns" << endl;
	{
		Matrix zeros = Matrix::Zeros(2, 4);
		cout << "The input matrix =" << endl;
		cout << zeros << endl;
		cout << "The number of rows = " << zeros.GetNoOfRows() << " ; ";
		cout << "the number of columns = " << zeros.GetNoOfColumns() << endl;
		cout << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
    
	cout << "Find out the value of a particular entry" << endl;
	{
		// the same matrix as in ToeplitzTesting
		double column[4] = {2, 1, 0, -1};
		double row[3] = {2, 0, -1};
		Matrix matrix = Matrix::Toeplitz(column, 4, row, 3);
		cout << "The original Matrix = " << endl;
		cout << matrix << endl;
		cout << "The entry at the 2nd row and the 3rd column is ";
		cout << matrix.GetEntry(1, 2) << endl;
		cout << "The entry at the 3rd row and the 2nd column is ";
		cout << matrix.GetEntry(2, 1) << endl;
		cout << endl;
		cout << "Press any key to continue ..." << flush;
		system("read");
		cout << endl;
	}
}

void OtherSquareTesting() {
    double row[4] = { 4, 3, 2, 1 };
    SquareMatrix input1 = SquareMatrix::Toeplitz(row, 4);

    cout << "Get upper triangle of a square matrix:" << endl;
    cout << "The input matrix = " << endl << input1 << endl;
    cout << "Upper triangle = " << endl << input1.TriU() << endl;

    cout << "Get lower triangle of a square matrix:" << endl;
    cout << "The input matrix = " << endl << input1 << endl;
    cout << "Lower triangle = " << endl << input1.TriL() << endl;

    cout << "LU decomposition of a square matrix without pivoting:" << endl;
    cout << "The input matrix = " << endl << input1 << endl;
    SquareMatrix lmatrix(4), umatrix(4);
    input1.LU(lmatrix, umatrix);
    cout << "Lower triangle = " << endl << lmatrix << endl;
    cout << "Upper triangle = " << endl << umatrix << endl;

    cout << "LU decomposition of a square matrix with pivoting:" << endl;
    cout << "The input matrix = " << endl << input1 << endl;
    SquareMatrix pivot(4);
    input1.LU(lmatrix, umatrix, pivot);
    cout << "Lower triangle = " << endl << lmatrix << endl;
    cout << "Upper triangle = " << endl << umatrix << endl;
    cout << "Pivot = " << endl << pivot << endl;

    cout << "LU decomposition of another square matrix with pivoting:" << endl;
    double column[4] = { 1, 2, 3, 4 };
    SquareMatrix input2 = SquareMatrix::Toeplitz(column, row, 4);
    cout << "The input matrix = " << endl << input2 << endl;
    input2.LU(lmatrix, umatrix, pivot);
    cout << "Lower triangle = " << endl << lmatrix << endl;
    cout << "Upper triangle = " << endl << umatrix << endl;
    cout << "Pivot = " << endl << pivot << endl;

    cout << "Solve the system of linear equations:" << endl;
    double system[16] = { 2, 4, 8, 6, 1, 3, 7, 7, 1, 3, 9, 9, 0, 1, 5, 8 };
    double bdata[4] = { 1, 0, 0, 0 };
    SquareMatrix A(4, system);
    Matrix b(4, 1, bdata);
    cout << "The system matrix A = " << endl << A << endl;
    cout << "The matrix b =" << endl << b << endl;
    cout << "The solution x = " << endl << A.Solve(b) << endl;

    cout << "LEAST SQUARES SOLUTION:" << endl;
    double system2[12] = { 2, 4, 8, 6, 1, 3, 7, 7, 0, 1, 5, 8 };
    Matrix Amn(4, 3, system2);
    cout << "The system matrix A = " << endl << Amn << endl;
    cout << "The matrix b =" << endl << b << endl;
    Matrix At = Matrix::Transpose(Amn);
    SquareMatrix Anew(At * Amn);
    Matrix bnew(At * b);
    cout << "The NEW system matrix A = " << endl << Anew << endl;
    cout << "The NEW matrix b =" << endl << bnew << endl;
    cout << "The solution x = " << endl << Anew.Solve(bnew) << endl;
}

int main () {

	for (;;) {
		cout << "Choose to test one of the following:" << endl;
		cout << "  Enter \'1\' for the constructors" << endl;
		cout << "  Enter \'2\' for the assignment operator" << endl;
		cout << "  Enter \'3\' for the Toeplitz function" << endl;
		cout << "  Enter \'4\' for the Transpose function" << endl;
		cout << "  Enter \'5\' for the multiplication" << endl;
		cout << "  Enter \'6\' for the Row or Column Exchange functions" << endl;
		cout << "  Enter \'7\' for the other functions" << endl;
        cout << "  Enter \'8\' for the other SquareMatrix functions" << endl;
        cout << ">> ";
		char choice;
		cin >> choice;

        switch (choice) {
			case '1':	ConstructorsTesting();
						break;
			case '2':	AssignmentTesting();
						break;
			case '3':	ToeplitzTesting();
						break;
			case '4':	TransposeTesting();
						break;
			case '5':	MultiplicationTesting();
						break;
			case '6':	RowColumnExchangeTesting();
						break;
			case '7':	OtherTesting();
						break;
            case '8':   OtherSquareTesting();
                        break;
            default:
                break;
		}
		cout << "Enter \'0\' to exit or \'1\' to choose another test" << endl;
		cout << ">> ";
		cin >> choice;
		if (choice == '0') {
			return 0;
		}
	}

}
