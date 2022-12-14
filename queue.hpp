#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

template <class T>
class Queue
{
private:
	int _rear, _front;
	int _currsize;
	int _capacity;
	int *arr;

public:
	Queue(int n = 1)
	{
		arr = new T[n];
		_rear = _front = 0;
		_currsize = 0;
		_capacity = n;
	}

	~Queue()
	{
		delete[] arr;
	}

	int size() { return _currsize; }
	int capacity() { return _capacity; }
	T front() { return _front; }
	T rear() { return _rear; }

	void enqueue(T element)
	{
		if (_currsize == 0)
		{
			arr[_rear] = element;
			_currsize++;
		}
		else
		{
			if (_currsize == _capacity)
			{
				T *narr = new T[2 * _capacity];
				for (int i = 0; i < _capacity; i++)
				{
					narr[i] = arr[i];
				}
				delete[] arr;
				arr = narr;
				_capacity = 2 * _capacity;
			}
			_rear++;
			_rear = (_rear) % (_capacity);
			arr[_rear] = element;
			_currsize++;
		}
	}

	T dequeue()
	{
		if (_front > _rear || _currsize == 0)
		{
			exit(1);
		}
		T r = arr[_front];
		if (_currsize <= _capacity / 4)
		{
			T *narr = new T[_capacity / 2];
			for (int i = 0; i < _currsize; i++)
			{
				narr[i] = arr[i + _front];
			}
			delete[] arr;
			arr = narr;
			_capacity = _capacity / 2;
			_front = 0;
			_rear = _currsize;
		}
		_front++;
		_currsize--;
		_front = (_front) % (_capacity);
		_rear = (_rear) % (_capacity);
		return r;
	}
};

#endif