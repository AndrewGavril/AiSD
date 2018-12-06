#include <iostream>

/*
 * Template class of avl tree
 */
template <typename T>
class AVL{
	T value;
	AVL *left;
	AVL *right;
	short height;
	AVL *rotate_right();
	AVL *rotate_left();
	int bfactor();
	AVL *find_min();
	AVL *remove_min();
	public:
	AVL(){
		left=nullptr;
		right=nullptr;
	};
	AVL(T elem);
	~AVL(){
		delete left;
		delete right;
	};
	short get_height();
	AVL *del_elem(T elem, int (*cmp)(T el1, T el2));
	void upd_height();
	AVL *balance();
	AVL *insert(T elem, int (*cmp)(T el1,T el2));
	void print(AVL<T> *root, int pad);
};

/*
 * Constructor for given element
 */
template <typename T>
AVL<T>:: AVL(T elem){
	value = elem;
	left = nullptr;
	right = nullptr;
	height = 1;
}

/*
 * Method for getting height of the tree
 */
template <typename T>
short AVL<T>::get_height(){
	return height;
}

/*
 * Method for getting the difference between left and right subtrees
 */
template <typename T>
int AVL<T>::bfactor(){
	if(left==nullptr && right==nullptr)
		return 0;
	if(left ==nullptr)
		return -right->height;
	if(right == nullptr)
		return left->height;
	else
		return left->height-right->height;
}

/*
 *Method for updating the values of height of the tree and subtrees.
 */
template <typename T>
void AVL<T>::upd_height(){
	short l=0, r=0;
	if(left!=nullptr){
		left->upd_height(); 	//updating left subtree
		l=left->height;		//getting the height of the left subtree
	}
	if(right!=nullptr){
		right->upd_height();	//updating right subtree
		r=right->height;	//getting the height of the right subtree
	}
	height = (l > r?l:r)+1;		//changing the height for greatest between left and right
}

//Methof wich rotates the tree to the right
template <typename T>
AVL<T>* AVL<T>::rotate_right(){
	AVL *ptr = left;	//new root of the tree
	left = ptr->right;
	ptr->right = this;
	ptr->upd_height();
	return ptr;
}

//Method wich rotates the tree to the left
template <typename T>
AVL<T>* AVL<T>::rotate_left(){
	AVL *ptr = right;	//new root of the tree
	right = ptr->left;	
	ptr->left = this;
	ptr->upd_height();
	return ptr;
}

/*
 * This method makes the tree balanced. It rotates it left if the difference between
 * left subtree and right subtree is 2 or -2.
 */
template <typename T>
AVL<T>* AVL<T>::balance(){
	if(bfactor()==2){
		if(left->bfactor()<0)
			left=left->rotate_left();
		return rotate_right();
	}
	if(bfactor()==-2){
		if(right->bfactor()>0)
			right=right->rotate_right();
		return rotate_left();
	}
	return this;
}


template <typename T>
AVL<T>* AVL<T>::insert(T elem, int (*cmp)(T el1, T el2)){
	if(cmp(elem,value)>0){			//if element is bigger than the root
		if(right==nullptr){		//if it is the position of the new element
			right=new AVL<T>(elem);
			upd_height();		//updating the height of the tree after inserting
		}
		else{				//continue the searching the position of this element
			right=right->insert(elem, cmp);	
			upd_height();
		}
	}
	if(cmp(elem,value)<0){			//if element is smaller than the root
		if(left==nullptr){
			left=new AVL<T>(elem);
			upd_height();
		}
		else{
			left= left->insert(elem, cmp);
			upd_height();
		}
	}
		return balance();
}

//Method for finding the smallest element
template <typename T>
AVL<T> *AVL<T>::find_min(){
	if(left==nullptr)
		return this;
	else
		return left->find_min();
}

template <typename T>
AVL<T> *AVL<T>::remove_min(){		//Method removes the element from the tree
	if(left==nullptr){		//but not from the memmory
		return right;
	}
	else{
	       left=left->remove_min();
	       upd_height();
	       return balance();
	}
}

/*
 * Method wich serching the element in the tree and deletes it from the
 * tree and from the memmory
 */
template <typename T>
AVL<T> *AVL<T>::del_elem(T elem, int (*cmp)(T el1, T el2)){
	if(cmp(elem,value)>0){					//Serching the element
		if(right!=nullptr){			
			right=right->del_elem(elem, cmp);
			upd_height();
		}
		else{
			std::cout<<"Element does not exist!\n";
		}
	}
	if(cmp(elem, value)<0){
		if(left!=nullptr){
			left=left->del_elem(elem, cmp);
			upd_height();
		}
		else{
			std::cout<<"Element does not exist!\n";
		}
	}
	if(cmp(elem, value)==0){			//if we find the element
		AVL<T> *bst=left;
		AVL<T> *r=right;
		left=nullptr;
		right=nullptr;
		delete this;
		if(r==nullptr)
			return bst;
		AVL<T> *min=r->find_min();
		min->right=r->remove_min();
		min->left=bst;
		min->upd_height();
		return min->balance();
	}
	return balance();
}

//Method wich printing the tree
template <typename T>
void AVL<T>::print(AVL<T> *root, int pad){
	int i=0;
	if (root != nullptr)
	{
		print(root->left, pad + 3);
		for (int i = 0;i < pad;i++)
		{
			std::cout << "   ";
		} 
		std::cout<< root->value<<"("<<pad/3<<")"<<std::endl;
		print(root->right, pad + 3);
	}
}
