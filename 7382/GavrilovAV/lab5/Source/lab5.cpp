#include <iostream>
#include "./avl.cpp"
#include <string>
#include <fstream>
#define TEST
//#define ADD_LOG

int cmp(int el1, int el2){	//Function-comparator fot int elements
	return el1-el2;
}

/*Function wich checking the string for existence only
 * cpace cymbols and digits. If it is correct return true
 * otherwise false.*/
bool check_str(std::string &str){
#ifdef TEST
	std::cout<<"Checking string...\n";
#endif
	for(int i=0;i<str.length()-1;i++){			//checking every symbol in string
		if(isdigit(str[i]) || str[i]=='-')
			continue;
		if(str[i]==' '){
			if(i!=(str.length()-1) && str[i+1]==' '){
				str.erase(i,1);			//deleting extra space charachters
				i--;
			}
			continue;
		}
		else{
#ifdef TEST
			std::cout<<"String is wrong!\n";
#endif
			return false;
		}
	}
	if(str[0]==' ')
		str.erase(0,1);			//deleting space charachter if it is in the beginning of the string
#ifdef TEST
	std::cout<<"String is correct!\n";
#endif
	return true;
}

/*
 * Function wich creates the avl tree by inserting elements to it.
 * Returns the pointer to the root of the tree.
 */
AVL<int> *create_bst(std::string str){
	std::string substr;
	int index=str.find(' ');		//finding the end of the first element
	int pos=index, flag=0;			//and creating the root of the tree
	substr=str.substr(0,index);
	AVL<int>* bst=new AVL<int>(stoi(substr));
	for(int i=index;i<str.length();i++){		//cycle for getting the element from the string
		if(isdigit(str[i]) || str[i]=='-'){
			if(flag==0)		//if it is the first digit of a number
				pos=i;
			flag=1;
		}
		else{
			if(flag==1){		//if it is the last digit of a number
				index=i;
#ifdef ADD_LOG
				std::cout<<"Inserting: "<<str.substr(pos,index-pos)<<"\nWas:\n";
				bst->print(bst,0);std::cout<<std::endl;
#endif
				bst=bst->insert(stoi(str.substr(pos,index-pos)),cmp);
#ifdef ADD_LOG
				std::cout<<"Now:\n";
				bst->print(bst,0);std::cout<<std::endl;
#endif
			}
			flag=0;
		}
		if(flag==1 && i==(str.length()-1)){	//if it is the last element in the string
#ifdef ADD_LOG						//and there is no any space charachters
			std::cout<<"Insrting: "<<str.substr(pos)<<"\nWas:\n"; //after it
			bst->print(bst,0);std::cout<<std::endl;
#endif
			bst=bst->insert(stoi(str.substr(pos)),cmp);
#ifdef ADD_LOG
			std::cout<<"Now:\n";
			bst->print(bst,0);std::cout<<std::endl;
#endif
		}
	}
	return bst;
}

int main(){
	AVL<int> *bst=nullptr;
	while(true){		//cycle for the programm menu
#if !defined TEST
		std::cout<<"Choose the operation(write the number of operation):\n"
			<<"1:Create tree from the file\n"
			<<"2:Insert element to the tree\n"
			<<"3:Delete element from the tree\n"
			<<"4:Print the tree\n"
			<<"5:Close program\n"
			<<"Enter the operation: ";
#endif
		int operation=1;
		std::cin>>operation;
		switch(operation){
			case 1:
				{
#if !defined TEST
				std::cout<<"----\nWarning: file should contain only integers or space characters!\n All symbols must be in one line.\n"
					<<"The name of file must contain the full path to it!\n----\n"
					<<"Enter file name:";
#endif
				std::string fname;
				char str[500];
				std::cin>>fname;
				std::ifstream file;
				file.open(fname, std::ifstream::in);
				if(file.is_open()){
					file.getline(str,500);
					file.close();
					std::string input(str);
					if(check_str(input))
						bst=create_bst(input);
					else
						std::cout<<"Wrong input data!\n";
				}
				else{
					std::cout<<"Wrong file name!\n";
				}
				break;
				}
			case 2:
				{
				if(bst!=nullptr){
					int el;
					std::cout<<"Enter the element:";
					std::cin>>el;
#ifdef ADD_LOG
					std::cout<<"Before insrting:\n";
					bst->print(bst,0);
#endif
					bst=bst->insert(el,cmp);
#ifdef ADD_LOG
					std::cout<<"After inserting:\n";
					bst->print(bst,0);
#endif
				}
				else{
					std::cout<<"Error: tree is empty!\n";
				}
				break;
				}
			case 3:
				{
				if(bst!=nullptr){
                                	int el;
					std::cout<<"Enter the element:";
                                	std::cin>>el;
#ifdef ADD_LOG
                                	std::cout<<"Before deleting:\n";
                                	bst->print(bst,0);
#endif
		      			bst=bst->del_elem(el,cmp);
#ifdef ADD_LOG
        	                        std::cout<<"After deleting:\n";
		      			bst->print(bst,0);
#endif
				}
				else{
					std::cout<<"Error: tree is empty!\n";
				}
				break;
				}
			case 4:
				{
				if(bst!=nullptr){
					std::cout<<"AVL Tree:\n";
					bst->print(bst, 0);
				}
				else{
					std::cout<<"Error: tree is empty!\n";
				}
				break;
				}
			case 5:
				{
				std::cout<<"Good luck, bye!"<<std::endl;
				delete bst;
				return 0;
				break;
				}
			default:
				std::cout<<"Unknown command!\n";
				break;
		}
		std::cout<<std::endl<<std::endl;
	}
}
