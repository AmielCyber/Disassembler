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
    string getPC();
    void addSymbol(string symbol, string address);
    void addLiteral(string literal, int length, string address);
    string getMnemonic(string op);
    string getLabel(int address);
    Literal getLiteral(int address);
    vector<InstructionLine> getInstructions();
    int isNextInstructionLiteral();
    int getFormatType(string byte);
    void addFormat(string opCode, int type);
    void addFormat1(string opCode);
    void addFormat2(string opCode);
    void addFormat3_4(string opCode, int type);
    void addLiteralInstruction(string opCode);
    void addSymbolInstructions();
    InstructionLine getInstruction(string address);
    InstructionLine getInstruction(int position);
    bool isNextInstructionSymbol();
    int getSize();
    void addHeader(string header);
    void addEnd(string end);
    void changeOperandAddress(string address, string newOperandAddress);
    void printAssembler();

};

#endif // ! DISASSEMBLER_H