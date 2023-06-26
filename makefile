SRC_DIR = ./src
INCLUDE_DIR = ./include
BIN_DIR = ./bin

EXE = sudoku.exe

SRC = $(wildcard $(SRC_DIR)/*.cpp)

CC = g++

$(EXE): $(SRC)
	$(CC) -o $(BIN_DIR)/$@ $(SRC) -I $(INCLUDE_DIR) -fdiagnostics-color=always -g





cleanall: cleanbin

cleanbin:
	del .\bin\*.exe

