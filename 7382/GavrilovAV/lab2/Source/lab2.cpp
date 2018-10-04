#include <regex>
#include <variant>
#include <iostream>
#include <cstring>
#include "BinBeam.cpp"
//#define TEST

bool isBeam(std::string str);
/*
 * Function number counts the number of weights in the binary
 * beam. This function finds weight in the shoulder and adds it
 * to the result. If there's no weight in shoulder function 
 * starts this algorithm again with the other beam which contains in this
 * shoulder.
 */
unsigned int number(BinBeam *bk, int d){
	unsigned int res=0;
	if(bk->isLeftInt()){
		res++;
	}
	else{
		res+=number(bk->getLeftBeam(),d++);
	}
	if(bk->isRightInt()){
                res++;
        }
        else{
                res+=number(bk->getRightBeam(),d++);
        }
#ifdef TEST
	std::cout<<"Recursion depth: "<<d<<" count = "<<res<<std::endl;
#endif
	return res;
}
/*Function isNum checks the input string for the number by
 *the regular expression. If the string contains
 *only number function returns true otherwise false.
 */
bool isNum(std::string str){
#ifdef TEST
	std::cout<<"\tChecking the string for the the number"<<std::endl;
#endif
        if(std::regex_match(str, std::regex("^[0-9]+$"))){
#ifdef TEST
                        std::cout<<"\tInput string: \""<<str<<"\" is correct"<<std::endl;
#endif
                return true;
        }
        else{
#ifdef TEST
                        std::cout<<"\tInput string: \""<<str<<"\" is wrong"<<std::endl;
#endif
                return false;
        }
}
/*
 * Function findSnd finds the point where the line splits on the two shoulders
 * and returns the index of first character int the second shoulder.
 */
unsigned int findSnd(std::string str){
	char cStr[str.length()+1];
	std::strcpy(cStr,str.c_str());
	unsigned int index=0;
	unsigned int numOp=0;
        unsigned int numCl=0;
	do{
		if(cStr[index]=='('){
			numOp++;
		}
		if(cStr[index]==')'){
			numCl++;
		}
		index++;

	}while(index<std::strlen(cStr) && numOp!=numCl);
	return index;
}
/*
 * Function isShoulder checks the input string for the correctness 
 * by the regular expression then checks the binary beam by function isBeam if
 * the shoulder contains it.
 */
bool isShoulder(std::string str){
	if(std::regex_match(str, std::regex("^[(]{1}[0-9]+,.+[)]{1}$"))){
		str.replace(str.begin(), str.begin()+1, "");
                str.replace(str.end()-1,str.end(),"");
		std:: string substr1=str.substr(0, str.find(','));
		std:: string substr2=str.substr(str.find(',')+1);
		if(isNum(substr1) && isNum(substr2)){
#ifdef TEST
                        std::cout<<"Input string: \""<<str<<"\" is correct"<<std::endl;
#endif
			return true;
		}
		if(isNum(substr1) && isBeam(substr2)){
#ifdef TEST
                        std::cout<<"Input string: \""<<str<<"\" is correct"<<std::endl;
#endif
			return true;
		}
		else{
#ifdef TEST
                        std::cout<<"Input string: \""<<str<<"\" is wrong"<<std::endl;
#endif
			return false;
	
		}
	}
	else{
#ifdef TEST
                        std::cout<<"Input string: \""<<str<<"\" is wrong"<<std::endl;
#endif
		return false;
	}
}
/*
 * Function isBeam checks the input string for the correctness by
 *  regular expression and checks the right and left shoulders for
 *  the correctness by function isShoulder. If it's correct returns true
 *  otherwise false.
 */
bool isBeam(std::string str){
	if(std::regex_match(str, std::regex("^[(]{2}.*[)(].*[)]{2}$"))){
		str.replace(str.begin(), str.begin()+1, "");
        	str.replace(str.end()-1,str.end(),"");
        	unsigned int pos=findSnd(str);
        	std::string substr1=str.substr(0,pos);
        	std::string substr2=str.substr(pos);
		if(isShoulder(substr1)&&isShoulder(substr2)){
#ifdef TEST
			std::cout<<"Input string: \""<<str<<"\" is correct"<<std::endl;
#endif
			return true;
		}
		else{
#ifdef TEST
                        std::cout<<"Input string: \""<<str<<"\" is wrong"<<std::endl;
#endif
			return false;
		}
	}
	else{
#ifdef TEST
                        std::cout<<"Input string: \""<<str<<"\" is wrong"<<std::endl;
#endif
		return false;
	}
}
/*
 * Main function which gets input string, checks the coorectness of it by
 * funtion isBeam the writs the error if it's not correct
 * otherwise writs the number of wights in the binary beam.
 */
int main(){
	std::cout<<"Enter the converting to the binary beam string:"<<std::endl;
        std::string str;
        std::getline(std::cin, str);
	str=std::regex_replace(str,std::regex("[^()0-9,]*"), "");
#ifdef TEST
	std::cout<<"Checking for the wrong input"<<std::endl;
#endif
	if(!isBeam(str)){
		std::cout<<"Wrong input"<<std::endl;
		return 0;}
#ifdef TEST
	std::cout<<"Creating binary beam"<<std::endl;
#endif
	BinBeam *bk= new BinBeam(str);
#ifdef TEST
	std::cout<<"Counting the number of weights:"<<std::endl;
#endif
	unsigned int res=number(bk, 0);
	std::cout<<"Number of weights is: "<< res<<std::endl;
	delete bk;
	return 0;
}
