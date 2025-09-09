# Makefile for TeamFish

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Directories
SRCDIR = src
TESTDIR = tests
OBJDIR = obj

# Executable names
TARGET = teamfish
TEST_RUNNER = test_runner

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)

# Object files
SRC_OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
SRC_OBJECTS_NO_MAIN = $(filter-out $(OBJDIR)/main.o,$(SRC_OBJECTS))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SOURCES))

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(SRC_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_OBJECTS)

# Test target
test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

$(TEST_RUNNER): $(SRC_OBJECTS_NO_MAIN) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_RUNNER) $(SRC_OBJECTS_NO_MAIN) $(TEST_OBJECTS)

# Rule to create object files from source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create object files from test files
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET) $(TEST_RUNNER)

.PHONY: all clean test
