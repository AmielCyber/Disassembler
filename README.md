# Disassembler

## Program Summary
A disassembler for the SIC/XE machine architecture. The disassembler opens a text file containing a valid object 
program and its accompanying symbol file. Next, the disassembler will disassemble the program code back to object code or the SIC/XE language source file 
into a text file named `list.txt`.
![objCodeToSource](/images/diagram.png)

## Objective
To read an object code file along with its symbol file in order to produce an assembly listing file or the SIC/XE source code.

## Compiling and Running Instructions
### Compiling Instructions
In the root directory of this repository run the following command in your terminal:
```bash
make
```
An executable file should be created named `dissem`.

To clean up any created files while running the disassembler program, enter the following in your terminal: 
```bash
make clean
```
Make clean will remove the executable and the output file created named `list.txt`.

### Running Instructions
After compiling the program using `make`, run the program properly by passing two arguments to the executable.
* The first argument passed should be the object program file.
    * One object file is provided in the directory `input/` with the file name `sample-obj.txt`
* The second argument passed should be the symbol file that accompanies the project code file. 
    * One symbol file is provided in the directory `input/` with the file name `sample.sym.txt`

To run the program with the default text file enter the following in your terminal:
```bash
./dissem ./input/sample-obj.txt ./input/sample.sym.txt
```

Or move the text files above to the root directory of this repository and enter the following:
```bash
./dissem sample-obj.txt sample.sym.txt 
```

## Repository Overview
```bash
Disassembler
├── LICENSE
├── Makefile
├── README.md
├── doc
│   ├── Pair-Programmer_Affidavit.docx
│   └── README.pdf
├── images
│   ├── diagram.png
│   ├── instructionLine.png
│   ├── joinModules.png
│   └── overviewDesign.png
├── input
│   ├── sample-obj.txt
│   ├── sample.lis.txt
│   ├── sample.sic.txt
│   └── sample.sym.txt
└── src
    ├── Disassembler.cpp
    ├── Disassembler.h
    ├── end_record.cpp
    ├── header.h
    ├── header_record.h
    ├── input.cpp
    ├── main.cpp
    ├── mod_record.cpp
    ├── mod_record.h
    ├── output.cpp
    └── textRecord.h
```
* `input.cpp` reads the object program file and the symbol file
* `Disassembler.cpp` decodes the object program and turns it into source code
* `*_record.cpp` handles the type of record file
* `output.cpp` prints the stored source object from what the disassembler produced into a source code file
* `input/` the input files for our program
After the program is done running a SIC/XE source code will be created based on the program code named `list.txt` at 
the repository root directory.

## Contributors 
* [Amiel Nava](https://github.com/AmielCyber)
* [Kenny Nguyen](https://github.com/kennydn99)
* [Jeremy Espinosa](https://github.com/Heremy)
* [Chase Parker](https://github.com/alanparkerc)

## Program Design
We also split up the work by disassembler, input, header record, text record, end record and output. 
We ended up changing some variable types and method names.
![overviewDesign](/images/overviewDesign.png)

We then setup a structure for the assembly line code, that way the output method can just iterate assembly code lines 
and print it or write it.
![instructionLine](/images/instructionLine.png)

Finally, we put all the parts together to have a running program.
![joinModules](/images/joinModules.png)

## Sources
SIC/XE machine architecture is from the textbook *System Software An Introduction to Systems Programming 3rd Edition* 
by Leland Beck.
