#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>
using namespace std;

template <class T>
class Vector
{
private:
    T *arr;
    int currsize;
    int capacity;

public:
    Vector(int n = 1)
    {
        arr = new T[n];
        currsize = 0;
        capacity = n;
    }

    ~Vector()
    {
        delete[] arr;
    }

    int getsize()
    {
        return currsize;
    }

    int getcapacity()
    {
        return capacity;
    }

    T &operator[](int index)
    {
        if (index < currsize)
        {
            return arr[index];
        }
        if (index > currsize)
        {
            cout << "ERROR";
            exit(1);
        }
        if (currsize == capacity)
        {
            T *narr = new T[2 * capacity];
            for (int i = 0; i < capacity; i++)
            {
                narr[i] = arr[i];
            }
            delete[] arr;
            arr = narr;
            capacity = 2 * capacity;
        }
        currsize++;
        return arr[index];
    }

    T remove_ind(int index)
    {
        T k = arr[index];
        for (int i = index; i < currsize - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        currsize--;
        if (currsize <= capacity / 4)
        {
            T *narr = new T[capacity / 2];
            for (int i = 0; i < capacity; i++)
            {
                narr[i] = arr[i];
            }
            delete[] arr;
            arr = narr;
            capacity = capacity / 2;
        }
        return k;
    }
};

#endif