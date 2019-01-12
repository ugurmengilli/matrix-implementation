#ifndef SQUAREMATRIX_H_
#define SQUAREMATRIX_H_

#include "Matrix.h"
class SquareMatrix :
    public Matrix
{
public:
    SquareMatrix(const int dimension);
    SquareMatrix(const SquareMatrix& input);
    SquareMatrix(const Matrix& input);
    ~SquareMatrix();

    SquareMatrix& TriU() const;

    static SquareMatrix& Identity(const int dimension);
    static SquareMatrix& Ones(const int dimension);
    static SquareMatrix& Toeplitz(const double* column, const double* row, const int dimension);
    static SquareMatrix& Toeplitz(const double* vector, const int dimension);
    static SquareMatrix& Zeros(const int dimension);
};

#endif /* SQUAREMATRIX_H_ */
