# Compiler and flags
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

# SERVER_TARGET executable name
SERVER_TARGET = server

#HEAD_TARGET exectuable name
HEAD_TARGET = head 

# Object files
SERVER_OBJS = src/server/server.o \
	   src/lib/picohttpparser/http_parser.o \
	   src/server/http_response.o

HEAD_OBJS = src/load_balancer/main_head.o \
			src/load_balancer/head.o

###### SERVER SIDE ######

# Link all object files into the final executable
$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS)

# Compile http_parser.c -> http_parser.o
src/lib/picohttpparser/http_parser.o: src/lib/picohttpparser/picohttpparser.c src/lib/picohttpparser/picohttpparser.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile http_response.c -> http_response.o
src/server/http_response.o: src/server/http_response.c src/server/http_response.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile server.c -> server.o
src/server/server.o: src/server/server.c
	$(CC) $(CFLAGS) -c $< -o $@

##### HEAD (LOAD BALANCER) #####
# Compile head into an executable 
$(HEAD_TARGET): $(HEAD_OBJS)
	$(CC) $(CFLAGS) -o $@ $(HEAD_OBJS)

# Compile head.c -> head.o
src/load_balancer/head.o: src/load_balancer/head.c src/load_balancer/head.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c -> main_head.o
src/load_balancer/main_head.o: src/load_balancer/main.c
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
