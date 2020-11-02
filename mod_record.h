#include "header.h"
#ifndef MOD_RECORD_H
#define MOD_RECORD_H

static Disassembler* parse_mod_Line(string line, Disassembler* disassembler) {

//check if the line entered was a modification record
	if (line.compare(0, 1, "M") == 0) {

		int textLineSize = line.length();  // Get the length of the text record without the headers

		if (textLineSize == 17) { //checks for valid input

			string first6Nibbles(line, 1, 6);  // Get the first 6 nibbles to get relative address to be modified

			string address = first6Nibbles; // parses the relative address out.

			string lengthOfField(line, 7, 8); //gets the nibbles for the length of field

			string length = lengthOfField; //parses length of the field out

			string modificationFlag(line, 9); // parses out the modification flag

			string externalSymbol(line, 10, 15); // parses out the external symbol

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

static Disassembler* modify_address(int add_loc, Disassembler* disassembler) { //modifys the address

	string address = disassembler->address;
	return disassembler;

}

#endif 