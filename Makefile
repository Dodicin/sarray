CXXFLAGS = -DNDEBUG

main.exe: main.o 
	g++ -g main.o -o main.exe

main.o: main.cpp
	g++ -g $(CXXFLAGS) -c main.cpp -o main.o


.PHONY: clean

clean:
	rm *.exe *.o
