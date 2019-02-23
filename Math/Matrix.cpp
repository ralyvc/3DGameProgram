#include "Matrix.h"
#include <cmath>

template <typename Type, size_t M, size_t N>
template <size_t P>
Matrix<Type, M, P> Matrix<Type, M, N>::operator*(const Matrix<Type, N, P> &other) const
{
    Matrix<Type, M, P> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t k = 0; k < P; k++)
        {
            for (size_t j = 0; j < N; j++)
            {
                res(i, k) += (*this)(i, j) * other(j, k);
            }
        }
    }
    return res;
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::operator+(const Matrix<Type, M, N> &other) const
{
    Matrix<Type, M, N> res;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) + other(i, j);
        }
    }
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::operator-(const Matrix<Type, M, N> &other) const
{
    Matrix<Type, M, N> res;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) - other(i, j);
        }
    }
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::operator-() const
{
    Matrix<Type, M, N> res;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = -(*this)(i, j);
        }
    }
}

template <typename Type, size_t M, size_t N>
void Matrix<Type, M, N>::operator+=(const Matrix<Type, M, N> &other)
{
    *this = *this + other;
}

template <typename Type, size_t M, size_t N>
void Matrix<Type, M, N>::operator-=(const Matrix<Type, M, N> &other)
{
    *this = *this - other;
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::operator+(Type scalar) const
{
    Matrix<Type, M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) + scalar;
        }
    }
    return res;
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::operator-(Type scalar) const
{
    Matrix<Type, M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) - scalar;
        }
    }
    return res;
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::operator*(Type scalar) const
{
    Matrix<Type, M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) * scalar;
        }
    }
    return res;
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::operator/(Type scalar) const
{
    Matrix<Type, M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) / scalar;
        }
    }
    return res;
}

template <typename Type, size_t M, size_t N>
void Matrix<Type, M, N>::operator+=(Type scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) + scalar;
        }
    }
}

template <typename Type, size_t M, size_t N>
void Matrix<Type, M, N>::operator-=(Type scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) - scalar;
        }
    }
}

template <typename Type, size_t M, size_t N>
void Matrix<Type, M, N>::operator*=(Type scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) * scalar;
        }
    }
}

template <typename Type, size_t M, size_t N>
void Matrix<Type, M, N>::operator/=(Type scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) / scalar;
        }
    }
}

template <typename Type, size_t M, size_t N>
Matrix<Type, M, N> Matrix<Type, M, N>::Transpose() const
{
    Matrix<Type, N, M> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = *this(j, i);
        }
    }
    return res;
}

/**

 * inverse based on LU factorization with partial pivotting

 */

template <typename Type, size_t M>
bool SquareMatrix<Type, M>::inv(SquareMatrix<Type, M> &inv) const

{
    SquareMatrix<Type, M> L;
    L.Identity();
    SquareMatrix<Type, M> U = *this;
    SquareMatrix<Type, M> P;
    P.Identity();
    for (size_t n = 0; n < M; n++)
    {
        // if diagonal is zero, swap with row below
        if (fabs(static_cast<float>(U(n, n))) < 1e-8f)
        {
            //printf("trying pivot for row %d\n",n);
            for (size_t i = n + 1; i < M; i++)
            {
                if (fabs(static_cast<float>(U(i, n))) > 1e-8f)
                {
                    U.SwapRows(i, n);
                    P.SwapRows(i, n);
                    L.SwapRows(i, n);
                    L.SwapCols(i, n);
                    break;
                }
            }
        }
        if (fabs(static_cast<float>(U(n, n))) < 1e-8f)
        {
            return false;
        }
        for (size_t i = (n + 1); i < M; i++)
        {
            L(i, n) = U(i, n) / U(n, n);
            for (size_t k = n; k < M; k++)
            {
                U(i, k) -= L(i, n) * U(n, k);
            }
        }
    }
    for (size_t c = 0; c < M; c++)
    {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                P(i, c) -= L(i, j) * P(j, c);
            }
        }
    }
    for (size_t c = 0; c < M; c++)
    {
        for (size_t k = 0; k < M; k++)
        {
            size_t i = M - 1 - k;
            for (size_t j = i + 1; j < M; j++)
            {
                P(i, c) -= U(i, j) * P(j, c);
            }
            P(i, c) /= U(i, i);
        }
    }
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            if (!is_finite(P(i, j)))
            {
                return false;
            }
        }
    }
    inv = P;
    return true;
}
