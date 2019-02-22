#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
template <typename Type, size_t M, size_t N>
class Matrix
{
  private:
  public:
    Type _data[M][N]{};

    Matrix() = default;
    Matrix(const Type data[M*N])
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
    inline Type &operator()(size_t i,size_t j)
    {
        return _data[i][j];
    }

    inline Type &operator()(size_t i,size_t j)const
    {
        return _data[i][j];
    }

    Matrix& operator=(const Matrix& other)
    {
        
        if (this != &other) {
             memcpy(_data, other._data, sizeof(_data));
        }
        return *this;
    }

    template <size_t P>
    Matrix<Type, M, P> operator*(const Matrix<Type, N, P> &other) const;
    Matrix<Type, M, N> operator+(const Matrix<Type, M, N> &other) const;
    Matrix<Type, M, N> operator-(const Matrix<Type, M, N> &other) const;
    Matrix<Type, M, N> operator-() const;
    void operator+=(const Matrix<Type, M, N> &other) ;
    void operator-=(const Matrix<Type, M, N> &other) ;
    Matrix<Type, M, N> operator*(Type scalar) const;
    Matrix<Type, M, N> operator/(Type scalar) const;
    Matrix<Type, M, N> operator+(Type scalar) const;
    Matrix<Type, M, N> operator-(Type scalar) const;
    void operator+=(Type scalar) ;
    void operator-=(Type scalar) ;
    void operator*=(Type scalar) ;
    void operator/=(Type scalar) ;
    ~Matrix(){};

    Matrix<Type, M, N> Transpose() const;

    inline void Zero(){
        memset(_data, 0, sizeof(_data));
    }

    void SetAll(Type val)
    {
        
        for(size_t i = 0; i < M; i++)
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
        
        for(size_t i = 0; i < M & i < N; i++)
        {
            *this(i, i) = 1;
        }
        
    }

    static Matrix<Type, M, N> Identitys() 
    {
        Matrix<Type, M, N> res;
        res.Identity();
        return res;
    }
    //Debug stuff
    void print();
};

#endif // !MATRIX_H