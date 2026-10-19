CC = gcc
# the compiler flags
CFLAGS = -Wextra -Wall -Wunreachable-code -Wfloat-equal -Wconversion


all: src/main.c
	$(CC) $(CFLAGS) $^ -o test