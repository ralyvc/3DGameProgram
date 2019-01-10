
#pragma once

#include <type_traits>
#include <cstring>
using namespace std;
//Templated struct to emulate GPU buffers such as
//the frame buffer and the ZBuffer
//Also keeps track of a bunch of useful data about itself
template <class T>
struct Buffer
{
    int mWidth, mHeight, mPixelCount, mPitch, mOrigin;
    T *buffer;

    //The buffer is actually just a simple 1D array which we access using an equation
    //Notice how it's not the usual (y*width + x) equation that you see for most quasi 2D arrays
    //This is because the origin is at the lower left (instead of upper left) and y moves upwards
    T &operator()(size_t x, size_t y)
    {
        return buffer[mOrigin + -y * mWidth + x];
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
            memset(buffer, 0xD, mPitch * mHeight);
        }
    }
};
