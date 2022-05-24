#include<iostream>
using namespace std;

template <class T>
struct node
{
    T data;
    node* left;
    node* right;
    int height;
};

template <class T, class V>
class BST
{
    node<T>* root;
    void makeEmpty(node<T>* t)
    {
        if (t == NULL)return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node<T>* insert(int x, node<T>* t)
    {
        if (t == NULL)
        {
            t = new node<T>;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
        {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if (x > t->data)
        {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    node<T>* singleRightRotate(node<T>*& t)
    {
        node<T>* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }

    node<T>* singleLeftRotate(node<T>*& t)
    {
        node<T>* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    node<T>* doubleLeftRotate(node<T>*& t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node<T>* doubleRightRotate(node<T>*& t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node<T>* findMin(node<T>* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node<T>* findMax(node<T>* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node<T>* remove(int x, node<T>* t)
    {
        node<T>* temp;
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }
        if (t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right)) + 1;
        if (height(t->left) - height(t->right) == 2)
        {
            if (height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            else
                return doubleLeftRotate(t);
        }
        else if (height(t->right) - height(t->left) == 2)
        {
            if (height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(node<T>* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node<T>* t)
    {
        if (t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(node<T>* t)
    {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

public:
    BST()
    {
        root = NULL;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }

    bool  _Retrieve(V   key, T& dataOut)
    {
        node<T>* node;
        if (!root)return false;
        node = _retrieve(key, root);
        if (node)
        {
            dataOut = node->data;
            return true;
        }
        else return false;
    }

    node<T>* _Retrieve2(V   key, T& dataOut)
    {
        node<T>* node;
        if (!root)return NULL;
        node = _retrieve(key, root);
        if (node)
        {
            return node;
        }
        else return NULL;
    }

    node<T>* _retrieve(V key, node<T>* root)
    {
        if (root)
        {
            if (key < root->data.key) return _retrieve(key, root->left);
            else if (key > root->data.key) return _retrieve(key, root->right);
            else return (root);
        }
        else return root;
    }


    bool _Insert(T dataIn)
    {
        node<T>* newPtr;
        bool taller;
        if (!(newPtr = new node<T>))return false;
        newPtr->right = NULL;
        newPtr->left = NULL;
        newPtr->data = dataIn;
        root = _insert(root, newPtr, taller);
        return true;
    }

    node<T>* _insert(node<T>* root, node<T>* newPtr, bool& taller)
    {
        if (!root)
        {
            root = newPtr;
            taller = true;
            return  root;
        }
        if (newPtr->data.key < root->data.key)
        {
            root->left = _insert(root->left, newPtr, taller);

        }
        else
        {
            root->right = _insert(root->right, newPtr, taller);
        }
        return root;
    }

    void  _Traverse(void(*process)(T dataProc))
    {
        _traversal(process, root); return;
    }

    void  _Traverse_preorder(void(*process)(T dataProc))
    {
        _traversal_preorder(process, root);
        return;
    }

    void _Traverse_postorder(void(*process)(T dataProc))
    {
        _traversal_postorder(process, root);
        return;
    }

    void _traversal(void(*process)(T dataproc), node<T>* root)
    {
        if (root)
        {
            _traversal(process, root->left);
            process(root->data);
            _traversal(process, root->right);
        }
        return;
    }

    void _traversal_preorder(void(*process)(T dataproc), node<T>* root)
    {
        if (root)
        {
            process(root->data);
            _traversal_preorder(process, root->left);
            _traversal_preorder(process, root->right);
        }
        return;
    }

    void  _traversal_postorder(void(*process)(T dataproc), node<T>* root)
    {
        if (root)
        {
            _traversal_preorder(process, root->left);
            _traversal_preorder(process, root->right);
            process(root->data);
        }
        return;
    }

    void  _Print(void)
    {
        _print(root, 0);
        cout << "\n" << "\n";
        return;
    }

    void  _print(node<T>* root, int level)
    {
        int i;
        if (root)
        {
            _print(root->right, level + 1);
            cout << endl;
            cout << root->data.key;
            _print(root->left, level + 1);
        }
    }
};