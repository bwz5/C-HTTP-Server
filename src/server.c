#include "server.h"

int on_message_begin(http_parser* _) {
  (void)_;
  printf("\n***MESSAGE BEGIN***\n\n");
  return 0;
}

int on_headers_complete(http_parser* _) {
  (void)_;
  printf("\n***HEADERS COMPLETE***\n\n");
  return 0;
}

int on_message_complete(http_parser* _) {
  (void)_;
  printf("\n***MESSAGE COMPLETE***\n\n");
  return 0;
}

int on_url(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Url: %.*s\n", (int)length, at);
  return 0;
}

int on_header_field(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Header field: %.*s\n", (int)length, at);
  return 0;
}

int on_header_value(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Header value: %.*s\n", (int)length, at);
  return 0;
}

int on_body(http_parser* _, const char* at, size_t length) {
  (void)_;
  printf("Body: %.*s\n", (int)length, at);
  return 0;
}

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
        clientfd = accept(s->socketfd, (struct sockaddr *)&s->server_address, (socklen_t *)&client_len);

        if (clientfd < 0){
            printf("Failed to connect to the client\n"); 
            exit(-1); 
        }

        // fork() here to process the HTTP request on a separate thread 
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

        // HTTP MESSAGE PROCESSING 

        http_parser_settings settings;
        memset(&settings, 0, sizeof(settings));
        settings.on_message_begin = on_message_begin;
        settings.on_url = on_url;
        settings.on_header_field = on_header_field;
        settings.on_header_value = on_header_value;
        settings.on_headers_complete = on_headers_complete;
        settings.on_body = on_body;
        settings.on_message_complete = on_message_complete;

        // initialize http_parser 
        http_parser *parser = malloc(sizeof(http_parser));
        http_parser_init(parser, HTTP_REQUEST);

        // parse the message 
        size_t nparsed = http_parser_execute(parser, &settings, buffer, bytes_read);
        
        if (nparsed != bytes_read) {
            printf("Error: Could not parse the entire incoming HTTP request\n");
        }

        free(parser); // free the memory associated with parser 

        // respond to the message 
        const char * response = "Received your message\n"; 
        send(clientfd, response, sizeof(response), 0); 

        close(clientfd); 

        exit(-1);
    }
}