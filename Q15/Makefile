
#This file Will compile and debug the source code  "Question2.cpp"
# Makefile for compiling and debugging a C++ program

# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Wall

SRCS = Q1_5.cpp
OBJS = $(SRCS:.cpp=.o)
DEBUG_OBJS = $(SRCS:.cpp=_debug.o)

TARGET = Q1_5

DEBUG_TARGET = Question_DEBUG

.PHONY: all clean

all: $(TARGET) $(DEBUG_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJS)
	$(CC) $(CFLAGS) -g $(DEBUG_OBJS) -o $(DEBUG_TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%_debug.o: %.cpp
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm -f $(OBJS) $(DEBUG_OBJS) $(TARGET) $(DEBUG_TARGET)