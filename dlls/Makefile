# Raylib library path
RAYLIB_DIR := $(shell brew --prefix raylib)

# Compiler flags
CXXFLAGS := -std=c++20 -Wall -O3

# Include directories
INC_DIRS := -I$(RAYLIB_DIR)/include -I../../src

# Library directories
LIB_DIRS := -L$(RAYLIB_DIR)/lib

# Libraries to link against
LIBS := -lraylib -framework OpenGL -framework OpenAL -framework IOKit -framework CoreVideo -framework Cocoa

# Source files
SRC := square/*.cpp ../src/interpolator.cpp ../src/ffmpeg.cpp

# Output file
OUTPUT := libplugin.so

.PHONY: all clean

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) $(LIB_DIRS) -shared -o $@ $^ $(LIBS)

clean:
	rm -f $(OUTPUT)
