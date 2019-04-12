
#ifndef MATRIX_H
#define MATRIX_H
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
    bool operator==(const Matrix<M, N> &other) const;
    bool operator!=(const Matrix<M, N> &other) const;
    template <size_t P>
    Matrix<M, P> operator*(const Matrix<N, P> &other) const;
    Matrix<M, N> operator+(const Matrix<M, N> &other) const;
    Matrix<M, N> operator-(const Matrix<M, N> &other) const;
    Matrix<M, N> operator-() const;
    void operator+=(const Matrix<M, N> &other);
    void operator-=(const Matrix<M, N> &other);
    Matrix<M, N> operator*(float scalar) const;
    Matrix<M, N> operator/(float scalar) const;
    Matrix<M, N> operator+(float scalar) const;
    Matrix<M, N> operator-(float scalar) const;
    void operator+=(float scalar);
    void operator-=(float scalar);
    void operator*=(float scalar);
    void operator/=(float scalar);
    ~Matrix(){};

    Matrix<M, N> Transpose() const;

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
    bool inv(SquareMatrix<M> &inv) const;

  public:
    SquareMatrix() : Matrix<M, M>() {}
    SquareMatrix(const float data_[M][M]) : Matrix<M, M>(data_) {}
    SquareMatrix(const Matrix<M, M> &other) : Matrix<M, M>(other) {}
    ~SquareMatrix();
    inline SquareMatrix<M> Inverse() const
    {
        SquareMatrix<M> res;
        if (!inv(res))
        {
            res.Zero();
        }
        return res;
    }
    float Determinant() const;
};

typedef SquareMatrix<4> Matrix4x4;
typedef SquareMatrix<3> Matrix3x3;

class EulerAngles;
class Quaternion;
class RotationMatrix : public Matrix3x3
{
  private:
    /* data */
  public:
    RotationMatrix() : Matrix3x3(){};
    RotationMatrix(const float data_[3][3]) : Matrix3x3(data_) {}
    RotationMatrix(const Matrix3x3 &other) : Matrix3x3(other) {}
    RotationMatrix(const EulerAngles &rotation);
    RotationMatrix(const Quaternion &q);
};

extern Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ);
extern Matrix4x4 TranslateMatrix(float dx, float dy, float dz);
#endif // !MATRIX_H