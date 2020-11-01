#include <iostream>
#include <sstream>
#include "header.h"
#include "Disassembler.h"
#include "textRecord.h"

int main() {

    Disassembler disassembler3("000000");
    disassembler3.addLiteral("=X'3F'",2,"000006");
    disassembler3.addSymbol("FIRST","000000");
    disassembler3.addSymbol("LOOP","00000B");
    disassembler3.addSymbol("COUNT","00001E");
    disassembler3.addSymbol("TABLE","000021");
    disassembler3.addSymbol("TABLE2","001791");
    disassembler3.addSymbol("TOTAL","002F01");
    processTextLine("T0000001E0500000320003F691017911BA0131BC0002F200A3B2FF40F102F014F0000",&disassembler3);
    vector<InstructionLine> line = disassembler3.getInstructions();
    for(InstructionLine instruction : line){
        cout<<"************************************************"<<endl;
        cout << "Format Type: " << instruction.type << endl;
        cout << "address: "<< instruction.address << endl;
        cout << "Label: "<< instruction.label << endl;
        cout << "Mnemonic: " << instruction.mnemonic << endl;
        cout << "Operand Address: " << instruction.operandAddress << endl;
        cout << "Opcode: " << instruction.opCode << endl;

    }


    return 0;
}