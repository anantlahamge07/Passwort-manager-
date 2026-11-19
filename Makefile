CC = gcc
# the compiler flags
CFLAGS = -Wextra -Wall -Wunreachable-code -Wfloat-equal -Wconversion -fsanitize=address
INCLUDES = src/main.c src/credentials.c src/vault_session.c  src/vault_manager.c src/storage.c

all: $(INCLUDES)
	$(CC) $(CFLAGS) $^ -o test

run: $(INCLUDES)
	./test


clean: 
	rm test