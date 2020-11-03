# Define compiler to be used
 ##############################################################
 # Amiel Nava RedID:824264864                                  #
 # Chase Parker RedID:821253141                                #
 # Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060#
 ##############################################################
GCC := g++

OUTPUT := dissem
OUTPUT_TXT := list.txt
SOURCES := $(wildcard *.cpp)
CCFLAGS := -std=c++11 -g

all: $(OUTPUT)

$(OUTPUT):
	$(GCC) -o $(OUTPUT) $(CCFLAGS) $(SOURCES)

clean:
	rm $(OUTPUT) $(OUTPUT_TXT) 

.PHONY: all
