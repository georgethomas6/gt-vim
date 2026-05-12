
CC = gcc
CFLAGS = -Wall -pedantic -Werror -Ihelpers -std=c23 

main: main.o compile_commands.json
	$(CC) $(CFLAGS) -o main main.c

compile_commands:
	bear -- make
	
