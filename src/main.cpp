/***************************************************************
 * Amiel Nava RedID:824264864                                  *
 * Chase Parker RedID:821253141                                *
 * Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060*
 ***************************************************************/
#include <iostream>
#include <sstream>
#include "header.h"
#include "Disassembler.h"
#include "textRecord.h"


int main(int argc, char** argv) {

    if(argc > 1){
        char** c;

        Disassembler dis = read_obj_file(argc,argv);
        write_file(&dis);
    }else{
        const std::string MSG = "No input text file passed.\nPlease run the program with the input textfiles to read from.\n";
        std::cout << MSG;
    }

    /*
    Disassembler disassembler1("000000");
    disassembler1.addHeader("HSUM","000000","002F04");
    disassembler1.addLiteral("=X'3F'", 2, "000006");
    disassembler1.addSymbol("FIRST", "000000");
    disassembler1.addSymbol("LOOP", "00000B");
    disassembler1.addSymbol("COUNT", "00001E");
    disassembler1.addSymbol("TABLE", "000021");
    disassembler1.addSymbol("TABLE2", "001791");
    disassembler1.addSymbol("TOTAL", "002F01");
    processTextLine("T0000001E0500000320003F691017911BA0131BC0002F200A3B2FF40F102F014F0000",&disassembler1);
    vector<InstructionLine> line = disassembler1.getInstructions();
    for(InstructionLine instruction : line){
        cout<<"************************************************"<<endl;
        cout << "Format Type: " << instruction.type << endl;
        cout << "address: "<< instruction.address << endl;
        cout << "Label: "<< instruction.label << endl;
        cout << "Mnemonic: " << instruction.mnemonic << endl;
        cout << "Operand Address: " << instruction.operandAddress << endl;
        cout << "Opcode: " << instruction.opCode << endl;
    }
    */

    /*
    Disassembler disassembler1("000000");
    disassembler1.addLiteral("=X'3F'", 2, "000006");
    disassembler1.addSymbol("FIRST", "000000");
    disassembler1.addSymbol("LOOP", "00000B");
    disassembler1.addSymbol("COUNT", "00001E");
    disassembler1.addSymbol("TABLE", "000021");
    disassembler1.addSymbol("TABLE2", "001791");
    disassembler1.addSymbol("TOTAL", "002F01");
    processTextLine("T0000001E0500000320003F691017911BA0131BC0002F200A3B2FF40F102F014F0000",&disassembler1);
    std::vector<InstructionLine> line = disassembler1.getInstructions();
    for(InstructionLine instruction : line){
        std::cout<<"************************************************"<< std::endl;
        std::cout << "Format Type: " << instruction.type << std::endl;
        std::cout << "address: "<< instruction.address << std::endl;
        std::cout << "Label: "<< instruction.label << std::endl;
        std::cout << "Mnemonic: " << instruction.mnemonic << std::endl;
        std::cout << "Operand Address: " << instruction.operandAddress << std::endl;
        std::cout << "Opcode: " << instruction.opCode << std::endl;
    }
    */

    /*
    std::cout << "EXAMPLE 2#######################################################"<< std::endl;
    Disassembler disassembler2("000000");
    disassembler2.addLiteral("=X'000001'", 6, "000855");
    disassembler2.addLiteral("=X'000007'", 6, "001090");
    disassembler2.addSymbol("FIRST", "000000");
    disassembler2.addSymbol("BADR", "00000A");
    disassembler2.addSymbol("RETADR", "00083E");
    disassembler2.addSymbol("WLOOP", "000849");
    disassembler2.addSymbol("EADR", "00085C");
    processTextLine("T0000000A6910083E174000024000",&disassembler2);
    processTextLine("T0008411BB400050001010005E32009332FFA53AFECDF200000000103101090",&disassembler2);
    processTextLine("T00109003000007",&disassembler2);
    std::vector<InstructionLine> line2 = disassembler2.getInstructions();
    for(InstructionLine instruction : line2){
        std::cout<<"************************************************"<< std::endl;
        std::cout << "Format Type: " << instruction.type << std::endl;
        std::cout << "address: "<< instruction.address << std::endl;
        std::cout << "Label: "<< instruction.label << std::endl;
        std::cout << "Mnemonic: " << instruction.mnemonic << std::endl;
        std::cout << "Operand Address: " << instruction.operandAddress << std::endl;
        std::cout << "Opcode: " << instruction.opCode << std::endl;

    }
    */

    return 0;
}
