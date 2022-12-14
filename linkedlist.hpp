#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

template <class T>
class LinkedList
{
private:
	class Link
	{
	public:
		T _data;
		Link *_prev;
		Link *_next;
		Link(const T &data) : _data(data) { _prev = _next = NULL; }
		~Link() { _prev = _next = NULL; }
	};

	Link *_head;
	Link *_tail;
	int _length;

public:
	LinkedList()
	{
		_head = _tail = NULL;
		_length = 0;
	}
	~LinkedList()
	{
		for (int i = 0; i < _length; ++i)
		{
			Link *n = _head;
			_head = _head->_next;
			delete n;
		}
	}

	int ll_size() { return _length; }

	void append(const T &data)
	{
		Link *n = new Link(data);
		if (_length == 0)
			_head = _tail = n;
		else
		{
			_tail->_next = n;
			n->_prev = _tail;
			_tail = n;
		}
		_length++;
	}

	T &tail() { return _tail->_data; }

	T remove_last()
	{
		T ret = _tail->_data;
		if (_length == 1)
			_head = _tail = NULL;
		else
			_tail = _tail->_prev;

		delete _tail;
		_length--;
		return ret;
	}

	T &get(int index)
	{
		Link *curr = _head;
		for (int i = 0; i < index; i++)
		{
			curr = curr->_next;
		}
		return curr->_data;
	}
};

#endif
