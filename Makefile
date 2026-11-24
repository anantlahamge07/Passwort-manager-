CC = gcc
# the compiler flags
CFLAGS = -Wextra -Wall -Wunreachable-code -Wfloat-equal -Wconversion -fsanitize=address -lsodium
INCLUDES = src/main.c src/credentials.c src/vault_session.c  src/vault_manager.c src/storage.c src/crypto.c

all: $(INCLUDES)
	$(CC) $(CFLAGS) $^ -o prog

run: $(INCLUDES)
	./prog

test: src/crypto.c tests/test.c
	$(CC) $(CFLAGS) $^ -o test 
run_test:
	./test
clean: 
	rm test