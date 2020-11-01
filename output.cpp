#include "header.h"
#include <fstream>
#include <vector>
#include <iostream>


const char space = ' ';
const int width = 8;
/*
 *Template function to help format printing out instruction lines
 */



template<typename T> void printLine(T t, const int& width)
{
    cout << left << setw(width) << setfill(space) << t;
}
/*
 * Iterate through InstructionLine and find out what to write to file
 * 
 */
void print_table(vector<InstructionLine> line)
{
    vector<InstructionLine> output;
    for(InstructionLine instruct : line)
    {
        printLine(instruct.address, width);
        printLine(instruct.label, width);
        printLine(instruct.mnemonic, width);
        printLine(instruct.operandAddress, width);
        printLine(instruct.opCode, width);
        cout << endl;
    }
}



/*
 * create the output file and print the table of instructions
 */
void write_file(string fileName, Disassembler myDisassembler)
{
    std::ofstream file(fileName);
    for(int i = 0; i < myDisassembler.getSize(); i++)
    {
        print_table(myDisassembler.getInstruction(i));
    }
    
}

