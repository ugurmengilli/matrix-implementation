#include "SquareMatrix.h"
#include "math.h"


SquareMatrix::SquareMatrix(const int dimension):
    Matrix(dimension, dimension)
{
}

SquareMatrix::SquareMatrix(const int dimension, double* data) :
    Matrix(dimension, dimension, data)
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

void SquareMatrix::LU(SquareMatrix& lmatrix, SquareMatrix& umatrix) const
{
    // Apply the steps given in the Algorithm 2.1
    umatrix = *this;
    lmatrix = SquareMatrix::Identity(noOfColumns);

    for (int k = 0; k < noOfColumns - 1; k++) {
        for (int j = k + 1; j < noOfColumns; j++) {
            lmatrix.data[GetIndex(j, k)] =
                umatrix.data[GetIndex(j, k)] / umatrix.data[GetIndex(k, k)];
            for (int m = k; m < noOfColumns; m++) {
                umatrix.data[GetIndex(j, m)] -=
                    lmatrix.data[GetIndex(j, k)] * umatrix.data[GetIndex(k, m)];
            }
        }
    }
}

void SquareMatrix::LU(SquareMatrix& lmatrix, SquareMatrix& umatrix, SquareMatrix& pivot) const
{
    // Apply the steps given in the Algorithm 2.2
    umatrix = *this;
    lmatrix = SquareMatrix::Identity(noOfColumns);
    pivot   = SquareMatrix::Identity(noOfColumns);

    for (int k = 0; k < noOfColumns - 1; k++) {
        // Find row that has the absolute greatest element in kth column of U
        double max = 0;
        int index = 0;
        for (int i = k; i < noOfRows; i++) {
            if (max < abs(umatrix.GetEntry(i, k))) {
                max = umatrix.GetEntry(i, k);   // Update max if it is less than current entry.
                index = i;  // Keep the index since i will iterate until the end of kth row.
            }
        }
        if (k != index) {
            umatrix.ExchangeRows(k, index, k, noOfColumns - 1);
            lmatrix.ExchangeRows(k, index, 0, k - 1);
            pivot.ExchangeRows(k, index);
        }
        for (int j = k + 1; j < noOfColumns; j++) {
            lmatrix.data[GetIndex(j, k)] =
                umatrix.data[GetIndex(j, k)] / umatrix.data[GetIndex(k, k)];
            for (int m = k; m < noOfColumns; m++) {
                umatrix.data[GetIndex(j, m)] -=
                    lmatrix.data[GetIndex(j, k)] * umatrix.data[GetIndex(k, m)];
            }
        }
    }
}

Matrix& SquareMatrix::Solve(const Matrix& B) const
{
    // Ensure the dimensions of the B matrix
    if (B.GetNoOfRows() != noOfRows || B.GetNoOfColumns() != 1)
        throw exception();

    // First decompose the A matrix
    SquareMatrix U(noOfColumns), L(noOfColumns), P(noOfColumns);
    LU(L, U, P);

    // Solve the new problem LUx = Pb. First solve Ly = Pb and then Ux = y.
    // Algorithm 3.1 gives the solution of Ly = Pb.
    Matrix Pb(P * B);
    double *y = new double[noOfRows];   // Column matrix

    y[0] = Pb.GetEntry(0, 0) / L.GetEntry(0, 0);
    for (int k = 1; k < noOfRows; k++) {
        y[k] = Pb.GetEntry(k, 0);

        for (int i = 0; i < k; i++)
            y[k] -= L.GetEntry(k, i) * y[i];
        
        y[k] /= L.GetEntry(k, k);
    }

    // Algorithm 3.2 gives the solution of Ux = y
    double *x = new double[noOfRows];   // Column matrix

    x[noOfRows - 1] = y[noOfRows - 1] / U.GetEntry(noOfRows - 1, noOfRows - 1);
    for (int k = noOfRows - 2; k >= 0; k--) {
        x[k] = y[k];

        for (int i = 1; i < noOfRows; i++)
            x[k] -= U.GetEntry(k, k + i) * x[k + i];

        x[k] /= U.GetEntry(k, k);
    }
    return *(new Matrix(noOfRows, 1, x));
}

SquareMatrix& SquareMatrix::TriL() const
{
    SquareMatrix* result(new SquareMatrix(noOfColumns));

    // Copy the upper triangle with the diagonal.
    for (int i = 0; i < noOfColumns; i++) {
        for (int j = i; j < noOfRows; j++)
            result->data[GetIndex(j, i)] = this->GetEntry(j, i);
    }
    return *result;
}

SquareMatrix& SquareMatrix::TriU() const
{
    SquareMatrix* result(new SquareMatrix(noOfColumns));

    // Copy the upper triangle with the diagonal.
    for (int i = 0; i < noOfColumns; i++) {
        for (int j = 0; j <= i; j++)
            result->data[GetIndex(j, i)] = this->GetEntry(j, i);
    }
    return *result;
}

SquareMatrix& SquareMatrix::Identity(const int dimension)
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
