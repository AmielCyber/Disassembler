#include "Assembler.h"
#include "header.h"

Assembler::Assembler(){
	size = 0;
}
string Assembler::getNextAddress(){
	
}

void Assembler::addAssemblyLine(int type, string address, string label, string mnemonic, string operandAddress, string opCode) {
    AssemblyLine newAssemblyLine;
    newAssemblyLine.type = type;
    newAssemblyLine.address = address;
    newAssemblyLine.label = label;
    newAssemblyLine.mnemonic = mnemonic;
    newAssemblyLine.operandAddress = operandAddress;
    newAssemblyLine.opCode = opCode;
    line.push_back(newAssemblyLine);
    lineMap[address] = newAssemblyLine;
    size++;
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
	string address(getNextAddress());
	string label;
	string mnemonic = getMnemonic(op);
	string operandAddress = "";
	AssemblyLine newAssemblyLine;
	

}

void Assembler::addFormat3(string opCode){

}

void Assembler::addFormat4(string opCode){

}

int Assembler::getFormatType(string op){
	int formatType= -1;	// Default if not found
	if(formatTypeMap.count(op)){
		formatType = formatTypeMap.at(op);
	}
	return formatType;

}

string Assembler::getMnemonic(string op){
	string mnemonic = "";
	if (mnemonicMap.count(op)){
		mnemonic = mnemonicMap.at(op);
	}
	return mnemonic;
}

void Assembler::changeOperandAddress(string address, string newOperandAddress){

}

void Assembler::changeLabel(string address, string newLabel){

}

AssemblyLine Assembler::getLine(string address){
    AssemblyLine instruction;	                    // Default if not found
    if(lineMap.count(address)){
        instruction = lineMap.at(address);
    }
    return instruction;

}

struct AssemblyLine Assembler::getLine(int position){
    AssemblyLine instruction;
    if(position>-1 && position< size){
        instruction = line.at(position);
    }
    return instruction;
}

void Assembler::printAssembler(){

}
