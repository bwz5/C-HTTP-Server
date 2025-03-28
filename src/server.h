#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include "util/vector.h"
#include "util/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// temporarily has 1 two-way reliable connection, but more will come later
// * use multi-threading for multiple connections ! 
typedef struct {
    int sockfd;
    const char * connection_string_address; 
    struct sockaddr_in connection_addr; 
} server; 

/* Initializes a [server] struct, setting its [sock] and [connections] 
    Returns -1 if failure, otherwise it returns the socket number. 
*/
server create_server();

/* Writes the message to the connection. If the bytes written are 0, throws an error. */
ssize_t write_to_connection(server * s, const char* message); 

#endif 