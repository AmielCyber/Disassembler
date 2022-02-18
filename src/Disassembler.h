/***************************************************************
 * Amiel Nava RedID:824264864                                  *
 * Chase Parker RedID:821253141                                *
 * Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060*
 ***************************************************************/
#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <vector>
#include <string>
#include <map>


struct InstructionLine{
    int type;
    std::string address;
    std::string label;
    std::string mnemonic;
    std::string operandAddress;
    std::string opCode;
};

struct Literal{
    std::string label;
    int length;
};

class Disassembler{
private:
    int size;
    int progLength;
    std::string PC_Counter;
    std::vector<InstructionLine> line;
    std::map<std::string, InstructionLine> lineMap;
    std::map<int,std::string> symbolTable;
    std::map<int,Literal> literalTable;
    std::map<std::string, int> registerTable;
    int getRegisterValue(std::string regi);
    std::string getOP_Code(std::string byte);
    std::string getNIXBPE(std::string twoBytes);
    void incrementPC(int numOfBytes);
    void addInstruction(int type, std::string address, std::string label, std::string mnemonic,
                        std::string operandAddress, std::string opCode);
    std::string getOperandAddress2(std::string mnemonic, std::string r1, std::string r2);
    std::string getOperandAddress3_4(std::string nixbpe, std::string disp, bool loadIndex, bool loadBase);

public:
    Disassembler(std::string startingAddress);
    std::string getPC();
    void addSymbol(std::string symbol, std::string address);
    void addLiteral(std::string literal, int length, std::string address);
    std::string getMnemonic(std::string op);
    std::string getLabel(int address);
    Literal getLiteral(int address);
    std::vector<InstructionLine> getInstructions();
    int isNextInstructionLiteral();
    int getFormatType(std::string byte);
    void addFormat(std::string opCode, int type);
    void addFormat1(std::string opCode);
    void addFormat2(std::string opCode);
    void addFormat3_4(std::string opCode, int type);
    void addLiteralInstruction(std::string opCode);
    void addSymbolInstructions();
    InstructionLine getInstruction(std::string address);
    InstructionLine getInstruction(int position);
    std::string addZeros(std::string address);
    bool isNextInstructionSymbol();
    int getSize();
    void addHeader(std::string progName, std::string startingAddress, std::string length);
    void addEnd(std::string address);
    void changeOperandAddress(std::string address, std::string newOperandAddress);
    void printAssembler();

};

#endif // ! DISASSEMBLER_H
