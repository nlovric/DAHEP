CC=g++
CFLAGS=-I. $(shell root-config --cflags)
LDFLAGS = $(shell root-config --libs)
DEPS = pdfGen.h

%.o: %.cpp $(DEPS)
	$(CC) $(LDFLAGS) -c -o $@ $< $(CFLAGS)

analyze: analyze.o pdfGen.o
	$(CC) $(LDFLAGS) -o analyze analyze.o pdfGen.o

clean:
	rm -rf *.o analyze
