# OOPD_Project Makefile Explanation
#Explanation of the makefile with comments
# This file Will compile and debug the source code 
# Makefile for compiling and debugging a C++ program

# Makefile for compiling and debugging a C++ program

# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Wall

# Source files, object files, and debug object files
SRCS = Q1-5.cpp
OBJS = $(SRCS:.cpp=.o)        # Generate object file names from source files
DEBUG_OBJS = $(SRCS:.cpp=_debug.o)  # Generate debug object file names from source files

# Executable names
TARGET = Q1-5
DEBUG_TARGET = Question_DEBUG

# Declare phony targets (targets not associated with actual files)
.PHONY: all clean

# Default target: build both the non-debug and debug versions
all: $(TARGET) $(DEBUG_TARGET)

# Rule to build the non-debug executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to build the debug executable
$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(CC) $(CFLAGS) -g $(DEBUG_OBJS) -o $(DEBUG_TARGET)

# Pattern rule to build object files from source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule to build debug object files from source files
%_debug.o: %.cpp
	$(CC) $(CFLAGS) -g -c $< -o $@

# Clean target: remove all object files and executables
clean:
	rm -f $(OBJS) $(DEBUG_OBJS) $(TARGET) $(DEBUG_TARGET)
