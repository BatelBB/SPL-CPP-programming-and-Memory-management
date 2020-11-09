all: Assignment_1



Assignment_1: bin/Agent.o bin/Graph.o bin/Main.o bin/Session.o bin/Tree.o
	@echo 'Building target: Assignment_1'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/Agent.o bin/Graph.o bin/Main.o bin/Session.o bin/Tree.o
	@echo 'Finished building target: Assignment_1'
	@echo ' '


bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp


bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp
	

bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp
	

bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp
	

bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp

#Clean the build directory
clean: 
	rm -f bin/*
