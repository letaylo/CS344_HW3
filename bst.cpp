using namespace std;

template <class T>
BST<T> * BST<T>::insert(const T &v) {
    if(this->getValue() < v) {
	if(this->getRight() == NULL) {
	    this->setRight(new BST<T>(v, NULL, NULL, this));
	} else {
	    BST<T>* right = dynamic_cast<BST<T>*>(this->getRight());
	    this->setRight(right->insert(v));
	}
    }else if(this->getValue() > v) {
	if(this->getLeft() == NULL) {
	    this->setLeft(new BST<T>(v, NULL, NULL, this));
	} else {
	    BST<T>* left = dynamic_cast<BST<T>*>(this->getLeft());
	    this->setLeft(left->insert(v));
	}
    }else if(this->getValue() == NULL) {
	this->setValue(v);
    }
    return this;

}

template <class T>
BST<T>* BST<T>::search(const T &v) {
    if(this->getValue() == v) {return this;}
    else if(this->getValue() < v) {
	if (this->getRight() == NULL) {
	    return NULL;
	}else {
	    BST<T>* right = dynamic_cast<BST<T>*>(this->getRight());
	    return right->search(v);
	}
    }else if(this->getValue() > v) {
	if(this->getLeft() == NULL) {
	    return NULL;
	}else {
	    BST<T>* left = dynamic_cast<BST<T>*>(this->getLeft());
	    return left->search(v);
	}
    }
}

template <class T>
BST<T>* BST<T>::remove(const T &v) {
    if(this->getValue() == v) {
	//If Root
	if(this->getParent() == NULL) {
	    if(this->getLeft() == NULL && this->getRight() != NULL) {
		BST<T>* right = dynamic_cast<BST<T>*>(this->getRight());
		right->setParent(NULL);
		delete this;
		return right;
	    }else if(this->getLeft() != NULL && this->getRight() == NULL) {
		BST<T>* left = dynamic_cast<BST<T>*>(this->getLeft());
		left->setParent(NULL);
		delete this;
		return left;
	    }else if(this->getLeft() == NULL && this->getRight() == NULL) {
		return NULL;
	    }else {
		BST<T>* successor = dynamic_cast<BST<T>*>(this->successor());	
		T val = successor->getValue();
		this->setValue(val);
		BST<T>* sParent = dynamic_cast<BST<T>*>(successor->getParent());
		BST<T>* sRight = dynamic_cast<BST<T>*>(successor->getRight());
		if (sParent->getLeft() == successor) {
		    sParent->setLeft(sRight);
		}else {
		    sParent->setRight(sRight);
		}
		if(sRight != NULL) {
		    sRight->setParent(sParent);
		}
		delete successor;
		return this;
	    }
	//Not Root
	}else {
	    BST<T>* parent = dynamic_cast<BST<T>*>(this->getParent());
	    //BST<T>* pleft = dynamic_cast<BST<T>*>(parent->getLeft());
            if(this->getLeft() == NULL && this->getRight() == NULL) {
		if(parent->getLeft() == this) {
		    delete this;
		    parent->setLeft(NULL);
		    return parent->getRoot();
		}else {
		    delete this;
		    parent->setRight(NULL);
		    return parent->getRoot();
		}
	    }else if(this->getLeft() == NULL && this->getRight() != NULL) {
		 if(parent->getLeft() == this) {
		    BST<T>* right = dynamic_cast<BST<T>*>(this->getRight());
		    right->setParent(parent);
		    parent->setLeft(right);
		    delete this;
		    return parent->getRoot();
                }else {
		    BST<T>* right = dynamic_cast<BST<T>*>(this->getRight());
                    right->setParent(parent);
		    parent->setRight(right);
		    delete this;
		    return parent->getRoot();
                }
	    }else if(this->getLeft() != NULL && this->getRight() == NULL) {
		if(parent->getLeft() == this) {
                    parent->setLeft(this->getLeft());
                    delete this;
		    BST<T>* left = dynamic_cast<BST<T>*>(parent->getLeft());
                    left->setParent(parent);
		    return parent->getRoot();
                }else {
                    parent->setRight(this->getLeft());
                    delete this;
		    BST<T>* left = dynamic_cast<BST<T>*>(parent->getRight());
                    left->setParent(parent);
		    return parent->getRoot();
                }
	    }else {
		BST<T>* successor = dynamic_cast<BST<T>*>(this->successor());
		if (successor == NULL) {
		    if(parent->getRight() == this) { parent->setRight(NULL); }
		    else { parent->setLeft(NULL); }
		    delete this;
		    return parent->getRoot();
		}
                T val = successor->getValue();    
                this->setValue(val);
		BST<T>* sParent = dynamic_cast<BST<T>*>(successor->getParent());
                BST<T>* sRight = dynamic_cast<BST<T>*>(successor->getRight());
                if (sParent->getLeft() == successor) {
                    sParent->setLeft(sRight);
                }else {
                    sParent->setRight(sRight);
                }
                if(sRight != NULL) {
                    sRight->setParent(sParent);
                }
                delete successor;
                return parent->getRoot();
	    }
	}
    }else { 
	if (v < this->getValue()) {
	    BST<T>* left = dynamic_cast<BST<T>*>(this->getLeft());
	    return left->remove(v);
	}else {
	    BST<T>* right = dynamic_cast<BST<T>*>(this->getRight());
	    return right->remove(v);
	}
    }
}

template <class T>
BST<T> * BST<T>::getRoot() {

    BST<T>* parent = dynamic_cast<BST<T>*>(this->getParent());
    if(parent != NULL) {

        return parent->getRoot();
    }else {

        return this;
    }
}

