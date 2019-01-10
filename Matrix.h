/*
 * Matrix.h
 *
 *  Created on: 
 *      Author: 
 */

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
protected:
	// These are the only member variables allowed!
	int noOfRows;
	int noOfColumns;
	double *data;

	int GetIndex (const int rowIdx, const int columnIdx) const;

public:
	Matrix (const int noOfRows, const int noOfCols);
	Matrix (const Matrix& input);
	Matrix& operator= (const Matrix& rhs);
	~Matrix ();

};

#endif /* MATRIX_H_ */
