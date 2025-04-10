#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../lib/picohttpparser/picohttpparser.h"
#include "../util/hashset.h"
#include "http_response.h"

#define SERVER_PORT_NUMBER 8080
#define SERVER_IP "127.0.0.1"
#define MAX_BACKLOG 100

/*
Represents a HTTP server. 
*/
typedef struct {
    int socketfd; 
    struct sockaddr_in server_address;
} server; 

/* 
Creates a socket fd and sets [socketfd] with that value. 
Defines the server address and port, setting [server_address].
Binds the socket to the address and port. 
*/
void create_server(server* s); 

/* 
Main control loop that:
    1. listens for connections
    2. accepts the connections and spawns a child process
    3. parses the HTTP request 
    4. returns a HTTP response 
*/
void run_server(server* s); 

#endif 