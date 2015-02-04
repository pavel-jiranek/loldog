CC=cc
CCFLAGS=-O3
LDFLAGS=

all: loldog

clean:
	rm -rf *.o

linelist.o: linelist.c linelist.h utils.h
	$(CC) $(CCFLAGS) -o $@ -c linelist.c

utils.o: utils.c utils.h
	$(CC) $(CCFLAGS) -o $@ -c utils.c

options.o: options.c options.h
	$(CC) $(CCFLAGS) -o $@ -c options.c

lol.o: lol.c lol.h linelist.h options.h

mail.o: main.c options.h lol.h linelist.h
	$(CC) $(CCFLAGS) -o $@ -c main.c

loldog: main.o utils.o linelist.o options.o lol.o
	$(CC) $(LDFLAGS) -o $@ $^

