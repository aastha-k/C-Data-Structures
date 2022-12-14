#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T _data;
    Node *_left;
    Node *_right;
    Node *_parent;
    int height;
    Node(T data)
    {
        _data = data;
        _left = _right = _parent = NULL;
        height = 1;
    }
};

template <typename T>
class AVLTree
{
private:
    Node<T> *_root;
    Node<T> *RightRotate(Node<T> *node)
    {
        Node<T> *new_root = node->_left;
        Node<T> *temp = new_root->_right;
        if (temp != NULL)
            temp->_parent = node;
        new_root->_right = node;
        node->_left = temp;
        node->_parent = new_root;
        node->height = 1 + max(height(node->_left), height(node->_right));
        new_root->height = 1 + max(height(new_root->_left), height(new_root->_right));
        return new_root;
    }

    Node<T> *LeftRotate(Node<T> *node)
    {
        Node<T> *new_root = node->_right;
        Node<T> *temp = new_root->_left;
        if (temp != NULL)
            temp->_parent = node;
        new_root->_left = node;
        node->_right = temp;
        node->_parent = new_root;
        node->height = 1 + max(height(node->_left), height(node->_right));
        new_root->height = 1 + max(height(new_root->_left), height(new_root->_right));
        return new_root;
    }
    Node<T> *insertNode(Node<T> *root, T data)
    {
        if (root == NULL)
        {
            return new Node<T>(data);
        }
        else if (root->_data > data)
        {
            root->_left = insertNode(root->_left, data);
            root->_left->_parent = root;
        }
        else if (root->_data < data)
        {
            root->_right = insertNode(root->_right, data);
            root->_right->_parent = root;
        }
        else
        {
            return root;
        }
        root->height = 1 + max(height(root->_left), height(root->_right));
        int bal_fac = height(root->_left) - height(root->_right);
        if (bal_fac >= -1 && bal_fac <= 1)
        {
            return root;
        }
        if (bal_fac > 1 && data < root->_left->_data)
        {
            return RightRotate(root);
        }
        if (bal_fac > 1 && data > root->_left->_data)
        {
            root->_left = LeftRotate(root->_left);
            return RightRotate(root);
        }
        if (bal_fac < -1 && data > root->_right->_data)
        {
            return LeftRotate(root);
        }
        if (bal_fac < -1 && data < root->_right->_data)
        {
            root->_right = RightRotate(root->_right);
            return LeftRotate(root);
        }
        return root;
    }
    bool searchNode(Node<T> *root, T data)
    {
        if (root == NULL)
        {
            return false;
        }
        if (root->_data == data)
        {
            return true;
        }
        else if (root->_data > data)
        {
            return searchNode(root->_left, data);
        }
        else
        {
            return searchNode(root->_right, data);
        }
    }
    void PreorderTraversal(Node<T> *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->_data << " ";
        PreorderTraversal(root->_left);
        PreorderTraversal(root->_right);
    }
    void InorderTraversal(Node<T> *root)
    {
        if (root == NULL)
        {
            return;
        }
        InorderTraversal(root->_left);
        cout << root->_data << " ";
        InorderTraversal(root->_right);
    }
    void PostorderTraversal(Node<T> *root)
    {
        if (root == NULL)
        {
            return;
        }
        PostorderTraversal(root->_left);
        PostorderTraversal(root->_right);
        cout << root->_data << " ";
    }
    void printTree(Node<T> *root, string indent, bool last)
    {
        if (root != nullptr)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->_data << endl;
            printTree(root->_left, indent, false);
            printTree(root->_right, indent, true);
        }
    }
    Node<T> *DeleteNode(Node<T> *root, T data)
    {
        if (root == NULL)
        {
            cout << "Tree is either empty or does not have the element!!" << endl;
            return root;
        }
        else if (root->_data > data)
        {
            root->_left = DeleteNode(root->_left, data);
            if (root->_left != NULL)
                root->_left->_parent = root;
        }
        else if (root->_data < data)
        {
            root->_right = DeleteNode(root->_right, data);
            if (root->_right != NULL)
                root->_right->_parent = root;
        }
        else
        {
            if (root->_left == NULL && root->_right == NULL)
            {
                Node<T> *temp = root->_parent;
                Node<T> *to_delete = root;
                if (root == temp->_left)
                {
                    temp->_left = NULL;
                }
                else
                {
                    temp->_right = NULL;
                }
                root = NULL;
                return NULL;
            }

            else if (root->_left != NULL && root->_right == NULL)
            {
                // only one child
                Node<T> *temp = root->_parent;
                Node<T> *new_root = root->_left;
                if (temp != NULL)
                {
                    if (root == temp->_left)
                    {
                        temp->_left = new_root;
                    }
                    else
                    {
                        temp->_right = new_root;
                    }
                }
                delete root;
                return new_root;
            }
            else if (root->_left == NULL && root->_right != NULL)
            {
                // only one child
                Node<T> *temp = root->_parent;
                Node<T> *new_root = root->_right;
                if (temp != NULL)
                {
                    if (root == temp->_left)
                    {
                        temp->_left = new_root;
                    }
                    else
                    {
                        temp->_right = new_root;
                    }
                }
                delete root;
                return new_root;
            }
            else
            {
                // both children are present, so we find maximum element in left subtree and swap.
                Node<T> *temp = root->_left;
                while (temp->_right != NULL)
                {
                    temp = temp->_right;
                }
                T to_change = temp->_data;
                root->_data = to_change;
                root->_left = DeleteNode(root->_left, to_change);
            }
        }
        if (root == NULL)
            return root;
        // recursively updating heights and checking for imbalance all the way up untill root.
        root->height = 1 + max(height(root->_left), height(root->_right));
        int bal_fac = height(root->_left) - height(root->_right);
        if (bal_fac <= 1 && bal_fac >= -1)
        {
            return root;
        }
        else if (bal_fac < -1)
        {
            if (height(root->_right->_left) < height(root->_right->_right))
            {
                root = LeftRotate(root);
            }
            else
            {
                root->_right = RightRotate(root->_right);
                root = LeftRotate(root);
            }
        }
        else if (bal_fac > 1)
        {
            if (height(root->_left->_left) > height(root->_left->_right))
            {
                root = RightRotate(root);
            }
            else
            {
                root->_left = LeftRotate(root->_left);
                root = RightRotate(root);
            }
        }
        return root;
    }

public:
    int height(Node<T> *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        else
        {
            return root->height;
        }
    }
    AVLTree() { _root = NULL; }
    AVLTree(Node<T> *root)
    {
        _root = root;
    }
    void insert(T data)
    {
        _root = insertNode(_root, data);
    }
    bool search(T data)
    {
        return searchNode(_root, data);
    }
    void Inorder()
    {
        InorderTraversal(_root);
    }
    void Preorder()
    {
        PreorderTraversal(_root);
    }
    void Postorder()
    {
        PostorderTraversal(_root);
    }
    void PrintTree()
    {
        printTree(_root, "  ", true);
    }
    void DelNode(T data)
    {
        _root = DeleteNode(_root, data);
    }
};