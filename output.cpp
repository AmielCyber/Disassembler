#include "header.h"
#include <fstream>
#include <iostream>
#include <iomanip>



/*
 *Template function to help format printing out instruction lines
 */



template<typename T> void printLine(T t, const int& width)
{
    cout << left << setw(width) << setfill(space) << t;
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
    cout << endl;
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
    myDisassembler->addEnd("000000");
    file.close();
}

