CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = Analyzer.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: analyze.o Analyzer.o
	$(CC) $(LDFLAGS) -o analyze analyze.o Analyzer.o

.PHONY: clean

clean:
	rm -rf *.o analyze