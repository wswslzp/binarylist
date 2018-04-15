#include "BinaryList.h"

/* get the depth of a subtree with a root of this node*/
template <typename T>
unsigned int BinaryNode<T>::depth() const {
    if (_left == NULL && _right == NULL) return 1;
    unsigned int leftDepth = _left->depth();
    unsigned int rightDepth = _right->depth();
    return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

/*clear the tree to a empty tree*/
template <typename T>
void BinaryList<T>::clear() {
    if (_root == NULL) return;
    delete _root;
    _root = NULL;
}

/*find the node that its data equal to the key
 *if not found, return the NULL
 *if found one, return the node;
 *if found two or more, return the first one;
 */
template <typename T>
BinaryNode<T>*
BinaryList<T>::findNode(const T &key, BinaryNode<T> *p) {
    if (p) {
        if (p->getData() == key) {
            return p;
        } else {
            BinaryNode<T> *tl = findNode(key, p->leftChild());
            BinaryNode<T> *tr = findNode(key, p->rightChild());
            if (tl || tr) {
                return (tl->depth() > tr->depth()) ? tr : tl;
            } else {
                return NULL;
            }
        }
    } else {
        return NULL;
    }
}

 /* insert a node c into a tree node p as p's leftchild
  * or rightchild. if p has already had a child and then 
  * the old child change into c's rightchild
  */ 
template <typename T> 
void BinaryList<T>::insertNode(BinaryNode<T> &p, LR place, BinaryNode<T> &c) {
    if (place == LEFT) {
        if (p.leftChild() == NULL) {
            *(p.leftChild()) = c;
            *(c.parent()) = p;
            
        } else {
            BinaryNode<T> *tmp = p.leftChild();
            *(p.leftChild()) = c;
            *(c.parent()) = p;
            c.rightChild() = tmp;
        }
    }
    if (place == RIGHT) {
        if (p.rightChild() == NULL) {
            *(p.rightChild()) = c;
            *(c.parent()) = p; 
        } else {
            BinaryNode<T> *tmp = p.rightChild();
            *(p.rightChild()) = c;
            *(c.parent()) = p;
            c.rightChild() = tmp;
        }
    }
}


template <typename T>
void BinaryList<T>::deleteNode(BinaryNode<T> &p, LR place) {
    if (place == LEFT) {
        if (p.leftChild() == NULL) return;
        delete p.leftChild();
        p.leftChild() = NULL;
    }
    if (place == RIGHT) {
        if (p.rightChild() == NULL) return;
        delete p.rightChild();
        p.rightChild() = NULL;
    }
}

/* not recursion , tranverse*/
#include <stack>
#include <deque>
using std::stack;
using std::deque;
template <typename T>
static void gotoHlvfl(stack<BinaryNode<T>*>&);

template <typename T>
void BinaryList<T>::preOrder(void (*visit)(const T &)) {
    stack<BinaryNode<T>*> s;
    BinaryNode<T> *p = _root;
    do {
        if (p) {
            visit(p->getData());
            s.push(p);
            p = p->leftChild();
        } else {
            p = s.top();
            p = p->rightChild();
            s.pop();
            
        }
    } while (!s.empty() && p != NULL);
}

template <typename T>
void BinaryList<T>::inOrder(void (*visit)(const T &)) {
    stack<BinaryNode<T>*> s;
    BinaryNode<T> *p = _root;
    do {
        if (p) {
            s.push(p);
            p = p->leftChild();
        } else {
            p = s.top();
            visit(p->getData());
            s.pop();
            
            p = p->rightChild();
        }
    } while (!s.empty() && p != NULL);
}

template <typename T>
void BinaryList<T>::postOrder(void (*visit)(const T &)) {
    stack<BinaryNode<T>*> s;
    BinaryNode<T> *p = _root;
	s.push(p);
    while (!s.empty()) {
		if (p->parent() != s.top()) {
			gotoHlvfl(s);
		}
        p = s.top();
        visit(p->getData());
        s.pop();
		
	}
}

template <typename T>
static void gotoHlvfl(stack<BinaryNode<T>*> &s) {
	while (BinaryNode<T> *p = s.top()) {
		if (p->leftChild()) {
			if (p->rightChild()) {
				s.push(p->rightChild());
			}
			s.push(p->leftChild());
		} else {
			s.push(p->rightChild());
		}
	}
	s.pop();
}

template <typename T>
void BinaryList<T>::levelOrder(void (*visit)(const T &)) {
    deque<BinaryNode<T>*> q;
    BinaryNode<T>* p = _root;
    q.push_back(p);
    do {
        p = q.front();
        visit(p->getData());
        if (p->leftChild()) {
            q.push_back(p->leftChild());
        }
        if (p->rightChild()) {
            q.push_back(p->rightChild());
        }
        q.pop_front();
    } while (!q.empty() && p != NULL);
}