/***************************************************************
 * Amiel Nava RedID:824264864                                  *
 * Chase Parker RedID:821253141                                *
 * Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060*
 ***************************************************************/
#include "header.h"
#include <fstream>
#include <iostream>
#include <iomanip>


/*
 *Template function to help format printing out instruction lines
 */
template<typename T> void printLine(T t, const int& width)
{
    std::cout << std::left << std::setw(width) << std::setfill(space) << t;
}

/*
 * Print all elements of Instructionline
 * 
 */
void print_table(InstructionLine instruct)
{
    printLine(instruct.address, width);
    printLine(instruct.label, width);
    printLine(instruct.mnemonic, width);
    printLine(instruct.operandAddress, width);
    printLine(instruct.opCode, width);
    std::cout << std::endl;
}

/*
 * create the output file and print the table of instructions
 */
void write_file(Disassembler *myDisassembler)
{
    std::ofstream file("list.txt");
    freopen("list.txt", "w", stdout);     //redirect cout to write into filename
    
    for(int i = 0; i < myDisassembler->getSize(); i++)
    {
        print_table(myDisassembler->getInstruction(i));
    }
    file.close();
}
