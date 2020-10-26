#include <iostream>
#include <sstream>
#include "header.h"
#include "Assembler.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Assembler assembler("0000");        // assembler object
    // Format 2 example
    assembler.addSymbol("FIRST","0000");    // add label
    assembler.addFormat2("1834");   // ADD B,S no memory reference
    InstructionLine lineOne = assembler.getInstruction(0);
    cout << "address: "<< lineOne.address << endl;
    cout << "Label: "<< lineOne.label << endl;
    cout << "Mnemonic: " << lineOne.mnemonic << endl;
    cout << "Operand Address: " << lineOne.operandAddress << endl;
    cout << "Opcode: " << lineOne.opCode << endl;
    std::cout << "Hello, World!" << std::endl;

    stringstream str;
    str << dec << "A";
    string hexi = "002A";
    string ten = "10";
    int n;
    istringstream(hexi) >> hex >> n;
    istringstream (ten) >> dec >> n;
    cout<<n<<endl;
    cout << str.str()<<endl;
    cout<< assembler.getFormatType("751")<<endl;
    return 0;
}
