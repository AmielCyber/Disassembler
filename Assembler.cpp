#include "Assembler.h"
#include "header.h"

Assembler::Assembler(){
	size = 0;
}
string Assembler::getNextAddress(){
	
}
/**
 * addInstruction adds an assembly instruction line to our assembler code
 * @param type              The format type of the instruction (2-4)
 * @param address           The address where this instruction starts at
 * @param label             The labels from our symbol table
 * @param mnemonic          The mnemonic instruction
 * @param operandAddress    The operand address label
 * @param opCode            The opcode
 */
void Assembler::addInstruction(int type, string address, string label, string mnemonic, string operandAddress, string opCode) {
    InstructionLine newAssemblyLine;
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

/**
 * addHeader will add the first line in our assembly code
 * @param header
 */
void Assembler::addHeader(string header){

}
/**
 * addFormat1 will will add an instruction line of SIC/XE Format 1
 * Just here for fun, if its too complicated we will remove
 * @param opCode The 1 byte opcode
 * the instruction
 */
void Assembler::addFormat1(string opCode){


		
}

/**
 * addFormat2 will will add an instruction line of SIC/XE Format 2
 * @param opCode The 2 byte length opcode
 */
void Assembler::addFormat2(string opCode){
    int TYPE = 2;

	string op(opCode,0,2);      // Get first byte
	string r1(opCode,2,3);      // Third byte will be r1
	string r2(opCode,3,4);      // Fourth byte will be r2
	string address(getNextAddress());   // Get next address for the new line
	string label = " ";                 // Label which will be added after the second pass
	string mnemonic = getMnemonic(op);  // The mnemonic for this instruction
	string operandAddress = " ";        // Operand Address which will be a label
    addInstruction(TYPE,address,label,mnemonic,operandAddress,opCode);
}

/**
 * addFormat3 will will add an instruction line of SIC/XE Format 3 to our assembly code
 * This function will be call for a format 4 also, where it will determine when we
 * check the e bit and if it is then this function will just call addFormat4 function
 * @param opCode The 3 byte length opcode
 */
void Assembler::addFormat3(string opCode){
    int TYPE = 3;
}

/**
 * addFormat4 will will add an instruction line of SIC/XE Format 4
 * @param opCode The 4 byte length opcode
 */
void Assembler::addFormat4(string opCode){
	int TYPE =4;
}

/**
 * addEnd will add the last line in our assembly code
 * @param end
 */
void Assembler::addEnd(string end){

}

/**
 * getFormatType will look on our map given the key is the opcode and
 * the value returned is the format type number
 * @param op The two hex values of the opcode
 * @return The integer format type of the opcode (1-4) or 0 if no opcode is found
 */
int Assembler::getFormatType(string op){
	int formatType= 0;	// Default if not found
	if(formatTypeMap.count(op)){
		formatType = formatTypeMap.at(op);
	}
	return formatType;

}

/**
 * getMnemonic will look on our mnemonicMap given the key is the opcode, e.g. 18
 * and the value returned is the mnemonic operation e.g. ADD
 * @param op The two hex values of the opcode
 * @return The mnemonic operation string
 */
string Assembler::getMnemonic(string op){
	string mnemonic = "";
	if (mnemonicMap.count(op)){
		mnemonic = mnemonicMap.at(op);
	}
	return mnemonic;
}

/**
 * changeOperandAddress is used when we need to modify an address which
 * will be in our second pass where we have the locations of our labels
 * @param address The address to be modified
 * @param newOperandAddress The new modified address
 */
void Assembler::changeOperandAddress(string address, string newOperandAddress){

}

/**
 * addLabel will add the label to our instructions from our label table
 * in our second pass.
 * @param address   The address where we are going to add the label
 * @param newLabel  The label to be added to the instruction
 */
void Assembler::addLabel(string address, string newLabel){

}

/**
 * getInstruction will return an instruction from our assembler code given
 * an address. This function is helpful when we need to change or add
 * something to an instruction.
 * @param address The address instruction we would like to get
 * @return The instruction
 */
InstructionLine Assembler::getInstruction(string address){
    InstructionLine instruction;	                    // Default if not found
    if(lineMap.count(address)){
        instruction = lineMap.at(address);
    }
    return instruction;

}

/**
 * getInstruction will return an instruction from our assembler code given
 * a line position or the index position in our vector.
 * This function is helpful when we need to change or add something to an
 * instruction.
 * @param position The position of our instruction in our vector
 * @return The instruction
 */
struct InstructionLine Assembler::getInstruction(int position){
    InstructionLine instruction;
    if(position>-1 && position< size){
        instruction = line.at(position);
    }
    return instruction;
}

void Assembler::printAssembler(){

}
