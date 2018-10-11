#include <iostream>
#include <fstream>
#include "stack.cpp"
//#define USER
#define TEST

/*Function readLE checks the string for the correct symbols of
 *operations and arguments. If an argument or a symbol is correct
 *this function pushs it to stack otherwise it returns false.
 *At the end of reading it returns true
 */
bool readLE(std::string str, Stack *stack){
#ifdef TEST
	std::cout<<"Reading the logical expession!"<<std::endl;
#endif
	int i = 0;
	int numOp=0;
	int numCl=0;
#ifdef TEST
	std::cout<<"Stack contains:"<<std::endl;
#endif
	while(i<str.length()){
		if(str[i]=='('){
			stack->push(str[i]);
			i++;
			numOp++;
			continue;
		}
		if(str[i]=='!' || str[i]=='&' || str[i]=='|'){
			stack->push(str[i]);
			i++;
			continue;
		}
		if(str[i]==')'){
			stack->push(str[i]);
			i++;
			numCl++;
			continue;
		}
		if(str.find("true", i, 4)!=std::string::npos){
			i+=4;
			stack->push('t');
			continue;
		}
		if(str.find("false", i, 5)!=std::string::npos){
			i+=5;
			stack->push('f');
			continue;
		}
		else{
			return false;
		}
	}
	if(numOp!=numCl)
		return false;
	return true;
}
/*
 * Function calc is calculating the logical expression which
 * is in the stack. It returns the result. If the logical expression
 * is wrong and the function can't calcculate it, the program is closing with
 * an error.
 */
bool calc(Stack *stack){
	char el=stack->pop();
	bool res;
	if(el=='t'){
		return true;
	}
	if(el=='f'){
                return false;
        }
	if(el==')' && stack->count()>2){
		bool fstLE=calc(stack);
		el=stack->pop();
		if(el=='!'){
			res = !fstLE;
			stack->pop();
			return res;
		}
		if(el=='|'){
			res= fstLE | calc(stack);
			stack->pop();
			return res;
		}
		if(el=='&'){
			res= fstLE & calc(stack);
			stack->pop();
			return res;
		}
	}
	else{
		std::cout<<stack->topElem()<<std::endl;
		std::cout<<"Can't calc!"<<std::endl;
		exit(1);
	}
}
/* Main function gets the name of file to read, reading it if the name is
 * correct otherwise return 0 with an error. If file is opend gets string
 * from the file, reads and calculates logical expression with a functions
 * readLE and calc.
 */
int main(){
#ifdef USER
	std::cout<<"Enter the name of file to read:"<<std::endl;
#endif
	std::string str;
	std::getline(std::cin, str);
	Stack *stack=new Stack(100);
#ifdef USER
	std::ifstream file(str);
	if(!file.is_open()){
		std::cout<<"Wrong file name!"<<std::endl;
		delete stack;
		return 0;
	}
	std::getline(file, str);
	file.close();
#endif
	bool res;
	if(readLE(str, stack)){
		res=calc(stack);
		if(stack->isEmpty())
			std::cout<<"Result: "<<res<<std::endl;
		else
			std::cout<<"Wrong logical expression!"<<std::endl;
	}
	else{
		std::cout<<"This is not logical expression!"<<std::endl;
		return 0;
	}
	delete stack;
	return 0;
}
