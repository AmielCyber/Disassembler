#include "header.h"
#include <string>


/*
* Parse through the end record and check if it is the correct length, save the starting address
*/
void parse_end_line(string line)
{
  if(line.compare(0, 1, "E") == 0)
  {
    int length = line.length();
    if(length == 7)
    {
      string startAddress = line.substr(1, length);
    }
    else
    {
      cout << "Invalid line" << endl;
    }
  }
  else
  {
    cout << "Invalid line" << endl;
  }
  
  
}
