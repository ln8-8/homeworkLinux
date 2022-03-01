all: signalHandler

signalHandler: signalHandling.o
	g++ signalHandling.o -o signalHandler

signalHandling.o: signalHandling.cpp
	g++ -c signalHandling.cpp

clean:
	rm *.o signalHandler
