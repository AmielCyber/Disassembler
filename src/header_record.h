/***************************************************************
 * Amiel Nava RedID:824264864                                  *
 * Chase Parker RedID:821253141                                *
 * Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060*
 ***************************************************************/
#include "header.h"
#include "Disassembler.h"
#ifndef HEADER_RECORD_H
#define HEADER_RECORD_H


static Disassembler parse_header_line(std::string line) {

	//check if the line entered is a header
	if (line.compare(0, 1, "H") == 0) {
		int textLineSize = line.length();               // Get the length of the line.
		//if (textLineSize == 19) { //checks to make sure the length of the header is valid
        std::string startingAddress(line, 7, 6);
		Disassembler disassembler(startingAddress);

        std::string first6Nibbles(line, 1, 6);  // Get the first 6 nibbles to get what type of mnemonic
		//disassembler.mnemonic = first6Nibbles; // parses the mnemonic out
        std::string operationLength(line, 13, 6);

        std::string length = operationLength; //parses the length of the program out
		disassembler.addHeader(first6Nibbles, startingAddress, length);
		return disassembler;

	}
	//else {

	//cout << "Invalid line sent to text processor!" << endl;

	//}
//}
	else {
        std::cout << "Invalid line sent to text processor!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

#endif 
