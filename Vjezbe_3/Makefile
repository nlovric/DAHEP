CC=g++
CFLAGS=-I.
DEPS = ElementaryParticle.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: analyzer.o ElementaryParticle.o
	$(CC) -o analyzer analyzer.o ElementaryParticle.o

.PHONY: clean

clean:
	-rm edit $(objects)