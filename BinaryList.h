#ifndef BINARYLIST_H
#define BINARYLIST_H
#include <iostream>
using std::ostream;

enum LR {
    LEFT = 0, 
    RIGHT = 1
};

template <typename T>
class BinaryNode {
public:

    BinaryNode(BinaryNode<T> *l = NULL, BinaryNode<T> *r = NULL, BinaryNode<T> *p = NULL) : _left(l), _right(r), _parent(p) {
        T d;
        _data = d;
    }

    explicit BinaryNode(const T &d, BinaryNode<T> *l = NULL, BinaryNode<T> *r = NULL, BinaryNode<T> *p = NULL) : _data(d), 
    _left(l), _right(r), _parent(p) {}

    ~BinaryNode() {
        
            delete _left;
        
        
            delete _right;
        
    }
    
    T getData() const {
        return _data;
    }

    unsigned int depth() const;
    
    friend ostream& operator<<(ostream& out, const BinaryNode<T> &e) {
        out << e._data;
        return out;
    }

    void setData(const T &d) {
        _data = d;
    }
    BinaryNode<T>*& parent() {
        return _parent;
    }
    BinaryNode<T>*& leftChild() {
        return _left;
    }
    BinaryNode<T>*& rightChild() {
        return _right;
    }

private:
    T _data;
    BinaryNode<T> *_left;
    BinaryNode<T> *_right;
    BinaryNode<T> *_parent;
    
};

template <typename T>
class BinaryList {
public:
    BinaryList() {
        _root = NULL;
    }
    explicit BinaryList(const T &d) {
        _root = new BinaryNode<T>(d);
    }
    ~BinaryList() {
        if (_root) {
            delete _root;
        }
    }

    bool isEmpty() const {return (_root == NULL);}
    unsigned int getDepth() const {
        if (!_root) return 0;
        return _root->depth();
    }
    //friend ostream& operator<<(ostream&, const BinaryList<T> &);

    BinaryNode<T>* getRoot() {return _root;}
    BinaryNode<T>* findNode(const T &e, BinaryNode<T> *p = getRoot());

    //BinaryNode& leftSibling( BinaryNode &e) ;
    //BinaryNode& rightSibling( BinaryNode &e) ;
    void clear();
    void setValue(BinaryNode<T> &e, const T &d) { e.setData(d); }
    void insertNode(BinaryNode<T> &p, LR place, BinaryNode<T> &c);
    void deleteNode(BinaryNode<T> &p, LR place);
    void preOrder(void (*visit)(const T &));
    void inOrder(void (*visit)(const T &));
    void postOrder(void (*visit)(const T &));
    void levelOrder(void (*visit)(const T &));
private:
    BinaryNode<T> *_root;
};

#endif