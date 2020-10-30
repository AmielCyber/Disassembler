#include <iostream>
#include <sstream>
#include "header.h"
#include "Disassembler.h"
int main() {

    Disassembler disassembler2("0000");        // assembler object
    // Format 2 example
    disassembler2.addSymbol("FIRST","0000");    // add label
    disassembler2.addSymbol("MAXLEN","1000");
    disassembler2.addSymbol("SECOND","0002");
    disassembler2.addSymbol("THIRD","0005");

    disassembler2.addFormat2("1834");   // ADD B,S no memory reference
    InstructionLine lineOne = disassembler2.getInstruction(0);
    cout << "Format Type: " << lineOne.type << endl;
    cout << "address: "<< lineOne.address << endl;
    cout << "Label: "<< lineOne.label << endl;
    cout << "Mnemonic: " << lineOne.mnemonic << endl;
    cout << "Operand Address: " << lineOne.operandAddress << endl;
    cout << "Opcode: " << lineOne.opCode << endl;

    disassembler2.addFormat3("290000");//COMP #0
    InstructionLine lineTwo = disassembler2.getInstruction(1);
    cout << "Format Type: "  << lineTwo.type << endl;
    cout << "address: "<< lineTwo.address << endl;
    cout << "Label: "<< lineTwo.label << endl;
    cout << "Mnemonic: " << lineTwo.mnemonic << endl;
    cout << "Operand Address: " << lineTwo.operandAddress << endl;
    cout << "Opcode: " << lineTwo.opCode << endl;

    disassembler2.addFormat4("75101000"); // +LDT #MAXLENGTH
    InstructionLine lineThree = disassembler2.getInstruction(2);
    cout << "Format Type: "  << lineThree.type << endl;
    cout << "address: "<< lineThree.address << endl;
    cout << "Label: "<< lineThree.label << endl;
    cout << "Mnemonic: " << lineThree.mnemonic << endl;
    cout << "Operand Address: " << lineThree.operandAddress << endl;
    cout << "Opcode: " << lineThree.opCode << endl;

    // Hex to decimal examples
    stringstream str;
    str << dec << "A";
    string hexi = "29";
    string ten = "10";
    int n;
    istringstream(hexi) >> hex >> n;
    cout << n << endl;
    istringstream (ten) >> dec >> n;
    cout<<n<<endl;
    cout << str.str()<<endl;
    cout<< disassembler2.getFormatType("751")<<endl;
    return 0;
}