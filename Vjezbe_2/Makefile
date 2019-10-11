CC=gcc
CFLAGS=-I.
DEPS = ElementaryParticle.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: analyzer.o ElementaryParticle.o
	$(CC) -o analyzer analyzer.0 ElementaryParticle.o
	