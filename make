# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRC_FILES = testDrive.cpp Profile.cpp myADT.cpp

# Header files
HEADER_FILES = Profile.h myADT.h

# Object files (automatically generated from source files)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Executable name
EXECUTABLE = testDriver

# Default target
all: $(EXECUTABLE)

# Linking object files to create the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_FILES)

# Compiling source files into object files
%.o: %.cpp $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up intermediate object files and the executable
clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

.PHONY: all clean
