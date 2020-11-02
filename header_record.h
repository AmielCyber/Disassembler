#include "header.h"
#ifndef HEADER_RECORD_H
#define HEADER_RECORD_H

static Disassembler* parse_header_Line(string line, Disassembler* disassembler) {

//check if the line entered is a header
	if (line.compare(0, 1, "H") == 0) {
		int textLineSize = line.length();               // Get the length of the line.

		if (textLineSize == 19) { //checks to make sure the length of the header is valid
		
			string first6Nibbles(line, 1, 6);  // Get the first 6 nibbles to get what type of mnemonic

			string mnemonic = first6Nibbles; // parses the mnemonic out

			string startingAddress(line, 7, 12);

			string address = startingAddress; //parses the starting address out

			string operationLength(line, 13, 18);

			string length = operationLength; //parses the length of the program out

		}
		else {
		
		cout << "Invalid line sent to text processor!" << endl;
		
			}
		}
	}
	else {
		cout << "Invalid line sent to text processor!" << endl;
		}
	}

	return disassembler;
}

#endif 