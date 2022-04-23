CC = gcc
CFLAGS = -g -Werror -Wall -Wextra -Wfloat-equal -O -lGL -lglut -lGLEW -lm -lGLU

start: main.o
	$(CC) main.o $(CFLAGS) -o start

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm start *.o
