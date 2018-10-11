#include <iostream>
#include "./bintree.cpp"
//#define TEST
/*
 * This function converts string to char for our tasks
 */
char stringtoT(std::string str){
	return str[0];
}
/*findSnd find the end of sequence of brackets and begining of the
 * second sequencce.
 */
int findSnd(std::string str){
	unsigned int index=0;
	unsigned int numOp=0;
        unsigned int numCl=0;
	do{
		if(str[index]=='('){
			numOp++;
		}
		if(str[index]==')'){
			numCl++;
		}
		index++;
 	}while(index<str.length() && numOp!=numCl);
	if(numOp==numCl)
		return index;
	else
		return -1;
}
/*
 * isBinTree checks the string for the corectness. If it is coorect returns true
 * otherwise false.
 */
bool isBinTree(std::string str){
#ifdef TEST
	std::cout<<"Checking string: \""<<str<<"\""<<std::endl;
#endif
	if(str==""){
#ifdef TEST
		std::cout<<"String: \""<<str<<"\" is wrong!"<<std::endl;
#endif
		return false;
	}
	if(str=="!"){
#ifdef TEST
		std::cout<<"String: \""<<str<<"\" is correct!"<<std::endl;
#endif
		return true;
	}
	if(str[0]!='('){
#ifdef TEST
		std::cout<<"String: \""<<str<<"\" is wrong!"<<std::endl;
#endif
		return false;
	}
	if(str[1]!='('){
		if(str.length()<5){
#ifdef TEST
			std::cout<<"String: \""<<str<<"\" is wrong!"<<std::endl;
#endif
			return false;
		}
		std::string br=str.substr(2, str.length()-3);
		int pos;
		if(str[0]=='!'){
			pos=1;
		}
		else{
			pos=findSnd(br);
		}
		if(pos<0){
#ifdef TEST			
			std::cout<<"String: \""<<str<<"\" is wrong!"<<std::endl;
#endif
			return false;
		}
		std::string fstBT=br.substr(0, pos);
		std::string sndBT=br.substr(pos, br.length()-1);
#ifdef TEST
		std::cout<<"\tFirst part of bt: \""<<fstBT<<"\""<<std::endl;
		std::cout<<"\tSecond part of bt: \""<<sndBT<<"\""<<std::endl;
#endif
		if(isBinTree(fstBT) && isBinTree(sndBT)){
#ifdef TEST
			std::cout<<"String: \""<<str<<"\" is correct!"<<std::endl;
#endif	
			return true;
		}
		else{
#ifdef TEST
			std::cout<<"String: \""<<str<<"\" is wrong!"<<std::endl;
#endif
			return false;
		}
	}
	else{
#ifdef TEST
		std::cout<<"String: \""<<str<<"\" is wrong!"<<std::endl;
#endif
		return false;
	}
}
/*Main function which reads the string checks it by isBinTree makes tree and
 * writes the result in the terminal
 */
int main(){
	std::cout<<"Enter the string interpretation of binary tree:"<<std::endl;
	std::string str;
	std::getline(std::cin, str);
	std::cout<<"Enter the search character:"<<std::endl;
	char el;
	std::cin>>el;
	if(isBinTree(str)){
		BinTree <char> bt(str, &stringtoT);
		std::cout<<"In binary tree was find symbol \""<<el<<"\" "<<bt.findElNum(el)<<" times!"<<std::endl;
		std::cout<<"Minimal length for this element is: "<<bt.findMinLength(el,0)<<std::endl;
	}
	else{
		std::cout<<"Wrong input!"<<std::endl;
	}
	return 0;
}
