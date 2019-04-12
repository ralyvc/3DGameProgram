#include "Matrix.h"
#include <cmath>
#include <cstdlib>
#include "MathUtil.h"
#include "EulerAngles.h"
#include "Quaternion.h"
template <size_t M, size_t N>
bool Matrix<M, N>::operator==(const Matrix<M, N> &other) const
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (fabs(*this(i, j) - other(i, j)) > kEpsilon)
            {
                return false;
            }
        }
    }

    return true;
}

template <size_t M, size_t N>
bool Matrix<M, N>::operator!=(const Matrix<M, N> &other) const
{
    return !(*this == other);
}

template <size_t M, size_t N>
template <size_t P>
Matrix<M, P> Matrix<M, N>::operator*(const Matrix<N, P> &other) const
{
    Matrix<M, P> res;
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

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(const Matrix<M, N> &other) const
{
    Matrix<M, N> res;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) + other(i, j);
        }
    }
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(const Matrix<M, N> &other) const
{
    Matrix<M, N> res;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) - other(i, j);
        }
    }
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-() const
{
    Matrix<M, N> res;

    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = -(*this)(i, j);
        }
    }
}

template <size_t M, size_t N>
void Matrix<M, N>::operator+=(const Matrix<M, N> &other)
{
    *this = *this + other;
}

template <size_t M, size_t N>
void Matrix<M, N>::operator-=(const Matrix<M, N> &other)
{
    *this = *this - other;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(float scalar) const
{
    Matrix<M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) + scalar;
        }
    }
    return res;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(float scalar) const
{
    Matrix<M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) - scalar;
        }
    }
    return res;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator*(float scalar) const
{
    Matrix<M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) * scalar;
        }
    }
    return res;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator/(float scalar) const
{
    Matrix<M, N> res;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            res(i, j) = (*this)(i, j) / scalar;
        }
    }
    return res;
}

template <size_t M, size_t N>
void Matrix<M, N>::operator+=(float scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) + scalar;
        }
    }
}

template <size_t M, size_t N>
void Matrix<M, N>::operator-=(float scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) - scalar;
        }
    }
}

template <size_t M, size_t N>
void Matrix<M, N>::operator*=(float scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) * scalar;
        }
    }
}

template <size_t M, size_t N>
void Matrix<M, N>::operator/=(float scalar)
{
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            *this(i, j) = (*this)(i, j) / scalar;
        }
    }
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::Transpose() const
{
    Matrix<N, M> res;
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

template <size_t M>
bool SquareMatrix<M>::inv(SquareMatrix<M> &inv) const
{
    SquareMatrix<M> L;
    L.Identity();
    SquareMatrix<M> U = *this;
    SquareMatrix<M> P;
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

template <size_t M>
float SquareMatrix<M>::Determinant() const
{

    int out;
    int i, j;
    double k, result = 1;
    SquareMatrix<M> a = *this;
    for (out = 0; out < M; out++)
    {
        for (i = out; i < M; i++)
        {
            if (EqualZero(a(i, out)))
                continue;
            else
                for (j = out; j < M; j++)
                {
                    k = a(i, j);
                    a(i, j) = a(out, j);
                    a(out, j) = k;
                }
            if (i == out)
                result *= a(out, out);
            else
                result *= -a(out, out);
            break;
        }
        if (i == M)
            return 0;
        if (!FloatEqual(a(out, out), 1))
            for (j = out + 1; j < M; j++)
                a(out, j) /= a(out, out);
        a(out, out) = 1;

        for (i = out + 1; i < M; i++)
            for (j = out + 1; j < M; j++)
                a(i, j) -= a(i, out) * a(out, j);
    }
    return result;
}

RotationMatrix::RotationMatrix(const EulerAngles& r)
{
    float ch = cos(r.heading);
    float cp = cos(r.pitch);
    float cb = cos(r.bank);
    float sh = sin(r.heading);
    float sp = sin(r.pitch);
    float sb = sin(r.bank);
    _data[0][0] = ch * cb + sh * sp * sb;
    _data[0][1] = sp * sb;
    _data[0][2] = -sh * cb + ch * sp * sb;
    _data[1][0] = -ch * cb + sh * sp * cb;
    _data[1][1] = cp * cb;
    _data[1][2] = sb * sh + ch * sp * cb;
    _data[2][0] = sh * cp;
    _data[2][1] = -sp;
    _data[2][2] = ch * cp;
}

RotationMatrix::RotationMatrix(const Quaternion& r)
{
    _data[0][0] = 1 - 2 * r.y * r.y - 2 * r.z * r.z;
    _data[0][1] = 2 * r.x * r.y + 2 * r.w * r.z;
    _data[0][2] = 2 * r.x * r.z - 2 * r.w * r.y;
    _data[1][0] = 2 * r.x * r.y - 2 * r.w * r.z;
    _data[1][1] = 1 - 2 * r.x * r.x - 2 * r.z * r.z;
    _data[1][2] = 2 * r.y * r.z + 2 * r.w * r.x;
    _data[2][0] = 2 * r.x * r.z + 2 * r.w * r.y;
    _data[2][1] = 2 * r.y * r.z - 2 * r.w * r.x;
    _data[2][2] = 1 - 2 * r.x * r.x - 2 * r.y * r.y;
}

Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ)
{
    Matrix4x4 mat;
    mat(0, 0) = scaleX;
    mat(1, 1) = scaleY;
    mat(2, 2) = scaleZ;
    mat(3, 3) = 1;
    return mat;
}

Matrix4x4 TranslateMatrix(float dx, float dy, float dz)
{
    Matrix4x4 mat;
    mat(0, 0) = 1;
    mat(1, 1) = 1;
    mat(2, 2) = 1;
    mat(3, 3) = 1;
    mat(3, 0) = dx;
    mat(3, 1) = dy;
    mat(3, 2) = dz;
    return mat;
}