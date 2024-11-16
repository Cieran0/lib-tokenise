# Compiler and Archiver
CC = gcc
CXX = g++
AR = ar

# Flags
CFLAGS = -Wall -Werror -std=c11
CXXFLAGS = -Wall -Werror -std=c++11
INCLUDE = -Iinclude -Iinclude/internal

# Source Files
SRC_C = $(wildcard src/*.c)
SRC_CPP = $(wildcard src/*.cpp)

# Object Files
OBJ_C = $(SRC_C:src/%.c=%.o)
OBJ_CPP = $(SRC_CPP:src/%.cpp=%.o)

# Output Library
LIB = libtokenise.a

.PHONY: all clean

# Default target
all: clean $(LIB)

# Static library
$(LIB): $(OBJ_C) $(OBJ_CPP)
	$(AR) rcs $@ $^

# Compile C object files
%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Compile C++ object files
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ_C) $(OBJ_CPP) $(LIB)
