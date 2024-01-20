# Define compiler
CC=g++

# Define flags
CFLAGS=-Wall -g

# Define target executable name
TARGET=chess

# Define source files
SRCS=main.cpp position.cpp

# Define object files
OBJS=$(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to link the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

