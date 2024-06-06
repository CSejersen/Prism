# Compiler
CXX := g++

# Raylib library path
RAYLIB_DIR := $(shell brew --prefix raylib)

# Compiler flags
CXXFLAGS := -std=c++20 -Wall -O3

# Include directories
INC_DIRS := -I$(RAYLIB_DIR)/include

# Library directories
LIB_DIRS := -L$(RAYLIB_DIR)/lib

# Libraries to link against
LIBS := -lraylib -framework OpenGL -framework OpenAL -framework IOKit -framework CoreVideo -framework Cocoa

# Source directory
SRC_DIR := src
# Build directory
BUILD_DIR := build
# Binary directory
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
# Executable name
EXEC := $(BIN_DIR)/prism

.PHONY: all clean

all: $(EXEC)

# Rule to compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $< -o $@

# Rule to link object files into executable
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LIB_DIRS) $^ -o $@ $(LIBS)

clean:
	@$(RM) -r $(BUILD_DIR) $(BIN_DIR)
