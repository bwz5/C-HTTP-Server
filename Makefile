# Compiler and flags
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

# Target executable name
TARGET = server

# Object files
OBJS = main.o \
       src/util/error.o \
       src/util/vector.o \
	   src/util/hashmap.o \
	   src/http_parser.o \
       src/server.o

# Default rule (when you run `make` without arguments)
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile main.c -> main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# Compile error.c -> error.o
src/util/error.o: src/util/error.c src/util/error.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile vector.c -> vector.o
src/util/vector.o: src/util/vector.c src/util/vector.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile hashmap.c -> hashmap.o
src/util/hashmap.o : src/util/hashmap.c src/util/hashmap.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile http_parser.c -> http_parser.o 
src/http_parser.o : src/http_parser.c src/http_parser.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile server.c -> server.o
src/server.o: src/server.c src/server.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

client_test: 
	$(CC) $(CFLAGS) test/testclient.c -o test_client

clean_test:
	rm -f test_client

# Explicitly define phony targets (not associated with files)
.PHONY: all clean
