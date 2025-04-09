#include "server.h"

void create_server(server * s){
    s->socketfd = socket(AF_INET, SOCK_STREAM, 0); 

    inet_aton(SERVER_IP,(struct in_addr*)&s->server_address.sin_addr); 
    s->server_address.sin_port = htons(SERVER_PORT_NUMBER); 
    s->server_address.sin_family = AF_INET; 
    
    char ip_str[INET_ADDRSTRLEN];

    // Convert to text string (Taken from GEMINI) 
    if (inet_ntop(AF_INET, &(s->server_address.sin_addr), ip_str, INET_ADDRSTRLEN) != NULL) {
        printf("IP Address: %s\n", ip_str);
    } else {
        perror("inet_ntop");
    }

    printf("Server started on address %s and port %i\n", ip_str, SERVER_PORT_NUMBER);

    if (bind(s->socketfd, (struct sockaddr *)&s->server_address, sizeof(s->server_address)) < 0){
        printf("Failure to bind the socketfd with the sockaddr_in struct\n"); 
        exit(-1); 
    }
}

void run_server(server * s){
    // listen on the socketfd and set the maximum number of queued connections 
    if (listen(s->socketfd, MAX_BACKLOG ) < 0){
        printf("Failed to listen to the socket\n");
        exit(-1); 
    }

    int clientfd; 
    struct sockaddr_in client_addr; 
    socklen_t client_len = sizeof(client_addr); 

    while (1) {
        // TODO: Change this to fork() when we have a new client acceptance
        // this will maximize efficiency of our program 
        clientfd = accept(s->socketfd, (struct sockaddr *)&s->server_address, (socklen_t *)&client_len);

        if (clientfd < 0){
            printf("Failed to connect to the client\n"); 
            exit(-1); 
        }

        // TODO: fork() here 

        // handle the incoming request 
        char buffer[1024] = {0}; 
        int bytes_read = recv(clientfd, buffer, sizeof(buffer)-1, 0); 
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the received data
            printf("Received: %s\n", buffer);
        }

        // respond that we got a message 
        const char * response = "Received your message\n"; 
        send(clientfd, response, sizeof(response), 0); 

        close(clientfd); 
    }
}