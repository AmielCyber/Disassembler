#ifndef ASSEMBLER_H
#define ASSEMBLER_H

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

class Assembler{
private:
    vector<InstructionLine> line;
    map<string, InstructionLine> lineMap;
    map<string,string> symbolTable;
    map<string,string> literalTable;
    string getNextAddress();
    string getFormat2Labels(string mnemonic, string r1, string r2);
    void addInstruction(int type, string address, string label, string mnemonic,
                        string operandAddress, string opCode);
    void incrementPC_Counter(int formatType);
    int size;
    string PC_Counter;
public:
    Assembler(string startingAddress);
    void addSymbol(string symbol, string address);
    void addLiteral(string literal, string address);
    void addHeader(string header);
    void addFormat1(string opCode);
    void addFormat2(string opCode);
    void addFormat3(string opCode);
    void addFormat4(string opCode);
    void addEnd(string end);
    int getFormatType(string byte);
    string getOP_Code(string byte);
    string getMnemonic(string op);
    void changeOperandAddress(string address, string newOperandAddress);
    string getLabel(string address);
    string getLiteral(string address);
    InstructionLine getInstruction(string address);
    InstructionLine getInstruction(int position);
    void printAssembler();

};

#endif // ! ASSEMBLER_H