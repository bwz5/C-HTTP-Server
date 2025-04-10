// Need a way of storing the server's IPs and weights + current weights 
// Route based on smooth weighted round robin load balancing algorithm 

// create a connection between the head and the server
    // need a way of differentiation the new server connections from other new connections 
#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct {
    const char * IP; 
    int clientfd; 
    struct sockaddr_in client_addr; 

    int weight;
    int current_weight; 
} server_connection; 

/*
Create the server object 
*/
void create_server(server_connection * sc); 

typedef struct {
    const char * IP; 
    int socketfd; 
    struct sockaddr_in sock_addr; 
} client_connection;

void create_client(client_connection * cc);

typedef struct {
    int response_length; 
    const char * response; 
} response; 

typedef struct {
    // TODO: Need dynamic array of the child servers 
    server_connection * server_pool; 
} head; 

void create_head(head * h); 

/* 
When receiving a non-server connection: Distribute the workload to a server. 
When receiving a server connection: Add to the pool of available servers. 
*/
void run_head(head * h);

response * distribute(head * h);
 
#endif 