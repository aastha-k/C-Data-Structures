#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "linkedlist.hpp"

template <class T>
class Stack
{
private:
	LinkedList<T> _stack;

public:
	Stack() {}
	bool isEmpty() { return _stack.ll_size() == 0; }
	int s_size() { return _stack.ll_size(); }
	T &top() { return _stack.tail(); }

	void push(const T &e) { _stack.append(e); }
	T pop() { return _stack.remove_last(); }
};

#endif