/* methods for Tree class */

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


// (re)compute height 
template <class T>
void Tree<T>::updateHeight()
{
	if (left == NULL && right == NULL) 
	{
		height = 0;
	}
	else if (left == NULL) 
	{
		right->updateHeight();
		height = 1 + right->height;
	}
	else if (right == NULL) 
	{
		left->updateHeight();
		height = 1 + left->height;
	}
	else 
	{
		left->updateHeight();
		right->updateHeight();
		height = 1 + max(left->height,right->height);
	}
}

// returns successor ("smallest" item in right subtree)
template <class T>
Tree<T> * Tree<T>::successor() const
{
	Tree<T> * next;

	if (right == NULL)
	{
		return NULL;
	}

	next = right;
	while (next->left != NULL)
	{
		next = next->left;
	}
	return next;
}

// compute inorder traversal sequence 
template <class T>
void Tree<T>::inOrder( vector<T> &sequence ) const
{
	if (left != NULL)
	{
		left->inOrder( sequence );
	}

	sequence.push_back(value);

	if (right != NULL)
	{
		right->inOrder( sequence );
	}
}


// simple tree printer
template <class T>
void Tree<T>::show( int spaces, int side ) const
{
	for (int i = 0; i < spaces; i++)
	{
		cerr << " ";
	}

	if (side < 0) 
	{
		cerr << "<" << value << "]" << endl;
	}
	else if (side > 0) 
	{
		cerr << "[" << value << ">" << endl;
	}
	else 
	{
		cerr << "[" << value << "]" << endl;
	}

	if (left != NULL)
	{
		left->show( spaces+4, -1 );
	}

	if (right != NULL)
	{
		right->show( spaces+4, +1 );
	}

}


// inline max
inline int max(int a, int b)
{
    return (a > b ? a : b);
}



template <class T>
void Tree<T>::rightRotate(){
    Tree<T>* left = dynamic_cast<Tree<T>*>(this->getLeft());
    Tree<T>* parent = dynamic_cast<Tree<T>*>(this->getParent());
    Tree<T>* lsRight = dynamic_cast<Tree<T>*>(left->getRight());

    left->setParent(parent);
    left->setRight(this);
    this->setParent(left);
    //cout << "Here?" << endl;
    //if(lsRight != NULL) {
    this->setLeft(lsRight);
    if(lsRight != NULL) {
    	lsRight->setParent(this);
    }
    if(parent != NULL){
	//cout << "NonNullParent";
        if(parent->getLeft() == this)
            parent->setLeft(left);
        else
            parent->setRight(left);
    }
    //cout << "RRotate?" << endl;
}

template <class T>
void Tree<T>::leftRotate(){
    Tree<T>* right = dynamic_cast<Tree<T>*>(this->getRight());
    Tree<T>* parent = dynamic_cast<Tree<T>*>(this->getParent());
    Tree<T>* rsLeft = dynamic_cast<Tree<T>*>(right->getLeft());

    right->setParent(parent);
    right->setLeft(this);
    this->setParent(right);
    //if(rsLeft != NULL) {
    this->setRight(rsLeft);
    if ( rsLeft != NULL ) {
	rsLeft->setParent(this);
    }
    if(parent != NULL){
	//cout << "NonNullParent";
        if(parent->getLeft() == this)
            parent->setLeft(right);
        else
            parent->setRight(right);
    }
    //cout << "LRotate?" << endl;
}

/*template <class T>
Tree<T> * Tree<T>::getRoot() {

    Tree<T>* parent = dynamic_cast<Tree<T>*>(this->getParent());
    if(parent != NULL) {

        return parent->getRoot();
    }else {

        return this;
    }
}*/
