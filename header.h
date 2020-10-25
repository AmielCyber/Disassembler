#ifndef HEADER_H
#define HEADER_H
#include <string>		// To use the string object class
#include <iostream>		// To use cout and cin object
#include <stdio.h>		// To use standard input and output object
#include <map>
#include <vector>

using namespace std;

map<string,  string> mnemonic = {
	{"18","ADD"},	{"68","LDB"},	{"0C","STA"},
	{"58","ADDF"},	{"50","LDCH"},  {"78","STB"}, 
	{"90","ADDR"},	{"70","LDF"},   {"54","STCH"},
	{"4O","AND"},	{"08","LDL"},   {"80","STF"},
	{"B4","CLEAR"},	{"6C","LDS"},   {"D4","STI"},
	{"28","COMP"},	{"74","LDT"},   {"14","STL"},
	{"88","COMPF"},	{"04","LDX"},   {"7C","STS"},
	{"A0","COMPR"},	{"D0","LPS"},   {"E8","STSW"},
	{"24","DIV"},	{"20","MUL"},   {"84","STT"},
	{"64","DIVF"},	{"60","MULF"},  {"10","STX"},
	{"9C","DIVR"},	{"98","MULR"},  {"1C","SUB"},
	{"C4","FIX"},	{"C8","NORM"},  {"5C","SUBF"},
	{"C0","FLOAT"},	{"44","OR"},    {"94","SUBR"},
	{"F4","HIO"},	{"D8","RD"},    {"B0","SVC"},
	{"3C","J"},		{"AC","RMO"},   {"E0","TD"},
	{"30","JEQ"},	{"4C","RSUB"},  {"F8","TIO"},
	{"34","JGT"},	{"A4","SHIFTL"},{"2C","TIX"},
	{"38","JLT"},	{"A8","SHIFTR"},{"B8","TIXR"},
	{"48","JSUB"},	{"F0","SIO"},   {"DC","WD"},
	{"00","LDA"},	{"EC","SSK"}
};

map<string, int>  formatType= {
	{"18",3},	{"68",3},	{"0C",3},
	{"58",3},	{"50",3},	{"78",3}, 
	{"90",2},	{"70",3},   {"54",3},
	{"4O",3},	{"08",3},   {"80",3},
	{"B4",2},	{"6C",3},   {"D4",3},
	{"28",3},	{"74",3},   {"14",3},
	{"88",3},	{"04",3},   {"7C",3},
	{"A0",2},	{"D0",3},   {"E8",3},
	{"24",1},	{"20",3},   {"84",3},
	{"64",1},	{"60",3},	{"10",3},
	{"9C",1},	{"98",2},	{"1C",3},
	{"C4",3},	{"C8",1},	{"5C",3},
	{"C0",3},	{"44",3},   {"94",2},
	{"F4",3},	{"D8",3},   {"B0",2},
	{"3C",3},	{"AC",2},   {"E0",3},
	{"30",3},	{"4C",3},	{"F8",1},
	{"34",3},	{"A4",2},	{"2C",3},
	{"38",3},	{"A8",2},	{"B8",2},
	{"48",3},	{"F0",1},   {"DC",3},
	{"00",3},	{"EC",3}
};


void read_sym_file(int argc, char **argv);
void insert_symbols(string  line);
/* Function Prototype Declarations for header_record.cpp*/
void parse_header_line(string line);
/* Function Prototype Declarations for text_record.cpp*/
void process_text_line(string line);
void process_obj_code(int byte_length, string op_code);
void format_1(string opCode);
void format_2(string opCode);
void format_3(string opCode);
void format_4(string opCode);

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
