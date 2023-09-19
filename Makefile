CC = gcc

CFLAGS = -std=c89

all: word_salad

# Building 
word.o: word.c
	$(CC) -c -o $@ $^ 

word_salad: main.c word.o
	gcc --std=c89 $^ -o $@

clean:
	rm *.o
