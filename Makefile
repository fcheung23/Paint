CC = cc
CFLAGS = -Wall -Werror

paint.out: main.o commands.o canvas.o input.o
	$(CC) $(CFLAGS) main.o commands.o canvas.o input.o -o paint.out

main.o: main.c	
	$(CC) $(CFLAGS) -c main.c -o main.o

commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -c commands.c -o commands.o

canvas.o: canvas.c canvas.h	
	$(CC) $(CFLAGS) -c canvas.c -o canvas.o

input.o: input.c input.h	
	$(CC) $(CFLAGS) -c input.c -o input.o

clean:
	rm -f *.o paint.out
