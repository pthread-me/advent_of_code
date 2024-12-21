CC= g++ --std=c++23
FLAGS= -Wall -Iinclude
MATH= -lm
BUILD_DIR = build
SRC_DIR = .

SRC_FILES = tokenizer.cpp 
OBJS = $(BUILD_DIR)/$(SRC_FILES:.cpp=.o)

all: $(OBJS)

#Builds all the obj files 
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -r build
