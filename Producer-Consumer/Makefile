CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -pthread

.PHONY: clean

producerConsumer.out: producerConsumer.c
	$(CC) $(CFLAGS) -o producerConsumer.out producerConsumer.c

clean:
	rm -f *.out
