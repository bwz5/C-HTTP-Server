#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h> 
#include <stdio.h> 

void raise_out_of_bounds_error(); 

void raise_socket_creation_error(); 

void raise_invalid_address_error(int sockfd); 

void raise_connection_error(int sockfd); 

void raise_write_error(int sockfd); 

#endif 