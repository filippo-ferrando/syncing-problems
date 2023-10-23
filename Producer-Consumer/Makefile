CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -pthread

.PHONY: clean

all: producerConsumer

producerConsumer: producerConsumer.c
	$(CC) $(CFLAGS) -o producerConsumer.out producerConsumer.c

clean:
	rm -f producerConsumer.out
