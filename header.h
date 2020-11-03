#ifndef HEADER_H
#define HEADER_H
#include <string>		// To use the string object class
#include <iostream>		// To use cout and cin object
#include <stdio.h>		// To use standard input and output object
#include <map>
#include <vector>
#include <sstream>
#include "Disassembler.h"

using namespace std;



static map<string,  string> mnemonicMap = {
        {"18","ADD"},	    {"68","LDB"},   {"0C","STA"},
        {"58","ADDF"},	{"50","LDCH"},  {"78","STB"},
        {"90","ADDR"},	{"70","LDF"},   {"54","STCH"},
        {"4O","AND"},	    {"08","LDL"},   {"80","STF"},
        {"B4","CLEAR"},	{"6C","LDS"},   {"D4","STI"},
        {"28","COMP"},	{"74","LDT"},   {"14","STL"},
        {"88","COMPF"},	{"04","LDX"},   {"7C","STS"},
        {"A0","COMPR"},	{"D0","LPS"},   {"E8","STSW"},
        {"24","DIV"},	    {"20","MUL"},   {"84","STT"},
        {"64","DIVF"},	{"60","MULF"},  {"10","STX"},
        {"9C","DIVR"},	{"98","MULR"},  {"1C","SUB"},
        {"C4","FIX"},	    {"C8","NORM"},  {"5C","SUBF"},
        {"C0","FLOAT"},	{"44","OR"},    {"94","SUBR"},
        {"F4","HIO"},	    {"D8","RD"},    {"B0","SVC"},
        {"3C","J"},		{"AC","RMO"},   {"E0","TD"},
        {"30","JEQ"},   	{"4C","RSUB"},  {"F8","TIO"},
        {"34","JGT"},	    {"A4","SHIFTL"},{"2C","TIX"},
        {"38","JLT"},	    {"A8","SHIFTR"},{"B8","TIXR"},
        {"48","JSUB"},	{"F0","SIO"},   {"DC","WD"},
        {"00","LDA"},	    {"EC","SSK"}
};

static map<string, int>  formatTypeMap= {
        {"18",3},	{"68",3},   {"0C",3},
        {"58",3},	{"50",3},   {"78",3},
        {"90",2},	{"70",3},   {"54",3},
        {"4O",3},	{"08",3},   {"80",3},
        {"B4",2},	{"6C",3},   {"D4",3},
        {"28",3},	{"74",3},   {"14",3},
        {"88",3},	{"04",3},   {"7C",3},
        {"A0",2},	{"D0",3},   {"E8",3},
        {"24",1},	{"20",3},   {"84",3},
        {"64",1},	{"60",3},   {"10",3},
        {"9C",1},	{"98",2},   {"1C",3},
        {"C4",1},	{"C8",1},   {"5C",3},
        {"C0",1},	{"44",3},   {"94",2},
        {"F4",1},	{"D8",3},   {"B0",2},
        {"3C",3},	{"AC",2},   {"E0",3},
        {"30",3},	{"4C",3},   {"F8",1},
        {"34",3},	{"A4",2},   {"2C",3},
        {"38",3},	{"A8",2},   {"B8",2},
        {"48",3},	{"F0",1},   {"DC",3},
        {"00",3},	{"EC",3}
};

static map<string,string> SIC_XE_RegisterMap = {
        {"0","A"},{"1","X"},{"2","L"},
        {"3","B"},{"4","S"},{"5","T"},
        {"6","F"},
};

static string hexToBinary(string hexidecimal){
    int decimalVal;
    string binaryVal;
    istringstream(hexidecimal) >> hex >> decimalVal;
    switch (decimalVal) {
        case 0:
            binaryVal = "0000";
            break;
        case 1:
            binaryVal = "0001";
            break;
        case 2:
            binaryVal = "0010";
            break;
        case 3:
            binaryVal = "0011";
            break;
        case 4:
            binaryVal = "0100";
            break;
        case 5:
            binaryVal = "0101";
            break;
        case 6:
            binaryVal = "0110";
            break;
        case 7:
            binaryVal = "0111";
            break;
        case 8:
            binaryVal = "1000";
            break;
        case 9:
            binaryVal = "1001";
            break;
        case 10:
            binaryVal = "1010";
            break;
        case 11:
            binaryVal = "1011";
            break;
        case 12:
            binaryVal = "1100";
            break;
        case 13:
            binaryVal = "1101";
            break;
        case 14:
            binaryVal = "1110";
            break;
        case 15:
            binaryVal = "1111";
            break;
        default:
            break;
    }
    return binaryVal;
}

static string getOP(string op){
    int decimalVal;
    string firstNibble(op,0,1);
    string secondNibble(op,1,1);
    istringstream(secondNibble) >> hex >> decimalVal;

    if(decimalVal > 11){
        secondNibble = "C";
    }else if(decimalVal > 7){
        secondNibble = "8";
    }else if(decimalVal > 3){
        secondNibble = "4";
    }else{
        secondNibble = "0";
    }
    string opCode(firstNibble + secondNibble);

    return opCode;
}

static const char space = ' ';
static const int width = 10;


void read_sym_file(int argc, char **argv);
void insert_symbols(string  line);
Disassembler read_obj_file(int argc, char **argv);
/* Function Prototype Declarations for header_record.cpp*/
static Disassembler parse_header_line(string line);
/* Function Prototype Declarations for text_record.cpp*/
static void processTextLine(string line,Disassembler *disassembler);
void processObjectCode(int byte_length, string op_code);
void format1(string opCode);
void format2(string opCode);
void format3(string opCode);
void format4(string opCode);
bool validateObjCode(string op_code);
/* Function Prototype Declarations for mod_rec.cpp*/
void parse_mod_line(string line);
void modify_address(int add_loc);
/* Function Prototype Declarations for header_record.cpp*/
void parse_end_line(string line, Disassembler *disassember);
/* Function Prototype Declarations for output.cpp*/
template<typename T> void printLine(T t, const int& width);
void print_table(InstructionLine instruct);
void write_file(Disassembler *myDisassembler);









#endif