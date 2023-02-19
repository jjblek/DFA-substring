Project1 : Project1.o DFA.o BigUnsigned.o
	g++ -o Project1 Project1.o DFA.o BigUnsigned.o

Project1.o : ../../../CS DFA.hpp
	g++ -c Project1.cpp -o Project1.o

DFA.o : ../../../CS DFA.hpp BigUnsigned.hpp
	g++ -c DFA.cpp -o DFA.o

BigUnsigned.o : ../../../CS BigUnsigned.hpp
	g++ -c BigUnsigned.cpp -o BigUnsigned.o

clean : 
	rm -rf *.o Project1