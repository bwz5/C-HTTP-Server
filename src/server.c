#include "server.h" 

server create_server(){
    server temp; 
    // uses the default TCP/IP protocol 
    temp.sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if (temp.sockfd < 0){
        raise_socket_creation_error();
    }

    temp.connection_string_address = "192.168.1.100"; // TODO: Change this to another address 

    temp.connection_addr.sin_family = AF_INET; // IPv4
    temp.connection_addr.sin_port = htons(80); // Connection port (80 for HTTP)

    // Convert the IP address from text to binary form
    if (inet_pton(AF_INET, temp.connection_string_address, &temp.connection_addr.sin_addr) <= 0) {
        raise_invalid_address_error(temp.sockfd); 
    }

    // Connect to the server
    if (connect(temp.sockfd, (struct sockaddr *)&temp.connection_addr, sizeof(temp.connection_addr)) < 0) {
        raise_connection_error(temp.sockfd); 
    }

    return temp; 
}

ssize_t write_to_connection(server * s, const char * message){
    ssize_t bytes = write(s->sockfd, message, sizeof(message)); 
    if (bytes < 0){
        raise_write_error(s->sockfd); 
    }
    printf("Successfully wrote message: %s", message); 
    return bytes; 
}