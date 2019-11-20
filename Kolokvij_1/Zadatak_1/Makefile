CC=g++
CFLAGS=-I.
DEPS = Statistics.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: analyze.o Statistics.o
	$(CC) -o analyze analyze.o Statistics.o

.PHONY: clean

clean:
	rm -rf *.o analyze