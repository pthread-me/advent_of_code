LIBRARY=../../lib
CC= g++ --std=c++23
FLAGS= -Wall -g -I$(LIBRARY)/include
BUILD_DIR = build

SRC_FILES = main.cpp 
PART1_SRC_FILES = part1.cpp 
PART2_SRC_FILES = part2.cpp 
LIB_FILES= $(wildcard $(LIBRARY)/build/*.o)

TARGET= $(BUILD_DIR)/main



$(TARGET): $(SRC_FILES) $(LIB_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $^ -o $@ 	
#	@$(info $(LIB_FILES))     PRINTS THE VARIABLE


$(BUILD_DIR)/part1: $(PART1_SRC_FILES) $(LIB_FILES)
		@mkdir -p $(BUILD_DIR)
		$(CC) $(FLAGS) $^ -o $@ 
#		@$(info $(LIB_FILES)) 


$(BUILD_DIR)/part2: $(PART2_SRC_FILES) $(LIB_FILES)
		@mkdir -p $(BUILD_DIR)
		$(CC) $(FLAGS) $^ -o $@ 
