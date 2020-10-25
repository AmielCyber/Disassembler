#include "Assembler.h"

Assembler::Assembler(){
	size = 0;
}

void Assembler::addHeader(string header){

}

void Assembler::addEnd(string end){

}

void Assembler::addFormat1(string opCode){
	
}

void Assembler::addFormat2(string opCode){
	string op(opCode,0,2);
	string r1(opCode,2,3);
	string r2(opCode,3,4);


}

void Assembler::addFormat3(string opCode){

}

void Assembler::addFormat4(string opCode){

}

string Assembler::getNextAddress(){

}

int Assembler::getFormatType(string op){

}

void Assembler::changeOperandAddress(string address, string newOperandAddress){

}

void Assembler::changeLabel(string address, string newLabel){

}

assemblyLine Assembler::geetLine(string operandAddress){

}

assemblyLine Assembler::getLine(int position){

}

void Assembler::printAssembler(){

}
