#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
template <typename Type, size_t M, size_t N>
class Matrix
{
  private:
  public:
    Type _data[M][N]{};

    Matrix() { Zero(); };
    Matrix(const Type data[M * N])
    {
        memcpy(_data, data, sizeof(_data));
    };

    Matrix(const Type data[M][N])
    {
        memcpy(_data, data, sizeof(_data));
    };
    Matrix(const Matrix &other)
    {
        memcpy(_data, other._data, sizeof(_data));
    };
    inline Type &operator()(size_t i, size_t j)
    {
        return _data[i][j];
    }

    inline Type &operator()(size_t i, size_t j) const
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

    template <size_t P>
    Matrix<Type, M, P> operator*(const Matrix<Type, N, P> &other) const;
    Matrix<Type, M, N> operator+(const Matrix<Type, M, N> &other) const;
    Matrix<Type, M, N> operator-(const Matrix<Type, M, N> &other) const;
    Matrix<Type, M, N> operator-() const;
    void operator+=(const Matrix<Type, M, N> &other);
    void operator-=(const Matrix<Type, M, N> &other);
    Matrix<Type, M, N> operator*(Type scalar) const;
    Matrix<Type, M, N> operator/(Type scalar) const;
    Matrix<Type, M, N> operator+(Type scalar) const;
    Matrix<Type, M, N> operator-(Type scalar) const;
    void operator+=(Type scalar);
    void operator-=(Type scalar);
    void operator*=(Type scalar);
    void operator/=(Type scalar);
    ~Matrix(){};

    Matrix<Type, M, N> Transpose() const;

    inline void Zero()
    {
        memset(_data, 0, sizeof(_data));
    }

    void SetAll(Type val)
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
        for (size_t i = 0; i < M & i < N; i++)
        {
            *this(i, i) = 1;
        }
    }

    inline void SwapRows(size_t a, size_t b)
    {
        if (a == b)
        {
            return;
        }
        Matrix<Type, M, N> &self = *this;
        for (size_t j = 0; j < N; j++)
        {
            Type tmp = self(a, j);
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
        Matrix<Type, M, N> &self = *this;
        for (size_t i = 0; i < M; i++)
        {
            Type tmp = self(i, a);
            self(i, a) = self(i, b);
            self(i, b) = tmp;
        }
    }
    //Debug stuff
    void print();
};

template <typename Type, size_t M>
class SquareMatrix : public Matrix<Type, M, M>
{
  private:
    bool inv(SquareMatrix<Type, M> &inv)const;

  public:
    SquareMatrix() : Matrix<Type, M, M>() {}
    SquareMatrix(const Type data_[M][M]) : Matrix<Type, M, M>(data_) {}
    SquareMatrix(const Matrix<Type, M, M> &other) : Matrix<Type, M, M>(other) {}
    ~SquareMatrix();
    inline SquareMatrix<Type,M> Inverse() const
    {
        SquareMatrix<Type, M> res;
        if (!inv(res))
        {
            res.Zero();
        }
        return res;
    }
};

typedef SquareMatrix<float, 4> Matrix4x4;
typedef SquareMatrix<float, 4> Matrix3x3;

#endif // !MATRIX_H