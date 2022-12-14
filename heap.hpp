#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
    return;
}

class Heap
{
protected:
    vector<int> _arr;
    int _size;
    int _capacity;

public:
    Heap() {}

    Heap(vector<int> &a, int size) : _size(size), _capacity(size)
    {
        for (int i = 0; i < size; i++)
            _arr.push_back(a[i]);
    }

    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }
    int parent(int index) { return (index - 1) / 2; }
    int size() { return _size; }

    void ShiftUp(int i)
    {
        while (i > 0 && _arr[parent(i)] < _arr[i])
        {
            swap(_arr[parent(i)], _arr[i]);
            i = parent(i);
        }
    }

    void MaxHeapify(int i)
    {
        int l = left(i);
        int r = right(i);

        int largest = i;

        if (l < _size && _arr[l] > _arr[i])
            largest = l;
        else
            largest = i;

        if (r < _size && _arr[r] > _arr[largest])
            largest = r;

        if (largest != i)
        {
            swap(_arr[i], _arr[largest]);
            MaxHeapify(largest);
        }
    }

    void BuildHeap()
    {
        for (int i = (_size - 1) / 2; i >= 0; i--)
            MaxHeapify(i);
    }

    void HeapSort()
    {
        int a = _size;
        BuildHeap();
        for (int i = _size - 1; i >= 0; i--)
        {
            swap(_arr[0], _arr[i]);
            _size--;
            MaxHeapify(0);
        }
        _size = a;
    }

    void InsertKey(int data)
    {
        if (_size == _capacity)
        {
            _arr.push_back(data);
            _size++;
            _capacity++;
        }
        else
        {
            _arr[_size++] = data;
        }

        int i = _size - 1;
        ShiftUp(i); // ask why it is not swapping???
        // MaxHeapify((_size - 1) / 2);
    }

    int DeleteMax()
    {
        if (_size > 1)
        {
            int max = _arr[0];
            swap(_arr[0], _arr[_size - 1]);
            _size--;
            MaxHeapify(0);
            return max;
        }

        else
            cout << "Error\n";

        _capacity--;
        return -1;
    }

    void Print()
    {
        for (int i = 0; i < _size; i++)
            cout << _arr[i] << " ";
        cout << endl;
        return;
    }
};

#endif