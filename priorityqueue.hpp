#ifndef __PRIORITY_QUEUE_HPP__
#define __PRIORITY_QUEUE_HPP__

#include <iostream>
#include <vector>
#include "heap.hpp"
using namespace std;

class PriorityQueue : public Heap
{
private:
    vector<int> *_pq;
    Heap pq;

public:
    PriorityQueue(vector<int> &a, int size)
    {
        pq = Heap(a, size);
        pq.BuildHeap();
        _pq = pq.Array();
    }

    void MoveUp(int i) { pq.ShiftUp(i); }
    void MoveDown(int i) { pq.MaxHeapify(i); }
    void Insert(int p) { pq.InsertKey(p); }
    int RemoveMax() { return pq.DeleteMax(); }
    void PrintQ() { pq.Print(); }

    void changePriority(int i, int p)
    {
        vector<int> &vr = *_pq;
        int oldp = vr[i] + 1;
        vr[i] = p;
        if (p > oldp)
            MoveUp(i);
        else
            MoveDown(i);
    }

    void Remove(int i)
    {
        vector<int> &vr = *_pq;
        vr[i] = vr[0] + 1;
        MoveUp(i);
        RemoveMax();
    }
};

#endif