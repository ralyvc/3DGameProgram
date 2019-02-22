#include "Matrix.h"

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

    
    for(size_t i = 0; i < M; i++)
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

    
    for(size_t i = 0; i < M; i++)
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

    
    for(size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = -(*this)(i, j) ;
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
    for(size_t i = 0; i < M; i++)
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
    for(size_t i = 0; i < M; i++)
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
    for(size_t i = 0; i < M; i++)
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
    for(size_t i = 0; i < M; i++)
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
    for(size_t i = 0; i < M; i++)
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
    for(size_t i = 0; i < M; i++)
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
    for(size_t i = 0; i < M; i++)
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
    for(size_t i = 0; i < M; i++)
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
    Matrix<Type, M, N> res;
    for(size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i,j) = *this(j, i);
        }
    }
    return res;
}