#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

using namespace std;
#include <vector>
#include <string>
#include <map>

struct InstructionLine{
    int type;
    string address;
    string label;
    string mnemonic;
    string operandAddress;
    string opCode;
};

struct Literal{
    string label;
    int length;
};

class Disassembler{
private:
    int size;
    string PC_Counter;
    vector<InstructionLine> line;
    map<string, InstructionLine> lineMap;
    map<int,string> symbolTable;
    map<int,Literal> literalTable;
    map<string, int> registerTable;
    string getPC();
    int getRegisterValue(string regi);
    string getOP_Code(string byte);
    string getNIXBPE(string twoBytes);
    void incrementPC(int numOfBytes);
    void addInstruction(int type, string address, string label, string mnemonic,
                        string operandAddress, string opCode);
    string getOperandAddress2(string mnemonic, string r1, string r2);
    string getOperandAddress3_4(string nixbpe, string disp, bool loadIndex, bool loadBase);

public:
    Disassembler(string startingAddress);
    void addSymbol(string symbol, string address);
    void addLiteral(string literal, int length, string address);
    void addHeader(string header);
    void addFormat1(string opCode);
    void addFormat2(string opCode);
    void addFormat3_4(string opCode, int type);
    void addEnd(string end);
    int getFormatType(string byte);
    string getMnemonic(string op);
    void changeOperandAddress(string address, string newOperandAddress);
    string getLabel(int address);
    Literal getLiteral(int address);
    InstructionLine getInstruction(string address);
    InstructionLine getInstruction(int position);
    vector<InstructionLine> getInstructions();
    int isNextInstructionLiteral();
    void addLiteralInstruction(string opCode);
    void addSymbolInstructions();
    void printAssembler();

};

#endif // ! DISASSEMBLER_H