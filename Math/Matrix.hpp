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
    Type &operator()(size_t i,size_t j)
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
    ~Matrix(){};

    //Debug stuff
    void print();
};
