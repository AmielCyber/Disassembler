/***************************************************************
 * Amiel Nava RedID:824264864                                  *
 * Chase Parker RedID:821253141                                *
 * Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060*
 ***************************************************************/
#include "header.h"
#ifndef MOD_RECORD_H
#define MOD_RECORD_H


static Disassembler* modify_address(std::string relativeAddress, std::string lengthOffield, 
                                    std::string modificationFlag, std::string externalSymbol, 
                                    Disassembler* disassembler) { //modifys the address
    return disassembler;
}

static void parse_mod_line(std::string line, Disassembler* disassembler) {

//check if the line entered was a modification record
    if (line.compare(0, 1, "M") == 0) {
        int textLineSize = line.length();  // Get the length of the text record without the headers
         //checks for valid input
            std::string first6Nibbles(line, 1, 6);  // Get the first 6 nibbles to get relative address to be modified
            std::string address = first6Nibbles; // parses the relative address out.
            std::string lengthOfField(line, 7, 1); //gets the nibbles for the length of field
            std::string length = lengthOfField; //parses length of the field out
            std::string modificationFlag(line, 9); // parses out the modification flag
            std::string externalSymbol(line, 10, 4); // parses out the external symbol
            disassembler = modify_address(first6Nibbles, lengthOfField, modificationFlag, externalSymbol, disassembler);
    } else {
            std::cout << "Invalid line sent to text processor!" << std::endl;
            exit(0);
    }
}

#endif 
