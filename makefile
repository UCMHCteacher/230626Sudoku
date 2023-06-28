# DIRECTORIES
SRC_DIR = ./src
INCLUDE_DIR = ./include
BIN_DIR = ./bin
OBJ_DIR = ./obj

MAINSRC_DIR = $(SRC_DIR)/main
TESTSRC_DIR = $(SRC_DIR)/test

# COMPILER
CC = g++

# PE FILENAME
EXE = sudoku.exe

# computed filenames
MAINSRCS = $(wildcard $(MAINSRC_DIR)/*.cpp)
MAINOBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(MAINSRCS)))

# TESTSRCS = $(wildcard $(TESTSRC_DIR)/*.cpp)
# TESTOBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(TESTSRCS)))


TESTFILENOFIXES = $(patsubst %.cpp,%,$(patsubst test_%,%,$(TESTFILE)))
TESTMAINSRC = $(MAINSRC_DIR)/$(TESTFILENOFIXES).cpp
TESTTESTSRC = $(TESTSRC_DIR)/test_$(TESTFILENOFIXES).cpp
TESTBIN = $(BIN_DIR)/test/$(TESTFILENOFIXES).exe


# COMMANDS

# command 1 "make" : make executable file
# every source file src/main/*.cpp is compiled to obj/*.o, then link them to generate sudoku.exe
$(EXE): $(MAINOBJS)
	$(CC) -o $(BIN_DIR)/$@ $^ -I $(INCLUDE_DIR) -fdiagnostics-color=always -g

$(MAINOBJS): $(OBJ_DIR)/%.o: $(MAINSRC_DIR)/%.cpp
	$(CC) -c $< -o $@ -I $(INCLUDE_DIR) -fdiagnostics-color=always -g



.PHONY: cleanall unittest debug


# command 2 "make cleanall"
cleanall: cleanbin cleanobj

cleanbin:
	del .\bin\*.exe

cleanobj:
	del .\obj\*.o


# command 3 "make unittest TESTFILE=<filename>"
# this makefile will find testfile as src/main/*.cpp and tester in src/test/test_*.cpp
# generate their object file and then link them to generate a PE file as bin/test_*.exe
unittest: $(TESTBIN)

$(TESTBIN): $(TESTMAINSRC) $(TESTTESTSRC)
	$(CC) -o $@ $^ -I $(INCLUDE_DIR) -fdiagnostics-color=always -g


# command 4 "make debug" : debug this makefile
debug:
