#include "Assembler.h"
#include "header.h"
#include <sstream>

Assembler::Assembler(string startingAddress){
    size = 0;
    PC_Counter = startingAddress;
}
string Assembler::getNextAddress(){
    return PC_Counter;
}
void Assembler::incrementPC_Counter(int formatType){
    int integerAddress;             // Our Address but in decimal form
    // Get PC_Counter hex value and turn it into an integer and store in integerAddress
    istringstream(PC_Counter) >> dec >> integerAddress;
    integerAddress += formatType;   // Increment the PC_Counter in decimal form

    string strPC_Counter = to_string(integerAddress); // Set the new PC_Counter in hex
    // Check to see if we need to add extra zeros and add the new PC counter in our variable
    switch (strPC_Counter.length()) {
        case 1:
            PC_Counter = "000" + strPC_Counter;
            break;
        case 2:
            PC_Counter = "00" + strPC_Counter;
            break;
        case 3:
            PC_Counter = "0" + strPC_Counter;
            break;
        default:
            PC_Counter = strPC_Counter;
    }
}
/**
 * getFormat2Labels will get the values or the form from the instruction
 * mnemonic. Like the following forms: r1,r2 or r1,n or r1 or n
 * @param mnemonic  The instruction mnemonic
 * @param r1        The r1 nibble of our format 2
 * @param r2        The r2 nibble of our format 2
 * @return          A string containing the label for a format2 instruction
 */
string Assembler::getFormat2Labels(string mnemonic, string r1, string r2) {
    string operandLabel = " ";
    string str_r1 = "R1";
    string str_r2 = "R2";
    string n;

    if(mnemonic == "SVC"){
        // SVC n
        // turn n value into a decimal value
        int n;
        istringstream(r1) >> dec >> n;
        n++;
        operandLabel = to_string(n);
    }else if (mnemonic == "SHIFTL" || mnemonic == "SHIFTR"){
        // SHIFTL r1,n or SHIFTR r1,n
        if(SIC_XE_RegisterMap.count(r1)){
            str_r1 = SIC_XE_RegisterMap.at(r1);
        }
        // turn n value into a decimal value
        int n;
        istringstream(r2) >> dec >> n;
        n++;
        operandLabel = str_r1 + "," + to_string(n);
    }else if (mnemonic == "CLEAR" || mnemonic == "TIXR"){
        // CLEAR r1 or TIXR r1
        str_r1 = SIC_XE_RegisterMap.at(r1);
        operandLabel = str_r1;
    }else{
        // ADDD r1,r2
        if(SIC_XE_RegisterMap.count(r1)){
            str_r1 = SIC_XE_RegisterMap.at(r1);
        }
        if(SIC_XE_RegisterMap.count(r2)){
            str_r2 = SIC_XE_RegisterMap.at(r2);
        }
        operandLabel = str_r1 + "," + str_r2;
    }
    return operandLabel;
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
 * addSymbol adds a symbol/label to our symbol table
 * @param symbol The symbol/label from that address
 * @param address The address we need to put that symbol/address
 */
void Assembler::addSymbol(string symbol, string address){
    symbolTable[address] = symbol;
}

/**
 * addLiteral adds a literal to our literal table
 * @param literal The literal from that address
 * @param address The address we need to put that literal
 */
void Assembler::addLiteral(string literal, string address){
    literalTable[address] = literal;
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
    string r1(opCode,2,1);      // Third byte will be r1
    string r2(opCode,3,1);      // Fourth byte will be r2
    string address(getNextAddress());   // Get next address for the new line
    string label = getLabel(address);   // Label for this address
    string mnemonic = getMnemonic(op);  // The mnemonic for this instruction
    // Operand Address which will be a label
    string operandAddress = getFormat2Labels(mnemonic,r1, r2);
    // Add instruction line
    addInstruction(TYPE,address,label,mnemonic,operandAddress,opCode);
    incrementPC_Counter(TYPE);          // Increment PC counter
}

/**
 * NOT FUNCTIONAL JUST FOR DEBUGGING FOR NOW
 * addFormat3 will will add an instruction line of SIC/XE Format 3 to our assembly code
 * This function will be call for a format 4 also, where it will determine when we
 * check the e bit and if it is then this function will just call addFormat4 function
 * @param opCode The 3 byte length opcode
 */
void Assembler::addFormat3(string opCode){
    int TYPE = 3;

    string address = getNextAddress();
    string op(opCode,0,2);
    op = getOP_Code(op);
    string mnemonic = getMnemonic(op);
    /**********NEEDS TO BE IMPLEMENTED TO BE FUNCTIONAL***********************/
    string label = " ";
    string operandAddress = " ";
    addInstruction(TYPE,address,label,mnemonic,operandAddress,opCode);
    incrementPC_Counter(TYPE);          // Increment PC counter
}

/**
 * NOT FUNCTIONAL JUST FOR DEBUGGING FOR NOW
 * addFormat4 will will add an instruction line of SIC/XE Format 4
 * @param opCode The 4 byte length opcode
 */
void Assembler::addFormat4(string opCode){
    int TYPE = 4;


    string address = getNextAddress();
    string op(opCode,0,2);
    op = getOP_Code(op);
    string mnemonic = getMnemonic(op);
    /**********NEEDS TO BE IMPLEMENTED TO BE FUNCTIONAL***********************/
    string label = " ";
    string operandAddress = " ";
    addInstruction(TYPE,address,label,mnemonic,operandAddress,opCode);
    incrementPC_Counter(TYPE);          // Increment PC counter
}



/**
 * getFormatType will look on our map given the key is the opcode and
 * the value returned is the format type number
 * @param threeNibbles The three hex values of the opcode
 * @return The integer format type of the opcode (1-4) or 0 if no opcode is found
 */
int Assembler::getFormatType(string threeNibbles){
    int formatType= 0;	// Default if not found
    string opCode(threeNibbles,0,2);
    opCode = getOP_Code(opCode);
    if(formatTypeMap.count(opCode)){
        formatType = formatTypeMap.at(opCode);
    }
    else{
        cout << "Invalid opCode found: "<< opCode<<endl;
        cout<< "Now exiting..."<<endl;
        system("exit");
    }
    // Check if its a type 3 or type 4
    if(formatType == 3){
        int decimalVal;
        // Turn the second nibble into a decimal value
        string thirdNibble(threeNibbles,2,1);
        istringstream(thirdNibble) >> dec >> decimalVal;
        if(decimalVal % 2 == 1){
            // If the second nibble is odd then it is format 4, hence by the e bit at the end
            formatType = 4;
        }
    }
    return formatType;

}

string Assembler::getOP_Code(string byte) {
    string opCode = getOP(byte);
    return opCode;
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
 * getLabel will get the label for the address that is passed. It will do this
 * by searching the symbol table for that address if any, else the label will
 * just be a blank space.
 * @param address   The address where we are going to add the label
 * @return label    The string label for the passed address
 */
string Assembler::getLabel(string address){
    string label(" ");
    if(symbolTable.count(address)){
        label = symbolTable.at(address);
    }
    return label;
}

/**
 * getLiteral will get the literal for the address that is passed. It will do this
 * by searching the literal table for that address if any, else the literal will
 * just be a blank space.
 * @param address   The address where we are going to add the literal
 * @return label    The string literal for the passed address
 */
string Assembler::getLiteral(string address) {
    string literal(" ");
    if(literalTable.count(address)){
        literal = literalTable.at(address);
    }
    return literal;
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

/**
 * addHeader will add the first line in our assembly code
 * @param header
 */
void Assembler::addHeader(string header){

}

/**
 * addEnd will add the last line in our assembly code
 * @param end
 */
void Assembler::addEnd(string end){

}

/**
 * changeOperandAddress is used when we need to modify an address which
 * will be in our second pass where we have the locations of our labels
 * @param address The address to be modified
 * @param newOperandAddress The new modified address
 */
void Assembler::changeOperandAddress(string address, string newOperandAddress){

}

void Assembler::printAssembler(){

}