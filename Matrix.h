/*
 * Matrix.h
 *
 *  Created on: 
 *      Author: 
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include <iostream>

using namespace std;

class Matrix {
protected:
	// These are the only member variables allowed!
	int noOfRows;
	int noOfColumns;
	double *data;

    // Add for code reuse. However, it would be useful for as a public class function.
    void fill(double data);
    int GetIndex (const int rowIdx, const int columnIdx) const;

public:
	Matrix (const int noOfRows, const int noOfCols);
	Matrix (const Matrix& input);
    Matrix& operator* (const Matrix& rhs) const;
    Matrix & operator*=(const Matrix & rhs);
	Matrix& operator= (const Matrix& rhs);
	~Matrix ();

    Matrix& ExchangeColumns(const int col1, const int col2, const int row1, const int row2);
    Matrix& ExchangeColumns(const int col1, const int col2);
    Matrix& ExchangeRows(const int row1, const int row2, const int col1, const int col2);
    Matrix& ExchangeRows(const int row1, const int row2);
    double GetEntry(const int rowIdx, const int columnIdx) const;
    int GetNoOfColumns() const;
    int GetNoOfRows() const;
    void Ones();
    void Transpose();
    void Zeros();

    static Matrix& Ones(const int nOfRows, const int nOfCols);
    static void Print(const double* data, const int nOfRows, const int nOfCols);
    static Matrix& Toeplitz(const double* column, const int noOfRows,
                            const double* row, const int noOfColumns);
    static Matrix& Transpose(const Matrix& matrix);
    static Matrix& Zeros(const int nOfRows, const int nOfCols);
    
    friend ostream& operator<<(ostream& os, const Matrix& m);
};

#endif /* MATRIX_H_ */
