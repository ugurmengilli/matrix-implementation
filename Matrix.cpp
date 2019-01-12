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

Matrix& Matrix::operator*(const Matrix& rhs) const
{
    Matrix *result(new Matrix(noOfRows, rhs.noOfColumns));

    for (size_t i = 0; i < noOfRows; i++) {
        for (size_t j = 0; j < rhs.noOfColumns; j++) {
            for (size_t k = 0; k < rhs.noOfRows; k++) {
                result->data[j * result->noOfRows + i] +=
                    data[k * noOfRows + i] * rhs.data[j * rhs.noOfRows + k];
            }
        }
    }
    return *result;
}

Matrix& Matrix::operator*=(const Matrix& rhs)
{
    Matrix *result(new Matrix(*this * rhs));
    this->noOfColumns = result->noOfColumns;
    this->noOfRows = result->noOfRows;
    this->data = result->data;
    result->data = NULL;
    
    return *this;
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

ostream& operator<<(ostream& os, const Matrix& m)
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
    return rowIdx + columnIdx * noOfRows;
}

Matrix& Matrix::ExchangeColumns(const int col1, const int col2, const int row1, const int row2)
{
    for (size_t i = row1; i <= row2; i++)
        swap(data[GetIndex(i, col1)], data[GetIndex(i, col2)]);
    return *this;
}

Matrix& Matrix::ExchangeColumns(const int col1, const int col2)
{
    ExchangeColumns(col1, col2, 0, noOfRows - 1);
    return *this;
}

Matrix& Matrix::ExchangeRows(const int row1, const int row2, const int col1, const int col2)
{
    for (size_t i = col1; i <= col2; i++)
        swap(data[GetIndex(row1, i)], data[GetIndex(row2, i)]);
    return *this;
}

Matrix& Matrix::ExchangeRows(const int row1, const int row2)
{
    ExchangeRows(row1, row2, 0, noOfColumns - 1);
    return *this;
}

double Matrix::GetEntry(const int rowIdx, const int columnIdx) const
{
    return data[GetIndex(rowIdx, columnIdx)];
}

int Matrix::GetNoOfColumns() const
{
    return noOfColumns;
}

int Matrix::GetNoOfRows() const
{
    return noOfRows;
}

void Matrix::Ones()
{
    fill(1);
}

void Matrix::Transpose()
{
    Matrix *transpose(new Matrix(Matrix::Transpose(*this)));

    delete this->data;
    size_t noOfElements = noOfColumns * noOfRows;
    this->data = new double[noOfElements];

    this->noOfRows = transpose->noOfRows;
    this->noOfColumns = transpose->noOfColumns;
    this->data = transpose->data;
}

void Matrix::Zeros()
{
    fill(0);
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
    // Const assignment to non-const pointer. This is still safe in this function since
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

Matrix& Matrix::Transpose(const Matrix& matrix)
{
    size_t noOfColumns = matrix.noOfRows;
    size_t noOfRows = matrix.noOfColumns;
    Matrix *transpose(new Matrix(noOfRows, noOfColumns));

    delete transpose->data;
    size_t noOfElements = noOfColumns * noOfRows;
    transpose->data = new double[noOfElements];

    for (size_t i = 0; i < noOfColumns; i++) {
        for (size_t j = 0; j < noOfRows; j++) {
            transpose->data[i * noOfRows + j] = matrix.data[i + noOfColumns * j];
        }
    }
    return *transpose;
}

Matrix& Matrix::Zeros(const int nOfRows, const int nOfCols)
{
    return *(new Matrix(nOfRows, nOfCols));
}