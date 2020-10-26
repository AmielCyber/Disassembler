#include "header.h"
#include <fstream>
#include <string>
#include <sstream>

void read_sym_file(int argc, char **argv)
{ 
    std::ifstream file("/Users/admin/Desktop/CS530 Assessments/Assignment 1/sample.sym.txt");
    std::string str; 
    bool isSym = true;

    while (std::getline(file, str))
    {
        std::istringstream iss(str);
        vector<string> tokens{istream_iterator<string>{iss},istream_iterator<string>{}};

        if(tokens.size() == 0) {
            isSym = false;
            continue;
        } else if(tokens[0] == "Name" || tokens[0] == "Sybmbol") {
            continue;
        }

        if(isSym && tokens.size() >= 2) {
             cout << "Symbol: " << tokens[0] << " Value: " << tokens[1] << endl;
        } else if(tokens.size() >= 2) {
            cout << "Literal: " << tokens[0] << " Address: " << tokens[2] << endl;
        }

    }
}


