#ifndef ASSEMBLER_H
#define ASSEMBLER_H

using namespace std;
#include <vector> 
#include <string>
#include <map>

class Assembler{
	private:
		struct assemblyLine{
			int type;
			string address;
			string label;
			string mnemonic;
			string operandAddress;
			string opCode;
		};
		vector<assemblyLine> line;
		map<string, assemblyLine> lineMap;
		int size;
	public:
		Assembler();
		void addHeader(string header);
		void addEnd(string end);
		void addFormat1(string opCode);
		void addFormat2(string opCode);
		void addFormat3(string opCode);
		void addFormat4(string opCode);
		string getNextAddress();
		int getFormatType(string op);
		void changeOperandAddress(string address, string newOperandAddress);
		void changeLabel(string address, string newLabel);
		assemblyLine getLine(string operandAddress);
		assemblyLine getLine(int position);
		void printAssembler();
		
};

#endif // ! ASSEMBLER_H
