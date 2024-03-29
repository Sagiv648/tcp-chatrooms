CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src/*.cpp $(shell find $(lib) -name *.cpp)
INCLUDE	:= -Iinclude -Ilib
LIB		:= lib

LIBRARIES	:= -lpthread \
-lssl 
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*


