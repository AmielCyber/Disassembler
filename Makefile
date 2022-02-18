# Define compiler to be used
 ##############################################################
 # Amiel Nava RedID:824264864                                  #
 # Chase Parker RedID:821253141                                #
 # Kenny Nguyen RedID:821649498 Jeremy Espinosa RedID:821770060#
 ##############################################################
CXX := g++
# non-optional compiler flags
CXXFLAGS := -std=c++11 -g
# output object
OUTPUT := dissem
# Output text from running dissem
OUTPUT_TXT := list.txt
# Source files
SOURCES := $(wildcard ./src/*.cpp)
# Header files
HEADERS := $(wildcard ./src/*.h)

all: $(OUTPUT)

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	rm $(OUTPUT) $(OUTPUT_TXT) 

.PHONY: all
