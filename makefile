CC=gcc

default: tokenizer.c
	$(CC) -o tokenizer tokenizer.c -Wall -g

clean:
	-rm -f tokenizer
