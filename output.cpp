#include "header.h"
#include <fstream>
#include <vector>



/*
 * Iterate through InstructionLine and find out what to write to file
 * 
 */
void print_table(vector<InstructionLine> line)
{
    vector<InstructionLine> output;
    for(InstructionLine instruct: line)
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
 *Template function to help format printing out instruction lines
 */

const char space = ' ';
const int width = 8;

template<string> void printLine(string s, const int& width)
{
    file << left << setw(width) << setfill(space) << s;
}

/*
 * create the output file and print the table of instructions
 */
void write_file(string fileName)
{
    std::ofstream file(fileName);
    print_table();
}
