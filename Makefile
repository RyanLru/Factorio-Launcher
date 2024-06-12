# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra

# SDL libraries and X11
SDL_LIBS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

# Source files
SRCS := $(wildcard *.cpp)

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
TARGET := Factorio-Launcher

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SDL_LIBS)

# Rule to compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ `sdl2-config --cflags`

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
