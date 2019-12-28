CC = gcc
CFLAGS = -Wall -Wextra

ALL: aes-ctr key-gen  

aes-ctr: main.c
	$(CC) $(CFLAGS) -o aes-ctr main.c aes.c fileio.c print.c

key-gen: key-gen.c
	$(CC) $(CFLAGS) -o key-gen key-gen.c fileio.c

clean:
	rm aes-ctr key-gen
