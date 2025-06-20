CXX = g++
CXXFLAGS = -std=c++11 -I include

SRC_DIR = src
OBJ_DIR = obj

TARGET = library_management

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	del /Q /F library_management.exe 2>nul
	del /Q /F src\*.o 2>nul
	rmdir /S /Q obj 2>nul
