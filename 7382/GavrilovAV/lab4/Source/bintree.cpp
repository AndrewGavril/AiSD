#include <iostream>
//Template class for binary tree for everu standart type of veriable
int findSnd(std::string str);
template <typename T>
class BinTree{
	private:
	bool isEmpty;
	BinTree *left;
	BinTree *right;
	T value;
	public:
	BinTree();
	BinTree(std::string, T (*stringtoT)(std::string str));
	~BinTree();
	int findElNum(T elem);
	int findMinLength(T elem, int depth);
};
//Standart constructor
template <typename T>
BinTree<T>::BinTree(){
	left=nullptr;
	right=nullptr;
	isEmpty=true;
}
//Constructor which makes the binary tree from the string
template <typename T>
BinTree<T>::BinTree(std::string str, T (*stringtoT) (std::string)){
	if(str=="!"){
		left=nullptr;
		right=nullptr;
		isEmpty=true;
	}
	else{
		int pos;
		isEmpty=false;
		str.erase(0,1);
		if(str.find('!')<str.find('('))
			pos=str.find('!');
		else
			pos=str.find('(');
		value=stringtoT(str.substr(0,pos));
		str=str.substr(pos, str.length()-2);
                if(str[0]=='!'){
                        pos=1;
                }
                else{
                        pos=findSnd(str);
                }
                std::string fstBT=str.substr(0, pos);
                std::string sndBT=str.substr(pos, str.length()-1);
		left=new BinTree(fstBT, stringtoT);
		right=new BinTree(sndBT, stringtoT);
	}	
}
//Standart destructror
template <typename T>
BinTree<T>::~BinTree(){
	delete left;
	delete right;
}
//findElNum find the number of search element in binary tree
template <typename T>
int BinTree<T>::findElNum(T elem){
	if(isEmpty==true){
		return 0;
	}
	else{
		int res=0;
		if(value==elem){
			res++;
		}
		res+=left->findElNum(elem);
		res+=right->findElNum(elem);
		return res;
	}
}

template <typename T>
//findMinLength find the minimal depth of the search element
int BinTree<T>:: findMinLength(T elem, int depth){
	if(isEmpty==true){
                return -1;
        }
        else{

		if(elem == value){
			return depth;
		}
                int leftMin=left->findMinLength(elem, depth+1);
                int rightMin=right->findMinLength(elem, depth+1);
                if(leftMin<rightMin){
			if(leftMin<0)
				return rightMin;
			else
				return leftMin;
		}
		if(rightMin<leftMin){
			if(rightMin<0){
				return leftMin;
			}
			else
				return rightMin;
		}
		return leftMin;
        }

}
