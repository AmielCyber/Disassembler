#include "header.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>

void read_sym_file(int argc, char **argv, Disassembler *disassembler)
{ 
    std::ifstream file(argv[1]);

    if(!file) {
        cout << "Error - Symbol file not found" << endl;
        exit(EXIT_FAILURE);
    }

    std::string str; 
    bool isSym = true;

    while (std::getline(file, str))
    {
        std::istringstream iss(str);
        vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};

        if(tokens.size() == 0) {
            isSym = false;
            continue;
        } else if(tokens[0] == "Name" || tokens[0] == "Symbol") {
            continue;
        }

        if(isSym && tokens.size() >= 2) {
            disassembler->addSymbol(tokens[0],tokens[1]);
             cout << "Symbol: " << tokens[0] << " Value: " << tokens[1] << endl;
        } else if(tokens.size() >= 2) {
            //Adress is key
            disassembler->addLiteral(tokens[0],std::stoi(tokens[1]),tokens[1]);
            cout << "Literal: " << tokens[0] << " Address: " << tokens[2] << endl;
        }

    }
}


void read_obj_file(int argc, char **argv) {

    std::ifstream file(argv[0]);

    if(!file) {
        cout << "Error - No object file found" << endl;
        exit(EXIT_FAILURE);
    }

    std::string str; 

    //Disassembler disassembler = parse_header_line(std::getline(file,str));
    //read_sym_file(argc,argv,&disassembler);

    while (std::getline(file, str))
    {
        // if(str.compare(0,1,"H") == 0) {
        //     cout << "Header processed" << endl;
        // } else
        if(str.compare(0,1,"T") == 0) {
            //processTextLine(str,&disassembler);
            cout << "Text line processed" << endl;
        } else if(str.compare(0,1,"M") == 0) {
            //parse_mod_line(str,&disassembler);
            cout << "Mod record processed" << endl;
        } else if(str.compare(0,1,"E") == 0) {
            //parse_end_line(str,&disassembler);
            cout << "End line processed" << endl;
        }

    }

    //return disassembler;
}


