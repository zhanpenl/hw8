#ifndef SPRAYTREE_H
#define SPRAYTREE_H 

#include "bst.h"
#include <iostream>

template <class KeyType, class ValueType>
class SplayTree : public BinarySearchTree<KeyType, ValueType> {
public:
	Node<KeyType, ValueType>* get(const KeyType& k) {
		Node<KeyType, ValueType>* x = find(k);
		std::cout << "get: key = " << x->getKey() << std::endl; 
		splay(x);
		if ( x->getKey() == k ) return x;
		else return NULL;
	}

	void insert(const KeyType& k, const ValueType& v) {
		Node<KeyType, ValueType>* x = find(k);
		if ( !x ) {
			this->root = new Node<KeyType, ValueType>(k, v, NULL);
			return;
		}
		else if ( x->getKey() == k ) {
			x->setValue(v);
		}
		else {
			Node<KeyType, ValueType>* p = x;
			x = new Node<KeyType, ValueType>(k, v, p);
			if ( k < p->getKey() ) {
				p->setLeft(x);
			}
			else {
				p->setRight(x);
			}
		}
		splay(x);
	}

	void remove(const KeyType& k) {
		Node<KeyType, ValueType>* x = find(k), *p = NULL;

		if ( x->getKey() != k ) {
			return;
		}
		Node<KeyType, ValueType>* s = findSuccessorInChld(x);
		if ( !s ) { // delete itself and splay its parent
			p = x->getParent();
			if ( !p ) this->root = NULL;
			else if ( p->getLeft() == x ) p->setLeft(NULL);
			else p->setRight(NULL);
		}
		else { // swap x and s, splay x's new parent
			swap(s, x);
			p = x->getParent();
			// if the successor is not a leaf node, it has only a child, 
			// which should be linked to x
			Node<KeyType, ValueType>* c = x->getLeft() ? x->getLeft() : x->getRight();
			if ( p->getLeft() == x ) p->setLeft(c);
			else p->setRight(c);
			if ( c ) c->setParent(p);
		}
		delete(x);
		splay(p);
	}

private:
	/**
	*  find the node containing the given key; if not, return the last non-null node
	**/
	Node<KeyType, ValueType>* find(const KeyType& k) {
		Node<KeyType, ValueType> *curr = this->root, *prev = NULL;

	    while (curr) {
			if (curr->getKey() == k) {
				return curr;
			} 
			else if (k < curr->getKey()) {
				prev = curr;
				curr = curr->getLeft();
			} 
			else {
				prev = curr;
				curr = curr->getRight();
			}
		}
		return prev;
	}

	/**
    *  helper to find successor in the children
    **/
    Node<KeyType, ValueType>* 
    findSuccessorInChld(Node<KeyType, ValueType>* node) {
        if ( node->getLeft() == NULL && node->getRight() == NULL ) {
            return NULL;
        }
        else if ( node->getLeft() ) {
            node = node->getLeft();
            while ( node->getRight() ) {
                node = node->getRight();
            }
        }
        else {
            node = node->getRight();
            while ( node->getLeft() ) {
                node = node->getLeft();
            }
        }
        return node;
    }

    /* precondition: x should be deeper than y in the tree */
    void swap(Node<KeyType, ValueType>* x, Node<KeyType, ValueType>* y) {
    	Node<KeyType, ValueType>* px = x->getParent();
    	Node<KeyType, ValueType>* py = y->getParent();

    	// swap parent
    	if ( !py ) {
    		this->root = x;
    	}
    	else {
    		if ( py->getLeft() == y ) py->setLeft(x);
    		else py->setRight(x);
    	}
    	x->setParent(py);
    	if ( px->getLeft() == x ) px->setLeft(y);
    	else px->setRight(y);
    	if ( y == px ) y->setParent(x); // case where x is a child of y
    	else y->setParent(px);

    	// swap children
    	Node<KeyType, ValueType>* lx = x->getLeft();
    	Node<KeyType, ValueType>* rx = x->getRight();
    	Node<KeyType, ValueType>* ly = y->getLeft();
    	Node<KeyType, ValueType>* ry = y->getRight();
    	x->setLeft(ly);
    	if ( ly ) ly->setParent(x);
    	x->setRight(ry);
    	if ( ry ) ry->setParent(x);
    	y->setLeft(lx);
    	if ( lx ) lx->setParent(y);
    	y->setRight(rx);
    	if ( rx ) rx->setParent(y);
    }

	void splay(Node<KeyType, ValueType>* x) {
		if ( !x ) return;
		Node<KeyType, ValueType>* p = x->getParent();
		if ( !p ) return;
		Node<KeyType, ValueType>* gp = p->getParent();

		if ( !gp ) { // p is the root
			if ( p->getLeft() == x ) rotateRight(x);
			else rotateLeft(x);
			return;
		}
		
		if ( gp->getLeft() == p && p->getLeft() == x ) {
			rotateRight(p);
			// std::cout << "splay: rotateRight";
			// this->print();
			// std::cout << std::endl;
			rotateRight(x);
			// std::cout << "splay: rotateRight";
			// this->print();
			// std::cout << std::endl;
		}
		if ( gp->getRight() == p && p->getRight() == x ) {
			rotateLeft(p);
			rotateLeft(x);
		}
		if ( gp->getLeft() == p && p->getRight() == x ) {
			rotateLeft(x);
			rotateRight(x);
		}
		if ( gp->getRight() == p && p->getLeft() == x ) {
			rotateRight(x);
			rotateLeft(x);
		}
		splay(x);
	}

	void rotateRight(Node<KeyType, ValueType>* x) {
		Node<KeyType, ValueType>* p = x->getParent();
		Node<KeyType, ValueType>* gp = p->getParent();
		Node<KeyType, ValueType>* rx = x->getRight();

		if ( !gp ) {
			this->root = x;
			x->setParent(NULL);
		}
		else {
			if ( gp->getLeft() == p ) gp->setLeft(x);
			else gp->setRight(x);
			x->setParent(gp);
		}

		p->setLeft(rx);
		if ( rx ) {
			rx->setParent(p);
		}

		x->setRight(p);
		p->setParent(x);
	}

	void rotateLeft(Node<KeyType, ValueType>* x) {
		Node<KeyType, ValueType>* p = x->getParent();
		Node<KeyType, ValueType>* gp = p->getParent();
		Node<KeyType, ValueType>* lx = x->getLeft();

		// same as rotateRight()
		if ( !gp ) {
			this->root = x;
			x->setParent(NULL);
		}
		else {
			if ( gp->getLeft() == p ) gp->setLeft(x);
			else gp->setRight(x);
			x->setParent(gp);
		}

		p->setRight(lx);
		if ( lx ) {
			lx->setParent(p);
		}

		x->setLeft(p);
		p->setParent(x);
	}
};

#endif
