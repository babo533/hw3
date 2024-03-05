CXX := g++
CXXFLAGS := -g -Wall -std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes
SRC_DIR := .
OBJ_DIR := .
BIN_DIR := .

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

# Source and object files
SRCS := $(SRC_DIR)/llrec-test.cpp $(SRC_DIR)/llrec.cpp
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable target
EXEC := $(BIN_DIR)/llrec-test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

.PHONY: all clean
