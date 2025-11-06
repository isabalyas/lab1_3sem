CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCLUDE_DIR)
INCLUDE_DIR = "include"
SRC_DIR = src
OBJ_DIR = obj
SRC = $(shell find $(SRC_DIR) -name "*.cpp")
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
TARGET = dbms


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJ)