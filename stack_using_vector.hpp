#ifndef __STACK_USING_VECTOR_HPP__
#define __STACK_USING_VECTOR_HPP__

#include "vector.hpp"

template <class T>
class Stack
{
private:
    Vector<T> st;

public:
    void push(T element)
    {
        st[st.getsize()] = element;
    }
    T pop()
    {
        if (st.getsize() == 0)
        {
            cout << "ERROR";
            exit(1);
        }
        else
        {
            T r = st[st.getsize() - 1];
            st.remove_ind(st.getsize() - 1);
            return r;
        }
    }
};

#endif