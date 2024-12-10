COMPILER =  g++ --std=c++23
FLAGS = -g -o


main: main.cpp map.o
	$(COMPILER) main.cpp map.o $(FLAGS) a

map.o: map.cpp map.hpp
	$(COMPILER) -c map.cpp map.hpp

test: test.cpp
	$(COMPILER) test.cpp $(FLAGS) test
