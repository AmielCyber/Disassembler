# Define compiler to be used
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
