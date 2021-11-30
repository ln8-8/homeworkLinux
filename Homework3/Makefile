all: shell

shell: myShell.o
	g++ myShell.o -o shell

myShell.o: myShell.cpp
	g++ -c myShell.cpp

clean:
	rm *.o shell
