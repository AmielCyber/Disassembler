/***************************************************************
 * Amiel Nava RedID:824264864                                  *
 * Chase Parker RedID:821253141                                *
 * Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060*
 ***************************************************************/
#include "header.h"
#include "header_record.h"
#include "textRecord.h"
#include "mod_record.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>


void read_sym_file(int argc, char **argv, Disassembler *disassembler)
{
    std::string fileName = *(argv+2);
    std::ifstream file(fileName);

    if(!file) {
        std::cout << "Error - Symbol file not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string str; 
    bool isSym = true;

    while (std::getline(file, str))
    {
        std::istringstream iss(str);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>{}};

        if(tokens.size() == 0) {
            isSym = false;
            continue;
        } else if(tokens[0] == "Name" || tokens[0] == "Symbol") {
            continue;
        }

        if(isSym && tokens.size() >= 2) {
            disassembler->addSymbol(tokens[0],tokens[1]);
             //cout << "Symbol: " << tokens[0] << " Value: " << tokens[1] << endl;
        } else if(tokens.size() >= 2) {
            //Adress is key
            disassembler->addLiteral(tokens[0],std::stoi(tokens[1]),tokens[2]);
            //cout << "Literal: " << tokens[0] << " Address: " << tokens[2] << endl;
        }

    }
}


Disassembler read_obj_file(int argc, char **argv) {
    std::string fileName = *(argv+1);
    std::ifstream file(fileName);


    if(!file) {
        std::cout << "Error - No object file found" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string str; 
    std::getline(file,str);
    str.erase(str.size() - 1);
    Disassembler disassembler = parse_header_line(str);
    read_sym_file(argc,argv,&disassembler);


    while (std::getline(file, str))
    {

        str.erase(str.size() - 1);

        if(str.compare(0,1,"T") == 0) { 
            processTextLine(str.erase(str.size() - 1),&disassembler);
            std::cout << "Text line processed" << std::endl;
        } else if(str.compare(0,1,"M") == 0) {
            //parse_mod_line(str,&disassembler);
            std::cout << "Mod record processed" << std::endl;
        } else if(str.compare(0,1,"E") == 0) {
            parse_end_line(str,&disassembler);
            std::cout << "End line processed" << std::endl;
        }

    }

    return disassembler;
}


