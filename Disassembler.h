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

class Disassembler{
private:
    int size;
    string PC_Counter;
    vector<InstructionLine> line;
    map<string, InstructionLine> lineMap;
    map<string,string> symbolTable;
    map<string,string> literalTable;
    map<string, string> registerTable;
    string getPC();
    string getRegisterValue(string regi);
    string getOP_Code(string byte);
    string getNIXBPE(string twoBytes);
    void incrementPC(int numOfBytes);
    void addInstruction(int type, string address, string label, string mnemonic,
                        string operandAddress, string opCode);
    string getOperandAddress2(string mnemonic, string r1, string r2);
    string getOperandAddress3(string nixbpe, string disp);

public:
    Disassembler(string startingAddress);
    void addSymbol(string symbol, string address);
    void addLiteral(string literal, string address);
    void addHeader(string header);
    void addFormat1(string opCode);
    void addFormat2(string opCode);
    void addFormat3(string opCode);
    void addFormat4(string opCode);
    void addEnd(string end);
    int getFormatType(string byte);
    string getMnemonic(string op);
    void changeOperandAddress(string address, string newOperandAddress);
    string getLabel(string address);
    string getLiteral(string address);
    InstructionLine getInstruction(string address);
    InstructionLine getInstruction(int position);
    void printAssembler();

};

#endif // ! DISASSEMBLER_H
