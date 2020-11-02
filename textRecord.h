#include "header.h"
#ifndef TEXTRECORD_H
#define TEXTRECORD_H
/**
 * processTextLine will take a text line from the object code file and
 * add each instruction found in the opcode.
 * @param line          The string line of the object file e.g "T......."
 * @param disassembler  The disassembler object we will be using to store the
 *                      assembly code instructions.
 */
static void processTextLine(string line,Disassembler *disassembler){
    // Check if the object code is a text record
    if(line.compare(0,1,"T") == 0){
        int textLineSize = line.length() - 9;               // Get the length of the text record without the headers
        string objCodeLine(line,9,textLineSize);       // Trim the object code line
        // Go through all object codes
        while(textLineSize > 0){
            // Check if next instruction is a literal and if it is get the number of nibbles for the opcode
            int literalSize = disassembler->isNextInstructionLiteral();

            int nibbles;
            if(literalSize>0){
                // If next instruction is a literal then get the opcode and added to the assembly code
                nibbles = literalSize;
                string opCode(objCodeLine,0,nibbles);
                disassembler->addLiteralInstruction(opCode);
            }else{
                // If there is no literal opcode then just add the instruction based on the opcode
                string first3Nibbles(objCodeLine,0,3);  // Get the first 3 nibbles to get what type of format
                int type = disassembler->getFormatType(first3Nibbles);  // Get the format type number
                nibbles = 2 * type;                         // Get number of nibbles = 2 * Bytes
                string opCode(objCodeLine,0,nibbles);      // Get a chunk of an object code depending on format type
                // Call disassembler addFormat function to add format opcode line to our assembly code
                disassembler->addFormat(opCode,type);
            }

            textLineSize -= nibbles;             // Decrease the size of our text record line
            objCodeLine.erase(0,nibbles);   // Erase the opcode we already added from our text record line
        }
        disassembler->addSymbolInstructions();
    }
    else{
        cout << "Invalid line sent to text processor!" << endl;
    }
}

#endif // !TEXTRECORD_H
