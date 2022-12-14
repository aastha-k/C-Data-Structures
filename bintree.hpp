#ifndef __TREE_HPP__
#define __TREE_HPP__

#include <iostream>
#include <vector>

using namespace std;
template <class T>
int search(vector<T> &vec, int start, int end, T value)
{
	for (int i = start; i <= end; i++)
	{
		if (vec[i] == value)
			return i;
	}
	return -1;
}

template <class T>
class BinaryTree
{
protected:
	class Node
	{
	public:
		T _data;
		Node *_left, *_right, *_parent;

		Node()
		{
			_left = NULL;
			_right = NULL;
			_parent = NULL;
		}

		Node(char data)
		{
			_data = data;
			_left = NULL;
			_right = NULL;
			_parent = NULL;
		}

		Node(T data, Node *l, Node *r)
		{
			_data = data;
			_left = l;
			_right = r;
			_parent = NULL;
			if (l)
				l->_parent = this;
			if (r)
				r->_parent = this;
		}
	};

	Node *_root;

	Node *ConstructTreeWithInAndPre(vector<T> &pre, int p_start, int p_end, vector<T> &in, int i_start, int i_end)
	{
		if (i_start > i_end || p_start > p_end)
			return NULL;
		Node *n = new Node(pre[p_start]);
		int index = search(in, i_start, i_end, pre[p_start]);
		if (i_start == i_end && p_start == p_end)
			return n;
		n->_left = ConstructTreeWithInAndPre(pre, p_start + 1, p_start + index, in, i_start, i_start + index - 1); // check if this works, otherwise try dhruva's try
		n->_right = ConstructTreeWithInAndPre(pre, p_start + index + 1, p_end, in, i_start + index + 1, i_end);
	}

	Node *ConstructTreeWithInAndPost(vector<T> &post, int p_start, int p_end, vector<T> &in, int i_start, int i_end)
	{
		if (i_start > i_end || p_start > p_end)
			return NULL;
		Node *n = new Node(post[p_end]);
		int index = search(in, i_start, i_end, post[p_end]);
		if (i_start == i_end && p_start == p_end)
			return n;
		n->_left = ConstructTreeWithInAndPost(post, p_start, p_start + index - 1, in, i_start, i_start + index - 1);
		n->_right = ConstructTreeWithInAndPost(post, p_start + index, p_end - 1, in, i_start + index + 1, i_end);
	}

	BinaryTree(Node *r)
	{
		_root = r;
	}

public:
	BinaryTree() {}
	BinaryTree(T data)
	{
		_root = new Node(data);
	}

	BinaryTree(T data, BinaryTree<T> &leftsubtree, BinaryTree<T> &rightsubtree)
	{
		_root = new Node(data, leftsubtree->_root, rightsubtree->_root);
		_root->_right->_parent = this;
		_root->_left->_parent = this;
	}

	BinaryTree(vector<T> &preorderorpostorder, vector<T> &inorder, bool i)
	{
		if (preorderorpostorder.size() != inorder.size())
		{
			cout << "ERROR: sizes are not same" << endl;
			return;
		}
		else
		{
			if (i)
				_root = ConstructTreeWithInAndPost(preorderorpostorder, 0, preorderorpostorder.size() - 1, inorder, 0, preorderorpostorder.size() - 1); // to use in and post make bool true

			else
				_root = ConstructTreeWithInAndPre(preorderorpostorder, 0, preorderorpostorder.size() - 1, inorder, 0, preorderorpostorder.size() - 1); // to use in and pre make bool false
		}
	}

	BinaryTree<T> &left()
	{
		BinaryTree *leftsub = new BinaryTree(_root->_left);
		return *leftsub;
	}

	BinaryTree<T> &right()
	{
		BinaryTree *rightsub = new BinaryTree(_root->_right);
		return *rightsub;
	}

	BinaryTree<T> &parent()
	{
		BinaryTree *par = new BinaryTree(_root->_parent);
		return *par;
	}

	void remove()
	{
		if (_root != NULL)
		{
			if (_root->_parent != NULL)
			{
				Node *temp = _root->_parent;
				if (temp->_left == _root)
				{
					temp->_left = NULL;
					cout << temp << ": Left deleted\n";
				}
				if (temp->_right == _root)
				{
					temp->_right = NULL;
					cout << temp << ": Right deleted\n";
				}
				else
				{
					cout << "Error! Node Structure Broken!\n";
					exit(1);
				}
			}
			_root.left()->remove();
			_root.right()->remove();
			delete _root;
		}
	}

	void insert_leftchild(T data)
	{
		Node *leftch = new Node(data);
		leftch->_parent = _root;
		_root->_left = leftch;
	}

	void insert_rightchild(T data)
	{
		Node *rightch = new Node(data);
		rightch->_parent = _root;
		_root->_right = rightch;
	}

	void insert_leftchild(BinaryTree<T> &l)
	{
		_root->_left = l._root;
		l._root->_parent = _root;
	}

	void insert_rightchild(BinaryTree<T> &r)
	{
		_root->_right = r._root;
		r._root->_parent = _root;
	}

	T &root()
	{
		if (_root == NULL)
		{
			_root = new Node();
		}
		return _root->_data;
	}

	vector<T> &PreOrder()
	{
		vector<T> *ret = new vector<T>();
		if (_root == NULL)
		{
			return *ret;
		}
		ret->push_back(_root->_data);
		BinaryTree *left = new BinaryTree(_root->_left);
		vector<T> vleft = left->PreOrder();
		ret->insert(ret->end(), vleft.begin(), vleft.end());
		BinaryTree *right = new BinaryTree(_root->_right);
		vector<T> vright = right->PreOrder();
		ret->insert(ret->end(), vright.begin(), vright.end());
		return *ret;
	}

	vector<T> &InOrder()
	{
		vector<T> *ret = new vector<T>();
		if (_root == NULL)
		{
			return *ret;
		}
		BinaryTree *left = new BinaryTree(_root->_left);
		vector<T> vleft = left->InOrder();
		ret->insert(ret->end(), vleft.begin(), vleft.end());
		ret->push_back(_root->_data);
		BinaryTree *right = new BinaryTree(_root->_right);
		vector<T> vright = right->InOrder();
		ret->insert(ret->end(), vright.begin(), vright.end());
		return *ret;
	}

	vector<T> &PostOrder()
	{
		vector<T> *ret = new vector<T>();
		if (_root == NULL)
		{
			return *ret;
		}
		BinaryTree *left = new BinaryTree(_root->_left);
		vector<T> vleft = left->PostOrder();
		ret->insert(ret->end(), vleft.begin(), vleft.end());
		BinaryTree *right = new BinaryTree(_root->_right);
		vector<T> vright = right->PostOrder();
		ret->insert(ret->end(), vright.begin(), vright.end());
		ret->push_back(_root->_data);
		return *ret;
	}
};

#endif