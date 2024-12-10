COMPILER = g++ --std=c++23
FLAGS = -g -o

main: main.cpp
	$(COMPILER) main.cpp $(FLAGS) main
	$(clean)

main.o: main.cpp
	$(COMPILER) -c main.cpp 

clean:
	rm main.o
