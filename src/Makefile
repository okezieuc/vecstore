# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -pthread -std=c++11 -I.

# Target executable
TARGET = main.out

# For deleting the target
TARGET_DEL = main.out

SRCS :=  $(wildcard $(shell find . -name '*.cpp'))

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	./$(TARGET) --vsize 3

# Clean rule to remove generated files
clean:
	rm $(OBJS) # $(TARGET_DEL)
