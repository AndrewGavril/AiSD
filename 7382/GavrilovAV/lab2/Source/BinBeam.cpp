#include <string>
#include <variant>
#include <iostream>
bool isNum(std::string str);
unsigned int findSnd(std::string str);
/*
 *Class BinBeam contains the lengh of left and right shoulder and the cargoes
 *of this shoulders. It has some methods which checks is in the shoulder weight
 *or beam. The constructor converts the string to the binary beam. And there
 *two methods to get the adress of beam in the left or in the right shoulder.
 */
  
class BinBeam{
        unsigned int leftShoulder;
	unsigned int rightShoulder;
	std::variant<unsigned int, BinBeam*>cargoLeft;
	std::variant<unsigned int ,BinBeam*>cargoRight;
	public:
	BinBeam(){
		leftShoulder=0;
		rightShoulder=0;
		cargoLeft=0;
		cargoRight=0;
	}
	BinBeam(std::string str){
		str.replace(str.begin(), str.begin()+1, "");
                str.replace(str.end()-1,str.end(),"");
                unsigned int pos=findSnd(str);
                std::string leftSh=str.substr(0,pos);
                std::string rightSh=str.substr(pos);
		leftSh.replace(leftSh.begin(), leftSh.begin()+1, "");
		leftSh.replace(leftSh.end()-1,leftSh.end(),"");
		leftShoulder=std::stoi(leftSh.substr(0, leftSh.find(',')));
		if(isNum(leftSh.substr(leftSh.find(',')+1))){
			cargoLeft=std::stoi(leftSh.substr(leftSh.find(',')+1));
		}
		else{
			cargoLeft=new BinBeam(leftSh.substr(leftSh.find(',')+1));
		}
		rightSh.replace(rightSh.begin(), rightSh.begin()+1, "");
		rightSh.replace(rightSh.end()-1, rightSh.end(),"");
		rightShoulder=std::stoi(rightSh.substr(0, rightSh.find(',')));
                if(isNum(rightSh.substr(rightSh.find(',')+1))){
                        cargoRight=std::stoi(rightSh.substr(rightSh.find(',')+1));
                }
                else{
                        cargoRight=new BinBeam(rightSh.substr(rightSh.find(',')+1));
                }
	       };
	bool isLeftInt(){
		return std::holds_alternative<unsigned int>(cargoLeft);
	};
	bool isRightInt(){
		return std::holds_alternative<unsigned int>(cargoRight);
	};
	BinBeam *getRightBeam(){
		if(!isRightInt())
			return std::get<BinBeam *>(cargoRight);
		else 
			return nullptr;
	};
	BinBeam *getLeftBeam(){
		if(!isLeftInt())
			return std::get<BinBeam *>(cargoLeft);
		else 
			return nullptr;
	};
	~BinBeam(){
		if(!isLeftInt())
			delete std::get<BinBeam *>(cargoLeft);
		if(!isRightInt())
			delete std::get<BinBeam *>(cargoRight);
	};

};
