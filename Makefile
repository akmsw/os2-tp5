CC = gcc
CFLAGS = -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

all: lab5

lab5: lab5.c
	$(CC) $(CFLAGS) -o $@ $< -lulfius

clean:
	rm -f lab5