LIBRARY=../../lib
CC= g++ --std=c++23
FLAGS= -Wall -I$(LIBRARY)/include
BUILD_DIR = build

SRC_FILES = main.cpp 
LIB_FILES= $(wildcard $(LIBRARY)/build/*.o)

TARGET= $(BUILD_DIR)/main

$(TARGET): $(SRC_FILES) $(LIB_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $^ -o $@	
#	@$(info $(LIB_FILES))     PRINTS THE VARIABLE
	
