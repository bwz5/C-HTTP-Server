#include "head.h"

void create_server(SERVER_CONNECTION * sc, const char * ip, int port){
    sc->IP = strdup(ip);
    sc->port = port;
    // TODO: create the sockets, connect, etc.

    sc->weight = MEDIUM_WEIGHT; // TODO: Change weight later based on real info (CPU probably best)
    
}

void create_head(HEAD * s){
    s->socketfd = socket(AF_INET, SOCK_STREAM, 0); 

    inet_aton(SERVER_IP,(struct in_addr*)&s->server_address.sin_addr); 
    s->server_address.sin_port = htons(SERVER_PORT_NUMBER); 
    s->server_address.sin_family = AF_INET; 
    
    char ip_str[INET_ADDRSTRLEN];

    // Convert to text string 
    inet_ntop(AF_INET, &(s->server_address.sin_addr), ip_str, INET_ADDRSTRLEN);

    printf("Server Head started on address %s and port %i\n", ip_str, SERVER_PORT_NUMBER);

    if (bind(s->socketfd, (struct sockaddr *)&s->server_address, sizeof(s->server_address)) < 0){
        printf("Failure to bind the socketfd with the sockaddr_in struct\n"); 
        exit(-1); 
    }

    // connection initializations 

    pthread_mutex_init(&(s->connections_mutex), NULL); 

    s->server_connections = (SERVER_CONNECTION *)malloc(sizeof(SERVER_CONNECTION) * MAX_SERVER_CONNECTIONS);
    s->server_connections_len = MAX_SERVER_CONNECTIONS; 

    s->num_connections = 0;
}

void add_server_connection(HEAD * s, const char * IP, int port){
    printf("Adding a connection to %s:%d!\n", IP, port);

    // create the server object 
    SERVER_CONNECTION * sc = (SERVER_CONNECTION*)malloc(sizeof(SERVER_CONNECTION));
    create_server(sc, IP, port); 

    // add to the array
    pthread_mutex_lock(&s->connections_mutex);

    if (s->num_connections == MAX_SERVER_CONNECTIONS){
        printf("Cannot add another server, already at the max capacity\n");
        pthread_mutex_unlock(&s->connections_mutex);  // Unlock before returning
        return; 
    }

    s->server_connections[s->num_connections] = *sc; 
    s->num_connections += 1; 
    pthread_mutex_unlock(&s->connections_mutex);
}

void print_server_connections(HEAD * s){
    pthread_mutex_lock(&s->connections_mutex);
    for (unsigned int i = 0; i < s->num_connections; i++){
        printf("Server connected on %s:%d\n",s->server_connections[i].IP, s->server_connections[i].port);
    }
    pthread_mutex_unlock(&s->connections_mutex);
}

void run_head(HEAD * s){
    // listen on the socketfd and set the maximum number of queued connections 
    if (listen(s->socketfd, MAX_BACKLOG ) < 0){
        printf("Failed to listen to the socket\n");
        exit(-1); 
    }

    int clientfd; 
    struct sockaddr_in client_addr; 
    socklen_t client_len = sizeof(client_addr); 

    while (1) {
        clientfd = accept(s->socketfd, (struct sockaddr *)&s->server_address, (socklen_t *)&client_len);

        if (clientfd < 0){
            printf("Failed to connect to the client\n"); 
            exit(-1); 
        }
        
        // fork() here to continue listening for other connections 
        pid_t PID = fork(); 

        if (PID != 0){
            // parent
            continue; 
        }

        // handle the incoming request 
        char buffer[1024] = {0}; 
        size_t bytes_read = recv(clientfd, buffer, sizeof(buffer)-1, 0); 
        if (bytes_read < 0) {
            printf("Error reading the clientfd\n"); 
            exit(-1);
        }

        printf("Received: %s\n\n", buffer); 

        // TODO: Send the HTTP parsing to other servers 

        // respond to the message 
        const char * response = "Response from server";
        int response_size = strlen(response); 

        // send the response to the client 
        send(clientfd, response, response_size, 0); 

        // cleanup 
        close(clientfd); 
        exit(-1);
    }
}

void cleanup(HEAD * s){
    // free all of the server connections 
    pthread_mutex_lock(&s->connections_mutex);
    for (unsigned int i = 0; i < s->num_connections; i++){
        free(&s->server_connections[i]);
    }
    pthread_mutex_unlock(&s->connections_mutex);
}