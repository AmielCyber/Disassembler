#include "header.h"
#include <fstream>
#include <vector>

/*
 *Template function to help format printing out instruction lines
 */

const char space = ' ';
const int width = 8;

template<string> void printLine(string s, const int& width)
{
    cout << left << setw(width) << setfill(space) << s;
}

/*
 * Iterate through InstructionLine and find out what to write to file
 * 
 */
void print_table(vector<InstructionLine> line)
{
    for(int i = 0; i < line.size(); i++)
    {
        string myAddress = line.address;
        string myLabel = line.label;
        string myMnemonic = line.mnemonic;
        string myOperandAddress = line.operandAddress;
        string myOpCode = line.opCode;

        printLine(myAddress, width);
        printLine(myLabel, width);
        printLine(myMnemonic, width);
        printLine(myOperandAddress, width);
        printLine(myOpCode, width);
        cout << endl
    }
}
void write_file()
{

}
