
#pragma once

#include <cstring>
#include <type_traits>
using namespace std;
//Templated struct to emulate GPU buffers such as
//the frame buffer and the ZBuffer
//Also keeps track of a bunch of useful data about itself
template <class T>
struct Buffer
{
    int mWidth, mHeight, mPixelCount, mPitch, mOrigin;
    T *buffer;

    T &operator()(size_t x, size_t y)
    {
        return buffer[y * mWidth + x];
    }

    Buffer(int w, int h)
        : mWidth(w), mHeight(h), mPixelCount(w * h), mPitch(w * sizeof(T)),
          mOrigin(mHeight * mWidth - mWidth)
    {
        buffer = new T[mPixelCount];
    }

    ~Buffer() { delete[] buffer; }

    //Cannot use memset to clear a float since the binary
    //Representation is more complex. We just iterate through the whole
    //thing and explicitely set it to zero instead
    void clear()
    {
        if (std::is_same<T, float>::value)
        {
            for (int i = 0; i < mPixelCount; ++i)
            {
                buffer[i] = 0.0f;
            }
        }
        else
        {
            //Set to a 15% white color to make it nicer looking.
            memset(buffer, 0xee, mPitch * mHeight);
        }
    }

    void SetBuffer(int x0, int y0, int x1, int y1,T data)
    {
        int begin = y0 * mWidth + x0;
        int end = y1 * mWidth + x1;
        
        if (end < begin) {
            return;
        }
        

        for (int i = begin; i <= end; ++i)
        {
            buffer[i] = data;
        }

    }
};
