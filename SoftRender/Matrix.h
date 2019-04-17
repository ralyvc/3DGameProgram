
#ifndef MATRIX_H
#define MATRIX_H
#include "EulerAngles.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include <cstring>
#include <iostream>

template <size_t M, size_t N>
class Matrix
{
  private:
  public:
    float _data[M][N]{};

    Matrix() { Zero(); };
    Matrix(const float data[M * N])
    {
        memcpy(_data, data, sizeof(_data));
    };

    Matrix(const float data[M][N])
    {
        memcpy(_data, data, sizeof(_data));
    };
    Matrix(const Matrix &other)
    {
        memcpy(_data, other._data, sizeof(_data));
    };
    inline float &operator()(size_t i, size_t j)
    {
        return _data[i][j];
    }

    inline float operator()(size_t i, size_t j) const
    {
        return _data[i][j];
    }

    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            memcpy(_data, other._data, sizeof(_data));
        }
        return *this;
    }

    bool operator==(const Matrix<M, N> &other) const
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

    bool operator!=(const Matrix<M, N> &other) const
    {
        return !(*this == other);
    }
    template <size_t P>
    Matrix<M, P> operator*(const Matrix<N, P> &other) const
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

    Matrix<M, N> operator+(const Matrix<M, N> &other) const
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

    Matrix<M, N> operator-(const Matrix<M, N> &other) const
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

    Matrix<M, N> operator-() const
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

    void operator+=(const Matrix<M, N> &other)
    {
        *this = *this + other;
    }

    void operator-=(const Matrix<M, N> &other)
    {
        *this = *this - other;
    }

    Matrix<M, N> operator+(float scalar) const
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

    Matrix<M, N> operator-(float scalar) const
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

    Matrix<M, N> operator*(float scalar) const
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

    Matrix<M, N> operator/(float scalar) const
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

    void operator+=(float scalar)
    {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                *this(i, j) = (*this)(i, j) + scalar;
            }
        }
    }

    void operator-=(float scalar)
    {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                *this(i, j) = (*this)(i, j) - scalar;
            }
        }
    }

    void operator*=(float scalar)
    {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                *this(i, j) = (*this)(i, j) * scalar;
            }
        }
    }

    void operator/=(float scalar)
    {
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                *this(i, j) = (*this)(i, j) / scalar;
            }
        }
    }

    Matrix<M, N> Transpose() const
    {
        Matrix<N, M> res;
        const Matrix<M, N> &self = *this;
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                res(i, j) = self(j, i);
            }
        }
        return res;
    }

    inline void Zero()
    {
        memset(_data, 0, sizeof(_data));
    }

    void SetAll(float val)
    {

        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                *this(i, j) = val;
            }
        }
    }

    inline void Identity()
    {
        Zero();
        Matrix<M, N> &self = *this;
        for (size_t i = 0; i < M & i < N; i++)
        {
            self(i, i) = 1;
        }
    }

    inline void SwapRows(size_t a, size_t b)
    {
        if (a == b)
        {
            return;
        }
        Matrix<M, N> &self = *this;
        for (size_t j = 0; j < N; j++)
        {
            float tmp = self(a, j);
            self(a, j) = self(b, j);
            self(b, j) = tmp;
        }
    }

    inline void SwapCols(size_t a, size_t b)
    {
        if (a == b)
        {
            return;
        }
        Matrix<M, N> &self = *this;
        for (size_t i = 0; i < M; i++)
        {
            float tmp = self(i, a);
            self(i, a) = self(i, b);
            self(i, b) = tmp;
        }
    }
    //Debug stuff
    void print();
};

template <size_t M>
class SquareMatrix : public Matrix<M, M>
{
  private:
    bool inv(SquareMatrix<M> &inv) const
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

  public:
    SquareMatrix() : Matrix<M, M>() {}
    SquareMatrix(const float data_[M][M]) : Matrix<M, M>(data_) {}
    SquareMatrix(const Matrix<M, M> &other) : Matrix<M, M>(other) {}
    inline SquareMatrix<M> Inverse() const
    {
        SquareMatrix<M> res;
        if (!inv(res))
        {
            res.Zero();
        }
        return res;
    }
    float Determinant() const
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
};

typedef SquareMatrix<4> Matrix4x4;
typedef SquareMatrix<3> Matrix3x3;

class EulerAngles;
class Quaternion;
class RotationMatrix : public Matrix4x4
{
  private:
    /* data */
  public:
    RotationMatrix() : Matrix4x4(){};
    RotationMatrix(const float data_[4][4]) : Matrix4x4(data_) {}
    RotationMatrix(const Matrix4x4 &other) : Matrix4x4(other) {}
    RotationMatrix(const EulerAngles &r)

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
        _data[3][3] = 1;
    }

    RotationMatrix(const Quaternion &r)
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
    };
};

static Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ)
{
    Matrix4x4 mat;
    mat(0, 0) = scaleX;
    mat(1, 1) = scaleY;
    mat(2, 2) = scaleZ;
    mat(3, 3) = 1;
    return mat;
}

static Matrix4x4 TranslateMatrix(float dx, float dy, float dz)
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

static Vector3<float> operator*(const Vector3<float> &lhs, const Matrix4x4 &mat) 
{
    Vector3<float> res;
    res.y = lhs.x * mat(0, 1) + lhs.y * mat(1, 1) + lhs.z * mat(2, 1) + mat(3, 1);
    res.z = lhs.x * mat(0, 2) + lhs.y * mat(1, 2) + lhs.z * mat(2, 2) + mat(3, 2);
    res.x = lhs.x * mat(0, 0) + lhs.y * mat(1, 0) + lhs.z * mat(2, 0) + mat(3, 0);
    return res;
}
#endif // !MATRIX_H