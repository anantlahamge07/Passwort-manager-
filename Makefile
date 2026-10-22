CC = gcc
# the compiler flags
CFLAGS = -Wextra -Wall -Wunreachable-code -Wfloat-equal -Wconversion
INCLUDES = src/main.c

all: $(INCLUDES)
	$(CC) $(CFLAGS) $^ -o test

run: $(INCLUDES)
	./test


clean: 
	rm test