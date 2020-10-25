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
		int size;
		string getNextAddress();
		void addInstruction(int type, string address, string label, string mnemonic,
                            string operandAddress, string opCode);
	public:
		Assembler();
		void addSymbol(string symbol, string address);
		void addLiteral(string literal, string address);
		void addHeader(string header);
		void addFormat1(string opCode);
		void addFormat2(string opCode);
		void addFormat3(string opCode);
		void addFormat4(string opCode);
        void addEnd(string end);
		int getFormatType(string op);
		string getMnemonic(string op);
		void changeOperandAddress(string address, string newOperandAddress);
		string getLabel(string address);
		string getLiteral(string address);
        InstructionLine getInstruction(string address);
        InstructionLine getInstruction(int position);
		void printAssembler();
		
};

#endif // ! ASSEMBLER_H
