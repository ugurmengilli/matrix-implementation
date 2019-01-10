/*
 * Matrix.cpp
 *
 *  Created on: 
 *      Author: 
 */

#include "Matrix.h"

using namespace std;

Matrix::Matrix(const int nOfRows, const int nOfCols) :
    noOfRows(nOfRows),
    noOfColumns(nOfCols),
    data(NULL)
 {
    // Set the size dynamically and initialize all elements with zeros
    size_t noOfElements = noOfColumns * noOfRows;
    data = new double[noOfElements];
    for (size_t i = 0; i < noOfElements; i++)
        data[i] = 0;
}

Matrix::Matrix(const Matrix& input)
{
}

Matrix::~Matrix()
{
    delete this->data;
}

Matrix& Matrix::operator=(const Matrix & rhs)
{
    // TODO: insert return statement here
}

ostream & operator<<(ostream& os, const Matrix& m)
{
    // Set display precision of the elements
    os.precision(4);
    // Print the column-major matrix in ordinary format
    for (size_t i = 0; i < m.noOfRows; i++) {
        for (size_t j = 0; j < m.noOfColumns; j++) {
            os << fixed << m.data[i + j * m.noOfRows] << '\t';
        }
        os << endl;
    }
    return os;
}

int Matrix::GetIndex(const int rowIdx, const int columnIdx) const
{
    return 0;
}
