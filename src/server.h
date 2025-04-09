#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "lib/http-parser/http_parser.h"

#define SERVER_PORT_NUMBER 8080
#define SERVER_IP "127.0.0.1"
#define MAX_BACKLOG 15 

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
Main control loop that will listen for connections, accept the connections, and then 
handle the requests. 
*/
void run_server(server* s); 

#endif 