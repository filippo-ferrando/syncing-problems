CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -pthread

.PHONY: clean

all: writerReader

writerReader: writerReader.c
	$(CC) $(CFLAGS) -o writerReader.out writerReader.c

clean:
	rm -f writerReader.out
