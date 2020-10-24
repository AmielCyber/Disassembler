#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

/* Valid Op codes */
const static string ops[] = {
"18", "58", "90", "40", "B4", "28",
"88", "A0", "24", "64", "9C", "C4",
"C0", "F4", "3C", "30", "34", "38",
"48", "00", "68", "50", "70", "08",
"6C", "74", "04", "D0", "20", "60",
"98", "C8", "44", "D8", "AC", "4C",
"A4", "A8", "F0", "EC", "0C", "78",
"54", "80", "D4", "14", "7C", "E8",
"84", "10", "1C", "5C", "94", "B0",
"E0", "F8", "2C", "B8", "DC"
};
/* Valid Mnemonics table */ 
const static string mnemonics[] = {
"ADD", "ADDF", "ADDR", "AND", "CLEAR", "COMP",
"COMPF", "COMPR", "DIV", "DIVF", "DIVR", "FIX",
"FLOAT", "HIO", "J", "JEQ", "JGT", "JLT",
"JSUB", "LDA", "LDB", "LDCH", "LDF", "LDL",
"LDS", "LDT", "LDX", "LPS", "MUL", "MULF",
"MULR", "NORM", "OR", "RD", "RMO", "RSUB",
"SHIFTL", "SHIFTR", "SIO", "SSK", "STA", "STB",
"STCH", "STF", "STI", "STL","STS", "STSW",
"STT", "STX", "SUB", "SUBF", "SUBR", "SVC",
"TD", "TIO", "TIX", "TIXR", "WD"
};

/* Function Prototype Declarations for input.cpp*/
void read_obj_file(int argc, char **argv);
void read_sym_file(int argc, char **argv);
void insert_symbols(string  line);
/* Function Prototype Declarations for header_record.cpp*/
void parse_header_line(string line);
/* Function Prototype Declarations for text_record.cpp*/
void process_text_line(string line);
void process_obj_code(int byte_length, string op_code);
bool validate_obj_code(string op_code);
/* Function Prototype Declarations for mod_rec.cpp*/
void parse_mod_line(string line);
void modify_address(int add_loc);
/* Function Prototype Declarations for header_record.cpp*/
void parse_end_line(string line);
/* Function Prototype Declarations for output.cpp*/
void print_table();
void write_file();









#endif
