using namespace std;

template <class T>
AVL<T>* AVL<T>::search(const T &v) {
    if(this->getValue() == v) {return this;}
    else if(this->getValue() < v) {
        if (this->getRight() == NULL) {
            return NULL;
        }else {
            AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
            return right->search(v);
        }
    }else if(this->getValue() > v) {
        if(this->getLeft() == NULL) {
            return NULL;
        }else {
            AVL<T>* left = dynamic_cast<AVL<T>*>(this->getLeft());
            return left->search(v);
	}
    }
}

template <class T>
AVL<T> * AVL<T>::balance() {
    AVL<T>* parent;
    AVL<T>* curr = this;
    
    do {
	parent = dynamic_cast<AVL<T>*>(curr->getParent());
	curr->updateHeight();
	int hDiff = curr->heightDifference();
	
	if (hDiff < -1) {
	    AVL<T>* left = dynamic_cast<AVL<T>*>(curr->getLeft());
	    if(left->heightDifference() > 1) {
		left->leftRotate();
	    }
	    curr->rightRotate();
	}else if (hDiff > 1) {
	    AVL<T>* right = dynamic_cast<AVL<T>*>(curr->getRight());
	    if(right->heightDifference() < -1) {
		right->rightRotate();
	    }
	    curr->leftRotate();
	}
	if(parent != NULL) {
	    curr = parent;
	}
	
    }while(parent != NULL);
    return curr->getRoot();

}

template <class T>
AVL<T> * AVL<T>::insert(const T &v) {
    if (this->getValue() == v) {
	return this->balance();
    }else if (this->getValue() < v) {
	if (this->getRight() == NULL) {
	    AVL<T> * right = new AVL<T>(v, NULL, NULL, this);
	    this->setRight(right);
	    return this->balance();
	}else {
	    AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
	    return right->insert(v);
	}
    }else {
	if (this->getLeft() == NULL) {
	    AVL<T> * left = new AVL<T>(v, NULL, NULL, this);
	    this->setLeft(left);
	    left->setParent(this);
	    return this->balance();
	}else {
	    AVL<T>* left = dynamic_cast<AVL<T>*>(this->getLeft());
	    return left->insert(v);
	}
    }
}

template <class T>
AVL<T> * AVL<T>::remove(const T &v) {
    if(this->getValue() == v) {

        if(this->getParent() == NULL) {
            if(this->getLeft() == NULL && this->getRight() != NULL) {
                AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
                right->setParent(NULL);
                delete this;
                return right->balance();
            }else if(this->getLeft() != NULL && this->getRight() == NULL) {
                AVL<T>* left = dynamic_cast<AVL<T>*>(this->getLeft());
                left->setParent(NULL);
                delete this;
                return left->balance();
            }else if(this->getLeft() == NULL && this->getRight() == NULL) {
                return NULL;
            }else {
                AVL<T>* successor = dynamic_cast<AVL<T>*>(this->successor());
                T val = successor->getValue();
                this->setValue(val);
                AVL<T>* sParent = dynamic_cast<AVL<T>*>(successor->getParent());
                AVL<T>* sRight = dynamic_cast<AVL<T>*>(successor->getRight());
                if (sParent->getLeft() == successor) {
                    sParent->setLeft(sRight);
                }else {
                    sParent->setRight(sRight);
                }
                if(sRight != NULL) {
                    sRight->setParent(sParent);
                }
                delete successor;
                return this->balance();
            }

        }else {
            AVL<T>* parent = dynamic_cast<AVL<T>*>(this->getParent());

            if(this->getLeft() == NULL && this->getRight() == NULL) {
                if(parent->getLeft() == this) {
                    delete this;
                    parent->setLeft(NULL);
                    return parent->balance();
                }else {
                    delete this; 
                    parent->setRight(NULL);
                    return parent->balance();
                }
            }else if(this->getLeft() == NULL && this->getRight() != NULL) {
                 if(parent->getLeft() == this) {
                    AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
                    right->setParent(parent);
                    parent->setLeft(right);
                    delete this;
                    return parent->balance();
                }else {
                    AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
                    right->setParent(parent);
                    parent->setRight(right);
                    delete this;
                    return parent->balance();
                }
            }else if(this->getLeft() != NULL && this->getRight() == NULL) {
                if(parent->getLeft() == this) {
                    parent->setLeft(this->getLeft());
                    delete this;
                    AVL<T>* left = dynamic_cast<AVL<T>*>(parent->getLeft());
                    left->setParent(parent);
                    return parent->balance();
                }else {
                    parent->setRight(this->getLeft());
                    delete this;
                    AVL<T>* left = dynamic_cast<AVL<T>*>(parent->getRight());
                    left->setParent(parent);
                    return parent->balance();
                }
            }else {
                AVL<T>* successor = dynamic_cast<AVL<T>*>(this->successor());
                if (successor == NULL) {
                    if(parent->getRight() == this) { parent->setRight(NULL); }
                    else { parent->setLeft(NULL); }
                    delete this;
                    return parent->balance();
                }
                T val = successor->getValue();
                this->setValue(val);
                AVL<T>* sParent = dynamic_cast<AVL<T>*>(successor->getParent());
                AVL<T>* sRight = dynamic_cast<AVL<T>*>(successor->getRight());
                if (sParent->getLeft() == successor) {
                    sParent->setLeft(sRight);
                }else {
                    sParent->setRight(sRight);
                }
                if(sRight != NULL) {
                    sRight->setParent(sParent);
                }
                delete successor;
                return parent->balance();
            }
        }
    }else {
        if (v < this->getValue()) {
            AVL<T>* left = dynamic_cast<AVL<T>*>(this->getLeft());
            return left->remove(v);
        }else {
            AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
            return right->remove(v);
        }
    }
}


template <class T>
int AVL<T>::heightDifference() {
        AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
        AVL<T>* left = dynamic_cast<AVL<T>*>(this->getLeft());
        int rHeight, lHeight;
        if(left == NULL) { lHeight = 0; }
        else { lHeight = left->getHeight(); }
        if(right == NULL) { rHeight = 0; }
        else { rHeight = right->getHeight(); }
        return rHeight - lHeight;
}

/*template <class T>
void AVL<T>::rightRotate(){
    AVL<T>* left = dynamic_cast<AVL<T>*>(this->getLeft());
    AVL<T>* parent = dynamic_cast<AVL<T>*>(this->getParent());
    AVL<T>* lsRight = dynamic_cast<AVL<T>*>(left->getRight());

    left->setParent(parent);
    left->setRight(this);
    this->setParent(left);
    this->setLeft(lsRight);

    if(parent != NULL){
	if(parent->getLeft() == this)
	    parent->setLeft(left);
	else
	    parent->setRight(left);
    }
}

template <class T>
void AVL<T>::leftRotate(){
    AVL<T>* right = dynamic_cast<AVL<T>*>(this->getRight());
    AVL<T>* parent = dynamic_cast<AVL<T>*>(this->getParent());
    AVL<T>* rsLeft = dynamic_cast<AVL<T>*>(right->getLeft());

    right->setParent(parent);
    right->setLeft(this);
    this->setParent(right);
    this->setRight(rsLeft);

    if(parent != NULL){
	if(parent->getLeft() == this)
	    parent->setLeft(right);
	else
	    parent->setRight(right);
    }
}*/
template <class T>
AVL<T> * AVL<T>::getRoot() {

    AVL<T>* parent = dynamic_cast<AVL<T>*>(this->getParent());
    if(parent != NULL) {

        return parent->getRoot();
    }else {

        return this;
    }
}
