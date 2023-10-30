# OOPD_Project Makefile Explanation
#Explanation of the makefile with comments

CC = g++    # Compiler and flags
CFLAGS = -std=c++20 -Wall


SRCS = Q1-5.cpp               # Source files, object files, and debug object files
OBJS = $(SRCS:.cpp=.o)        # Generate object file names from source files
DEBUG_OBJS = $(SRCS:.cpp=_debug.o)  # Generate debug object file names from source files


TARGET = Q1-5     # Executable names
DEBUG_TARGET = Question_DEBUG

.PHONY: all clean     # Declare phony targets

all: $(TARGET) $(DEBUG_TARGET)     # Default target: build both the non-debug and debug versions

$(TARGET): $(OBJS)     # Rule to build the non-debug executable
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJS)      # Rule to build the debug executable
	$(CC) $(CFLAGS) -g $(DEBUG_OBJS) -o $(DEBUG_TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@     # Pattern rule to build object files from source files

%_debug.o: %.cpp     # Pattern rule to build debug object files from source files
	$(CC) $(CFLAGS) -g -c $< -o $@


clean:    # Clean target: remove all object files and executables
	rm -f $(OBJS) $(DEBUG_OBJS) $(TARGET) $(DEBUG_TARGET)
