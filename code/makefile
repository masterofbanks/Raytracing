# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -lglfw -lGLEW -lGL

# Make sure you add new cpp files here :D
SRC = simpleTexture.cpp

OBJ = $(addprefix build/, $(SRC:.cpp=.o))
EXEC = build/rayTracingAssignment1

# Default target
all: $(EXEC)

# Create the build directory
build:
	mkdir -p build

# Linking
$(EXEC): $(OBJ)
	$(CXX) $^ -o $@ $(LIBS)

# Compiling
build/%.o: %.cpp | build
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Cleaning up
clean:
	rm -rf build