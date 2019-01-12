#include "SquareMatrix.h"



SquareMatrix::SquareMatrix(const int dimension):
    Matrix(dimension, dimension)
{
}

SquareMatrix::SquareMatrix(const SquareMatrix& input) :
    Matrix(input)
{

}

SquareMatrix::SquareMatrix(const Matrix& input) :
    Matrix(input)
{
    if (input.GetNoOfRows() != input.GetNoOfColumns())
        throw exception();
}

SquareMatrix::~SquareMatrix()
{
}

SquareMatrix & SquareMatrix::TriL() const
{
    SquareMatrix* result(new SquareMatrix(noOfColumns));

    // Copy the upper triangle with the diagonal.
    for (size_t i = 0; i < noOfColumns; i++) {
        for (size_t j = i; j < noOfRows; j++)
            result->data[result->GetIndex(j, i)] = this->GetEntry(j, i);
    }
    return *result;
}

SquareMatrix& SquareMatrix::TriU() const
{
    SquareMatrix* result(new SquareMatrix(noOfColumns));

    // Copy the upper triangle with the diagonal.
    for (size_t i = 0; i < noOfColumns; i++) {
        for (size_t j = 0; j <= i; j++)
            result->data[result->GetIndex(j, i)] = this->GetEntry(j, i);
    }
    return *result;
}

SquareMatrix & SquareMatrix::Identity(const int dimension)
{
    SquareMatrix *eye(new SquareMatrix(dimension));
    for (size_t i = 0; i < dimension; i++)
        eye->data[i * (dimension + 1)] = 1;

    return *eye;
}

SquareMatrix& SquareMatrix::Ones(const int dimension)
{
    return *(new SquareMatrix(Matrix::Ones(dimension, dimension)));
}

SquareMatrix& SquareMatrix::Toeplitz(const double* column, const double* row, const int dimension)
{
    Matrix m(Matrix::Toeplitz(column, dimension, row, dimension));
    SquareMatrix *sm(new SquareMatrix(m));
    return *sm;
}

SquareMatrix& SquareMatrix::Toeplitz(const double* vector, const int dimension)
{
    return SquareMatrix::Toeplitz(vector, vector, dimension);
}

SquareMatrix& SquareMatrix::Zeros(const int dimension)
{
    return *(new SquareMatrix(dimension));
}
