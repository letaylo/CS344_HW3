using namespace std;

template <class T>
void Splay<T>::splay() {
    Splay<T>* parent = dynamic_cast<Splay<T>*>(this->getParent());
    if(parent != NULL) {
	if(this == parent->getLeft()) {
	    parent->rightRotate();
	}else {
	    parent->leftRotate();
	}
	//cout << "Splay?" << endl;
	this->splay();
    }
    //cout << "SplayComplete?" << endl;
}

template <class T>
Splay<T> * Splay<T>::getRoot() {
    //cout << "getRootInitialize" << endl;
    Splay<T>* parent = dynamic_cast<Splay<T>*>(this->getParent());
    if(parent != NULL) {
	//cout << "getRoot?" << endl;
	return parent->getRoot();
    }else {
	//cout << "getRootComplete?" << endl;
	return this;
    }
}

template <class T>
Splay<T> * Splay<T>::search(const T &v) {
    if(this->getValue() == v) {
 	this->splay();
	//cout << "SearchComplete?" << endl;
	return this->getRoot();
    }else if(this->getValue() > v) {
	Splay<T>* left = dynamic_cast<Splay<T>*>(this->getLeft());
	//cout << "Search?" << endl;
	return left->search(v);
    }else if(this->getValue() < v) {
	Splay<T>* right = dynamic_cast<Splay<T>*>(this->getRight());
	//cout << "Search?" << endl;
	return right->search(v);
    }else {
	cerr << "Value not found" << endl;
    }
}

template <class T>
Splay<T> * Splay<T>::insert(const T &v) {
    if(this->getValue() > v) {
	if(this->getLeft() == NULL) {
	    Splay<T>* left = new Splay<T>(v);
            this->setLeft(left);
            left->setParent(this);
	    left->splay();
	    //cout << "LInsertComplete?" << endl;
	    return this->getRoot();
	}else {
	    Splay<T>* left = dynamic_cast<Splay<T>*>(this->getLeft());
	    //cout << "LInsert?" << endl;
	    return left->insert(v);
	}
    }else if(this->getValue() < v) {
	 if(this->getRight() == NULL) {
            Splay<T>* right = new Splay<T>(v);
	    this->setRight(right);
	    right->setParent(this);
            right->splay();
	    //cout << "RInsertComplete?" << endl;
            return this->getRoot();
        }else {
            Splay<T>* right = dynamic_cast<Splay<T>*>(this->getRight());
	    //cout << "RInsert?" << endl;
            return right->insert(v);
        }
    }else {
	cerr << "Something went wrong!" << endl;
    }
}

template <class T>
Splay<T> * Splay<T>::remove(const T &v) {
    if(this->getValue() > v) {
        if(this->getLeft() == NULL) {
            cerr << "Value not found!" << endl;
        }else {
            Splay<T>* left = dynamic_cast<Splay<T>*>(this->getLeft());
	    //cout << "LRemove?" << endl;
            return left->remove(v);
        }
    }else if(this->getValue() < v) {
         if(this->getRight() == NULL) {
            cerr << "Value not found!" << endl;
        }else {
            Splay<T>* right = dynamic_cast<Splay<T>*>(this->getRight());
	    //cout << "RRemove?" << endl;
            return right->remove(v);
        }
    }else if(this->getValue() == v) {
	this->splay();
	if(this->successor() != NULL) {
	    Splay<T>* left = dynamic_cast<Splay<T>*>(this->successor());
	    Splay<T>* next = dynamic_cast<Splay<T>*>(this->successor());
	    Splay<T>* nParent = dynamic_cast<Splay<T>*>(next->getParent());
	    Splay<T>* nRight = dynamic_cast<Splay<T>*>(next->getRight());
	    T val = next->getValue();
	    this->setValue(val);
	    if(nParent->getLeft() == next) {
	        nParent->setLeft(nRight);
	    }else {
		nParent->setRight(nRight);
	    }
	    if(nRight != NULL) {nRight->setParent(nParent);}
	    delete next;
	    //this->splay();
	    //cout << "RemoveComplete?" << endl;
	    return this->getRoot();
	}else if(this->getLeft() != NULL) {
	    //this->splay
	    Splay<T>* left = dynamic_cast<Splay<T>*>(this->getLeft());
	    Splay<T>* parent = dynamic_cast<Splay<T>*>(this->getParent());
	    if(parent == NULL) {
		return left;
	    }
	    left->setParent(parent);
	    if(parent->getLeft() == this) {
		parent->setLeft(left);
		//cout << "RemoveComplete?" << endl;
		return left->getRoot();
	    }else if(parent->getRight() == this) {
		parent->setRight(left);
		//cout << "RemoveComplete?" << endl;
		return left->getRoot();
	    }else {
		cerr << "Uh-oh!" << endl;
	    }
	}else {
	    return NULL;
	}	
    }else {
        cerr << "Something went wrong!" << endl;
    }
}



