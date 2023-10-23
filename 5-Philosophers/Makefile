CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -pthread

.PHONY: clean

all: philosophers

philosophers: philosophers.c
	$(CC) $(CFLAGS) -o philosophers.out philosophers.c

clean:
	rm -f philosophers.out
