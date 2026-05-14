# $@ = name of the rule
# $< = name of the first pre-req
# $^ = all pre-reqs
CC = gcc
CFLAGS = -Wall -pedantic -Werror -Iinclude -std=c23

OBJS = build/main.o \
       build/input.o

TARGET = bin/main

# | indicates an `order only pre-req` 
# i.e. if bin file (make sees directories as files) doesn't exist, run the rule
$(TARGET): $(OBJS) | bin
	$(CC) $(CFLAGS) -o $@ $^


# for any file build/<name>.o we need, it depends on the file src/<name>.c 
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

build:
	mkdir -p build
compile_commands: 
	make clean
	bear -- make

clean:
	rm -rf build bin
