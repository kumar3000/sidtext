CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

sidtext: src/sidtext.c
	$(CC) src/sidtext.c -o bin/sidtext $(CFLAGS)

.PHONY: clean
clean:
	rm -f bin/sidtext

.PHONY: run
run: sidtext
	bin/sidtext $(ARGS)