#include "error.h"
#include <sys/socket.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>


void raise_out_of_bounds_error(){
    perror( "Error: Index is out of bounds\n"); 
    exit(EXIT_FAILURE); 
}

void raise_socket_creation_error(){
    perror( "Error: Failed to create socket\n"); 
    exit(EXIT_FAILURE); 
}

void raise_invalid_address_error(int sockfd){
    perror("Error: Invalid address or Address not supported\n");
    close(sockfd);
    exit(EXIT_FAILURE);
}

void raise_connection_error(int sockfd){
    perror( "Error: Connection Failed\n");
    close(sockfd);
    exit(EXIT_FAILURE);
}

void raise_write_error(int sockfd){
    perror( "Error: Failed to write to connection\n");
    close(sockfd);
    exit(EXIT_FAILURE);
}

