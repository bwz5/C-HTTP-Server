# Compiler and flags
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

# SERVER_TARGET executable name
SERVER_TARGET = server

#HEAD_TARGET exectuable name
HEAD_TARGET = head 

# Object files
SERVER_OBJS = src/server/main.o \
       src/util/error.o \
       src/util/vector.o \
	   src/util/hashmap.o \
       src/server/server.o \
	   src/lib/picohttpparser/http_parser.o \
	   src/server/http_response.o

HEAD_OBJS = src/head/main_head.o \
			src/head/head.o

# Link all object files into the final executable
$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS)

# Compile main.c -> main.o
src/server/main.o: src/server/main.c
	$(CC) $(CFLAGS) -c src/server/main.c -o src/server/main.o

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
src/lib/picohttpparser/http_parser.o: src/lib/picohttpparser/picohttpparser.c src/lib/picohttpparser/picohttpparser.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile http_response.c -> http_response.o
src/server/http_response.o: src/server/http_response.c src/server/http_response.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile server.c -> server.o
src/server/server.o: src/server/server.c src/server/server.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile head into an executable 
$(HEAD_TARGET): $(HEAD_OBJS)
	$(CC) $(CFLAGS) -o $@ $(HEAD_OBJS)

# Compile head.c -> head.o
src/head/head.o: src/head/head.c src/head/head.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c -> main_head.o
src/head/main_head.o: src/head/main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(SERVER_OBJS) $(HEAD_OBJS) $(SERVER_TARGET) $(HEAD_TARGET)

client_test: 
	$(CC) $(CFLAGS) test/testclient.c -o test_client

clean_test:
	rm -f test_client

# Explicitly define phony targets (not associated with files)
.PHONY: all clean
