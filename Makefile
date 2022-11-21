#g++ <source> -Wall -Wextra -std=c++11 -pedantic
all: cTreeTest main#tTreeTest

cTreeTest: cTreeTest.o cTree.o
	g++ -o cTreeTest cTreeTest.o cTree.o -Wall -Wextra -std=c++11 -pedantic

main: main.o cTree.o
	g++ -o main main.o cTree.o -Wall -Wextra -std=c++11 -pedantic


#TreeTest: tTreeTest.o cTree.o
#	g++ -o tTreeTest tTreeTest.o cTree.o -Wall -Wextra -std=c++11 -pedantic

cTree.o: CTree.cpp CTree.h
	g++ -c CTree.cpp -Wall -Wextra -std=c++11 -pedantic

cTreeTest.o: CTreeTest.cpp
	g++ -c CTreeTest.cpp -Wall -Wextra -std=c++11 -pedantic

main.o: main.cpp
	g++ -c main.cpp -Wall -Wextra -std=c++11 -pedantic


#tTreeTest.o: TTreeTest.cpp
#	g++ -c TTreeTest.cpp -Wall -Wextra -std=c++11 -pedantic