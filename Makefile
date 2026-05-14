CC = gcc
CFLAGS = -Wall -pedantic -Werror -Ihelpers -std=c23

OBJS = build/main.o \
			 build/input.o

main: $(OBJS)
	$(CC) $(CFLAGS) -o ./exe/$@ $^

build/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c -o ./build/main.o $<

build/input.o: ./src/input.c
	$(CC) $(CFLAGS) -c -o ./build/input.o $<

compile_commands:
	bear -- make

clean:
	rm -f main *.o
