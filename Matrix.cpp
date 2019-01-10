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
    // Fill the matrix with zeros
    fill(0);
}

Matrix::Matrix(const Matrix& input) :
    noOfRows(input.noOfRows),
    noOfColumns(input.noOfColumns),
    data(NULL)
{
    // Deep copy the data array
    size_t noOfElements = noOfColumns * noOfRows;
    this->data = new double[noOfElements];

    for (size_t i = 0; i < noOfElements; i++)
        this->data[i] = input.data[i];
}

Matrix::~Matrix()
{
    delete this->data;
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
    this->noOfRows = rhs.noOfRows;
    this->noOfColumns = rhs.noOfColumns;
    
    // Deep copy the data array
    delete this->data;

    size_t noOfElements = noOfColumns * noOfRows;
    this->data = new double[noOfElements];

    for (size_t i = 0; i < noOfElements; i++)
        this->data[i] = rhs.data[i];

    return *this;
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

// Protected members
void Matrix::fill(double data)
{
    // Set the size dynamically and initialize all elements with zeros
    size_t noOfElements = noOfColumns * noOfRows;
    if (this->data)
        delete this->data;

    this->data = new double[noOfElements];

    for (size_t i = 0; i < noOfElements; i++)
        this->data[i] = data;
}

// Static members
Matrix& Matrix::Ones(const int nOfRows, const int nOfCols)
{
    Matrix *m = new Matrix(nOfRows, nOfCols);
    m->fill(1);
    return *m;
}

void Matrix::Print(const double* data, const int nOfRows, const int nOfCols)
{
    Matrix m(nOfRows, nOfCols);
    // Hack around const assignment to non-const pointer. This is still safe in this function since
    // we don't change the data but only print it.
    delete m.data;
    m.data = const_cast<double*>(data);
    // Use operator<< to print the custom data
    cout << m;
    // Release the data since the destructor will try to delete it upon returning this function,
    // which is not possible for the const double* type. So assign a null pointer to the m.data
    // and let the destructor safely delete it instead. The const double* data will be handled
    // in its own scope.
    m.data = NULL;
}

Matrix& Matrix::Toeplitz(const double* column, const int noOfRows, const double* row, const int noOfColumns)
{
    Matrix *toeplitz(new Matrix(noOfRows, noOfColumns));
    // Construct Toeplizt matrix:
    delete toeplitz->data;
    size_t noOfElements = noOfColumns * noOfRows;
    toeplitz->data = new double[noOfElements];

    for (int i = 0; i < noOfColumns; i++) {
        for (int j = 0; j < noOfRows; j++) {
            if ((j - i) >= 0)
                toeplitz->data[i * noOfRows + j] = column[j - i];
            else
                toeplitz->data[i * noOfRows + j] = row[i - j];
        }
    }
    return *toeplitz;
}

Matrix& Matrix::Zeros(const int nOfRows, const int nOfCols)
{
    return *(new Matrix(nOfRows, nOfCols));
}