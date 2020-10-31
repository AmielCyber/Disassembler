#include "header.h"
#ifndef TEXTRECORD_H
#define TEXTRECORD_H
static void processTextLine(string line,Disassembler *disassembler){
    if(line.compare(0,1,"T") == 0){
        int textLineSize = line.length() - 9;
        string objCodeLine(line,9,textLineSize);
        while(textLineSize > 0){
            string first3Nibbles(objCodeLine,0,3);
            int type = disassembler->getFormatType(first3Nibbles);
            int nibbles = 2 * type;
            string opCode(objCodeLine,0,nibbles);
            switch (type) {
                case 1:
                    disassembler->addFormat1(opCode);
                    break;
                case 2:
                    disassembler->addFormat2(opCode);
                    break;
                case 3:
                    disassembler->addFormat3(opCode);
                    break;
                case 4:
                    disassembler->addFormat4(opCode);
                    break;
                default:
                    cout << "Invalid op code found!" << endl;
                    break;
            }
            textLineSize -= nibbles;
            objCodeLine.erase(0,nibbles);
        }
    }else{
        cout << "Invalid line sent to text processor!" << endl;
    }
}

#endif // !TEXTRECORD_H
