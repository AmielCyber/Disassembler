#ifndef ASSEMBLER_H
#define ASSEMBLER_H

using namespace std;
#include <vector> 
#include <string>
#include <map>

struct AssemblyLine{
    int type;
    string address;
    string label;
    string mnemonic;
    string operandAddress;
    string opCode;
};

class Assembler{
	private:
		vector<AssemblyLine> line;
		map<string, AssemblyLine> lineMap;
		int size;
		string getNextAddress();
		void addAssemblyLine(int type, string address, string label, string mnemonic,
				string operandAddress, string opCode);
	public:
		Assembler();
		void addHeader(string header);
		void addEnd(string end);
		void addFormat1(string opCode);
		void addFormat2(string opCode);
		void addFormat3(string opCode);
		void addFormat4(string opCode);
		int getFormatType(string op);
		string getMnemonic(string op);
		void changeOperandAddress(string address, string newOperandAddress);
		void changeLabel(string address, string newLabel);
        AssemblyLine getLine(string address);
        AssemblyLine getLine(int position);
		void printAssembler();
		
};

#endif // ! ASSEMBLER_H
