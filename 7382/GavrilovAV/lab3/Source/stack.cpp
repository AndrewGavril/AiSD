#include <iostream>
//#define TEST
//Stack class for the char elements
class Stack{
	char *arr;
	int elNum;
	size_t size;
	public:
	//Standart constructor
	Stack(){
		arr=nullptr;
		elNum=0;
		size=0;
	}
	//Constructor which makes a stack of s elemenst
	Stack(size_t s){
		arr= new char[s];
		size=s;
		elNum =0;
	}
	//Standart destructor
	~Stack(){
		delete[] arr;
	}
	void push(char el){	//This function pushs element to stack
#ifdef TEST	
		std::cout<<"\tPush element: "<<el<<std::endl;
#endif	
		if(elNum<size){
			arr[elNum]=el;
			elNum++;
		}
		else{
			std::cout<<"Error: stack is full!"<<std::endl;
			exit(1);
		}
	}
	//This function gets top element from the stack and deletes it
	//from the stack
	char pop(){
		if(!this->isEmpty()){
			char el=arr[elNum-1];
			arr[elNum-1]='\0';
			elNum--;
#ifdef TEST
			std::cout<<"Pop element: \'"<<el<<"\'"<<std::endl;
#endif
			return el;
		}
		else{
			std::cout<<"Error: stack is empty!"<<std::endl;
			return '\0';
		}
	}
	bool isEmpty(){	//This function checks stack for emptiness
		if(elNum == 0)
			return true;
		else
			return false;
	}
	int count(){	//This function return number of element in the stack
		return elNum;
	}
	char topElem(){		//This function returns top element in the stack
		if(!this->isEmpty()){	//without deleting
			return arr[elNum-1];
		}
		else{
			return '\0';
		}
	}
};
