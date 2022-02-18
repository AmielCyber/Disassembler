/***************************************************************
 * Amiel Nava RedID:824264864                                  *
 * Chase Parker RedID:821253141                                *
 * Kenny Nguyen RedID:821649498                                * 
 * Jeremy Espinosa RedID:821770060                             *
 ***************************************************************/
#include "Disassembler.h"
#include "header.h"
#include <sstream>


/**
 * Disassembler instantiates our class with a starting address
 * @param startingAddress
 */
Disassembler::Disassembler(std::string startingAddress) {
    size = 0;
    PC_Counter = startingAddress;
    registerTable["X"] = 0;
    registerTable["B"] = 0;
}

/**
 * getPC Gets the program counter value in hex form
 * @return program counter string in hexadecimal
 */
std::string Disassembler::getPC() {
    return PC_Counter;
}

/**
 * getRegisterValue takes in a string of a register and return the value
 * stored in that register in decimal
 * @param regi register string
 * @return the register value
 */
int Disassembler::getRegisterValue(std::string regi) {
    int value = 0;
    if (registerTable.count(regi)) {
        value = registerTable.at(regi);
    }
    return value;
}

/**
 * getOP_Code Returns the Opcode for an instruction given the
 * first bytes of an opcode, since we only get the first half
 * of the second nibble. For example: byte= 2E then
 * the second nibble in binary: E = 1110 which the opcode
 * will be 0010 11 which is 2C
 * @param bytes the first two nibbles of an opcode
 * @return the opcode from those two nibbles
 */
std::string Disassembler::getOP_Code(std::string byte) {
    std::string opCode = getOP(byte);
    return opCode;
}

/**
 * getNIXBPE takes in a byte that has the values nixbpe. This function will strip
 * off the the first two binary values which are the op values and return the binary
 * value of nixbpe.
 * @param byte which will contain two nibbles containing the nixbpe values
 * @return nixbpe string represented as binary numbers in string format
 */
std::string Disassembler::getNIXBPE(std::string byte) {
    std::string ni(byte, 0, 1);      // Get first nibble
    std::string xbpe(byte, 1, 1);    // Get second nibble

    ni = hexToBinary(ni);               // Turn ni hex value to binary
    ni = ni.substr(2, 2);       // Get only the last two binary values
    xbpe = hexToBinary(xbpe);           // Turn xbpe hex value to binary

    return ni + xbpe;                   // Return nixbpe in binary form
}

/**
 * increment PC increments our program-counter which is done when
 * we add an instruction line to our disassembler. The amount that is incremented
 * depends on the format type that call this function which is also the
 * number of bytes.
 * @param numOfBytes number of bytes to increment program-counter
 */
void Disassembler::incrementPC(int numOfBytes) {
    int integerAddress;                 // Our Address but in decimal form
    // Get PC_Counter hex value and turn it into an integer and store in integerAddress
    std::istringstream(PC_Counter) >> std::hex >> integerAddress;
    integerAddress += numOfBytes;       // Increment the PC in decimal form
    // stringstream object to help us us convert int decimals int string hexadecimal
    std::stringstream stream;
    stream << std::hex << integerAddress;
    std::string pcString = stream.str();
    // Check to see if we need to add extra zeros and add the new PC in our variable
    PC_Counter = addZeros(pcString);
}

/**
 * addInstruction adds an assembly instruction line to our assembler code
 * @param type              The format type of the instruction (2-4)
 * @param address           The address where this instruction starts at
 * @param label             The label for this instruction from our symbol table
 * @param mnemonic          The mnemonic instruction
 * @param operandAddress    The operand address label
 * @param opCode            The opcode
 */
void Disassembler::addInstruction(int type, std::string address, std::string label, std::string mnemonic, std::string operandAddress,
                                  std::string opCode) {
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
 * getOperandAddress2 will get the values or the form from the instruction
 * mnemonic. Like the following forms: r1,r2 or r1,n or r1 or n
 * @param mnemonic  The instruction mnemonic
 * @param r1        The r1 nibble of our format 2
 * @param r2        The r2 nibble of our format 2
 * @return          A string containing the operandAddress label for a format2 instruction
 */
std::string Disassembler::getOperandAddress2(std::string mnemonic, std::string r1, std::string r2) {
    std::string operandLabel = " ";
    std::string str_r1 = "R1";
    std::string str_r2 = "R2";
    std::string n;

    if (mnemonic == "SVC") {
        // SVC n, turn n value into a decimal value
        int n;
        std::istringstream(r1) >> std::hex >> n;
        n++;
        operandLabel = std::to_string(n);
    } else if (mnemonic == "SHIFTL" || mnemonic == "SHIFTR") {
        // SHIFTL r1,n or SHIFTR r1,n
        if (SIC_XE_RegisterMap.count(r1)) {
            str_r1 = SIC_XE_RegisterMap.at(r1);
        }
        // turn n value into a decimal value
        int n;
        std::istringstream(r2) >> std::hex >> n;
        n++;
        operandLabel = str_r1 + "," + std::to_string(n);
    } else if (mnemonic == "CLEAR" || mnemonic == "TIXR") {
        // CLEAR r1 or TIXR r1
        str_r1 = SIC_XE_RegisterMap.at(r1);
        operandLabel = str_r1;
    } else {
        // ADDD r1,r2
        if (SIC_XE_RegisterMap.count(r1)) {
            str_r1 = SIC_XE_RegisterMap.at(r1);
        }
        if (SIC_XE_RegisterMap.count(r2)) {
            str_r2 = SIC_XE_RegisterMap.at(r2);
        }
        operandLabel = str_r1 + "," + str_r2;
    }
    return operandLabel;
}

/**
 * getOperandAddress3_4 gets the operand address for this fromat type
 * Examples: m or c or c,X or m,X
 * @param nixbpe    binary representation of nixbpe
 * @param disp      the displacement or address made of 4 nibbles
 * @return          string operand Address label
 */
std::string Disassembler::getOperandAddress3_4(std::string nixbpe, std::string disp, bool loadIndex, bool loadBase) {
    std::string operandAddress("");  // the return string
    std::string label;               // Label we will get when we get the TA
    std::string ONE = "1";
    int MAX_DISPLACEMENT = 2047;// Used to see if we are subtracting from PC
    std::string THREE_ZEROS = "000";
    int targetAddress;
    bool index = nixbpe.compare(2, 1, ONE) == 0;
    bool base = nixbpe.compare(3, 1, ONE) == 0;
    bool pc = nixbpe.compare(4, 1, ONE) == 0;
    // Get the target address in decimal value integer
    std::istringstream(disp) >> std::hex >> targetAddress;

    // Add assembly notation if addressing type is Immediate/Indirect type
    if (nixbpe.compare(0, 2, "10") == 0) {
        // If the addressing type is Indirect (n=1,i=0)
        operandAddress.append("@");
    } else if (nixbpe.compare(0, 2, "01") == 0) {
        // If the addressing type is Immediate (n=0,i=1)
        operandAddress.append("#");
    }

    if (nixbpe.compare(3, 3, THREE_ZEROS) == 0) {
        // If we are using a constant (b=p=e=0)
        operandAddress.append(std::to_string(targetAddress)); // c : constant value
    }
    else {
        if (index) {
            // If the index bit is turned on then : m,X
            // disp + X
            int indexValue = getRegisterValue("X");
            targetAddress += indexValue;
        }
        if (base) {
            // If the base bit is one then disp + B
            int baseValue = getRegisterValue("B");
            targetAddress += baseValue;
        }
        if (pc) {
            // If the PC bit is one then disp + PC
            int pcValue;
            std::istringstream(getPC()) >> std::hex >> pcValue;
            if(targetAddress > MAX_DISPLACEMENT){
                // If we have to subtract
                targetAddress = targetAddress - 4096 ;
            }
            targetAddress += pcValue;
        }
        label = getLabel(targetAddress);
        if(label == " "){
            // If we do not get a label then we search for a literal instead
            label = getLiteral(targetAddress).label;
        }
        operandAddress.append(label);   // Append the label or the literal
    }
    if(loadIndex){
        // Load the value of X register if there was an LDX instruction
        registerTable["X"] = targetAddress;
    }else if(loadBase){
        // Load the value of B register if there was an LDB instruction
        registerTable["B"] = targetAddress;
        addInstruction(0," "," ","BASE",label," ");
    }
    if(index){
        // Attach the following string if the index bit was on for nixbpe
        operandAddress.append(",X");
    }

    return operandAddress;
}

/**
 * addSymbol adds a symbol/label to our symbol table
 * @param symbol The symbol/label from that address
 * @param address The address we need to put that symbol/address
 */
void Disassembler::addSymbol(std::string symbol, std::string address) {
    int decimalValue;
    std::istringstream(address) >> std::hex >> decimalValue;
    symbolTable[decimalValue] = symbol;
}

/**
 * addLiteral adds a literal to our literal table
 * @param literal The literal from that address
 * @param address The address we need to put that literal
 */
void Disassembler::addLiteral(std::string literal, int length, std::string address) {
    int decimalValue;
    std::istringstream(address) >> std::hex >> decimalValue;
    Literal literalStruct = {literal, length};
    literalTable[decimalValue] = literalStruct;
}

void Disassembler::addFormat(std::string opCode, int type) {
    switch (type) {
        case 0:
            break;
        case 1:
            addFormat1(opCode);
            break;
        case 2:
            addFormat2(opCode);
            break;
        case 3:
            addFormat3_4(opCode,type);
            break;
        case 4:
            addFormat3_4(opCode,type);
            break;
        default:
            std::cout << "Invalid op code found!" << std::endl;
            std::cout << "Now exiting..."<<std::endl;
            exit(EXIT_FAILURE);
            break;
    }
}

/**
 * addFormat1 will will add an instruction line of SIC/XE Format 1
 * Just here for fun, if its too complicated we will remove
 * @param opCode The 1 byte opcode
 * the instruction
 */
void Disassembler::addFormat1(std::string opCode) {
    int TYPE = 1;

    std::string op(opCode, 0, 2);      // Get first byte
    std::string address(getPC());            // Get next address for the new line
    int addressDecimal;
    std::istringstream(address) >> std::hex >> addressDecimal;
    std::string label = getLabel(addressDecimal);   // Label for this address
    std::string mnemonic = getMnemonic(op);  // The mnemonic for this instruction
    // Operand Address which will be a label
    std::string operandAddress = " ";
    // Add instruction line
    addInstruction(TYPE, address, label, mnemonic, operandAddress, opCode);
    incrementPC(TYPE);                  // Increment PC counter
}

/**
 * addFormat2 will will add an instruction line of SIC/XE Format 2
 * @param opCode The 2 byte length opcode
 */
void Disassembler::addFormat2(std::string opCode) {
    int TYPE = 2;

    std::string op(opCode, 0, 2);      // Get first byte
    std::string r1(opCode, 2, 1);      // Third byte will be r1
    std::string r2(opCode, 3, 1);      // Fourth byte will be r2
    std::string address(getPC());            // Get next address for the new line
    int addressDecimal;
    std::istringstream(address) >> std::hex >> addressDecimal;
    std::string label = getLabel(addressDecimal);   // Label for this address
    std::string mnemonic = getMnemonic(op);  // The mnemonic for this instruction
    // Operand Address which will be a label
    std::string operandAddress = getOperandAddress2(mnemonic, r1, r2);
    // Add instruction line
    addInstruction(TYPE, address, label, mnemonic, operandAddress, opCode);
    incrementPC(TYPE);                  // Increment PC counter
}

/**
 * addFormat3_4 will add either a format3/format4 instruction.
 * @param opCode The opcode for this function
 * @param type The type of the function either 3 or 4
 */
void Disassembler::addFormat3_4(std::string opCode, int type) {
    std::string address = getPC();
    incrementPC(type);          // Increment PC counter
    int addressDecimal;
    std::istringstream(address) >> std::hex >> addressDecimal;
    std::string label = getLabel(addressDecimal);
    std::string op(opCode, 0, 2);
    op = getOP_Code(op);
    int numOfNibbles;

    std::string mnemonic = getMnemonic(op);
    bool loadIndex = mnemonic.compare("LDX") ==0;
    bool loadBase = mnemonic.compare("LDB") == 0;
    if (type == 4){
        mnemonic = "+" + getMnemonic(op);
    }
    if(type == 3){
        numOfNibbles = 3;
    }else{
        numOfNibbles = 5;
    }
    std::string nixbpe(opCode, 1, 2);  // Initialize to the first 2 nibbles
    nixbpe = getNIXBPE(nixbpe);         // Trim out the op part and get nixbpe values in binary
    std::string disp(opCode, 3, numOfNibbles);    // Initialize to the last number of nibbles (disp)
    std::string operandAddress = getOperandAddress3_4(nixbpe, disp, loadIndex, loadBase);
    if(mnemonic == "RSUB"){
        // If the instruction is RSUB then the operand address will be empty
        operandAddress = " ";
    }
    InstructionLine baseLine;   // Use to remove and add an Instruction base line
    if(loadBase){
        /* Remove the base instruction it was added in the getOperandAddress3_4
         * function and put the Instruction and then put the base instruction back at the end*/
        baseLine = line.back();
        line.pop_back();
        addInstruction(type, address, label, mnemonic, operandAddress, opCode);
        line.push_back(baseLine);
    } else{
        // If there were no load base instruction
        addInstruction(type, address, label, mnemonic, operandAddress, opCode);
    }

}

/**
 * getFormatType will look on our format type map given the key is the opcode and
 * the value returned is the format type number.
 * @param threeNibbles The three hex values of the opcode.
 * @return The integer format type of the opcode (1-4) or 0 if no opcode is found.
 */
int Disassembler::getFormatType(std::string threeNibbles) {
    int formatType;    // Default if not found
    std::string opCode(threeNibbles, 0, 2);
    opCode = getOP_Code(opCode);
    formatType = formatTypeMap.count(opCode);
    if (formatType) {
        formatType = formatTypeMap.at(opCode);
    } else {
        std::cout << "Invalid opCode found! " << opCode << std::endl;
        std::cout << "Now exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }
    // Check if its a type 3 or type 4
    if (formatType == 3) {
        int decimalVal;
        // Turn the second nibble into a decimal value
        std::string thirdNibble(threeNibbles, 2, 1);
        std::istringstream(thirdNibble) >> std::hex >> decimalVal;
        if (decimalVal % 2 == 1) {
            // If the second nibble is odd then it is format 4, hence by the e bit at the end
            formatType = 4;
        }
    }
    return formatType;

}

/**
 * getMnemonic will look on our mnemonicMap given the key is the opcode, e.g. 18
 * and the value returned is the mnemonic operation e.g. ADD
 * @param op The two hex values of the opcode
 * @return The mnemonic operation string
 */
std::string Disassembler::getMnemonic(std::string op) {
    std::string mnemonic = "";
    if (mnemonicMap.count(op)) {
        mnemonic = mnemonicMap.at(op);
    }
    return mnemonic;
}

/**
 * getLabel will get the label for the address that is passed. It will do this
 * by searching the symbol table for that address if any, else the label will
 * just be a blank space.
 * @param address   The address where we are going to add the label in decimal form
 * @return label    The string label for the passed address. Returns empty if not found
 */
std::string Disassembler::getLabel(int address) {
    std::string label(" ");
    if (symbolTable.count(address)) {
        label = symbolTable.at(address);
    }
    return label;
}

/**
 * getLiteral will get the literal for the address that is passed. It will do this
 * by searching the literal table for that address if any, else the literal will
 * just be a blank space.
 * @param address   The address where we are going to add the literal in decimal form
 * @return literal    The string literal for the passed address. Returns null if not found
 */
Literal Disassembler::getLiteral(int address) {
    Literal literal;
    if (literalTable.count(address)) {
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
InstructionLine Disassembler::getInstruction(std::string address) {
    InstructionLine instruction;
    if (lineMap.count(address)) {
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
struct InstructionLine Disassembler::getInstruction(int position) {
    InstructionLine instruction;
    if (position > -1 && position < size) {
        instruction = line.at(position);
    }
    return instruction;
}

/**
 * getInstructions will return a vector of all Instructions in the
 * assembler code.
 * @return vector of type InstructionLine that will contain all the
 * instruction lines added to the assembly code.
 */
std::vector<InstructionLine> Disassembler::getInstructions(){
    return line;
}

/**
 * isNextInstructionLiteral will determine if the next address is a literal
 * since we cant decipher if there is a literal up next from opcode.
 * @return int positve integer: if the next address/line is a literal
 * and that integer value will be the size in bytes of that literal.
 * Returns a zero if the next instruction line is not a literal.
 */
int Disassembler::isNextInstructionLiteral() {
    int programCounter;
    int sizeOfLiteral = 0;
    std::istringstream(getPC()) >> std::hex >> programCounter;    // Get the PC in integer decimal value
    if(literalTable.count(programCounter)){
        sizeOfLiteral = literalTable.at(programCounter).length;
    }
    return sizeOfLiteral;
}

/**
 * isNextInstructionSymbol check if the next instruction is a reserved word
 * @return
 */
bool Disassembler::isNextInstructionSymbol(){
    int currentAddress;
    bool nextSymbol;
    std::istringstream(getPC()) >> std::hex >> currentAddress;    // Get the PC in integer decimal value
    nextSymbol = symbolTable.count(currentAddress) && currentAddress != 0;

    return nextSymbol;
}

/**
 * addLiteralInstruction adds a literal instruction to our assembly code.
 * @param opCode The opcode for the literal instruction
 */
void Disassembler::addLiteralInstruction(std::string opCode) {
    std::string operandAdress;
    bool prevIsLiteral = false;                             // Used to check if we already have a literal pool
    int address;
    std::string prevAddress = line.back().address;          // Get the last address
    std::istringstream(prevAddress) >> std::hex >> address; // Convert into decimal
    prevIsLiteral = literalTable.count(address) > 0;
    if(!prevIsLiteral){
        // If there is no literal pool before the current then we add one
        addInstruction(0, " ", " ", "LTORG", " ", " ");
    }
    std::istringstream(getPC()) >> std::hex >> address;
    Literal literal = literalTable.at(address);
    operandAdress = literal.label;
    addInstruction(0,getPC(),getLabel(address),"*",operandAdress,opCode);
    incrementPC(opCode.length()/2);
}

/**
 * addSymbolInstructions adds all the reserve words at the end of our assembly code.
 */
void Disassembler::addSymbolInstructions() {
    int address;
    int lastAddress;
    int byteSize;
    int count;
    std::string label;
    std::vector<InstructionLine> symbolLine;
    std::map<int, std::string>::iterator iter;    // Create an iterator

    // Iterate through the symbol table
    for(iter = symbolTable.begin(); iter != symbolTable.end(); iter++){
        address = iter->first;
        label = iter->second;
        std::istringstream(line.back().address) >> std::hex >> lastAddress;
        if(address > lastAddress){
            // If the symbol found is not added to the assembly code
            std::stringstream stream;
            stream << std::hex << address;
            std::string addressString = stream.str();
            symbolLine.push_back({0,addZeros(addressString),label,"RESW","",""});
            count++;
        }

    }
    int nextAddress, currentAddress;
    int length = symbolLine.size();
    int index = 0;
    while(index<length-1){

        InstructionLine l = symbolLine.at(index);
        std::istringstream (symbolLine.at(index+1).address) >> std::hex >> nextAddress;
        std::istringstream (l.address) >>std::hex>> currentAddress;
        byteSize = (nextAddress - currentAddress) / 3;
        addInstruction(l.type,l.address,l.label,l.mnemonic,std::to_string(byteSize),l.opCode);
        index++;
    }
    if(length > 0 ){
        InstructionLine l = symbolLine.at(index);
        nextAddress = progLength;
        std::istringstream (l.address) >>std::hex>> currentAddress;
        byteSize = (nextAddress - currentAddress) / 3;
        addInstruction(l.type,l.address,l.label,l.mnemonic,std::to_string(byteSize),l.opCode);
    }
}

/**
 * getSize Gets the size of Disassembler
 * @return size
 */
int Disassembler::getSize() {
    return size;
}

/**
 * addHeader will add the first line in our assembly code
 * @param header
 */
void Disassembler::addHeader(std::string progName, std::string startingAddress, std::string length) {
    std::istringstream(length) >> std::hex >> progLength;
    addInstruction(0,startingAddress,progName,"START","0"," ");
}

/**
 * addEnd will add the last line in our assembly code
 * @param end
 */
void Disassembler::addEnd(std::string address) {
    std::string first = address;
    addInstruction(0," ","END","FIRST"," "," ");
}

std::string Disassembler::addZeros(std::string address) {
    std::string newStr(" ");
    switch (address.length()) {
        case 1:
            newStr = "00000" + address;
            break;
        case 2:
            newStr = "0000" + address;
            break;
        case 3:
            newStr = "000" + address;
            break;
        case 4:
            newStr = "00" + address;
            break;
        case 5:
            newStr = "0" + address;
        default:
            newStr = address;
    }
    return newStr;
}

/**
 * changeOperandAddress is used when we need to modify an address which
 * will be in our second pass where we have the locations of our labels
 * @param address The address to be modified
 * @param newOperandAddress The new modified address
 */
void Disassembler::changeOperandAddress(std::string address, std::string newOperandAddress) {

}

void Disassembler::printAssembler() {

}
