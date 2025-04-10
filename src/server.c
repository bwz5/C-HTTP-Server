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

const char * extract_substring(const char * buf, int start, int length){
  char * temp = (char *)malloc(length);
  for (int i = start; i < start + length; i++){
    temp[i] = buf[i]; 
  }
  return temp;
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

        // HTTP MESSAGE PARSING
        const char *method, *path;
        int pret, minor_version;
        struct phr_header headers[100];
        size_t prevbuflen = 0, method_len, path_len, num_headers;
            
        /* parse the request */
        num_headers = sizeof(headers) / sizeof(headers[0]);
        pret = phr_parse_request(buffer, bytes_read, &method, &method_len, &path, &path_len,
                                &minor_version, headers, &num_headers, prevbuflen);

        // PRINT THE HTTP MESSAGE 
        printf("request is %d bytes long\n", pret);
        printf("method is %.*s\n", (int)method_len, method);
        printf("path is %.*s\n", (int)path_len, path);
        printf("HTTP version is 1.%d\n", minor_version);
        printf("headers:\n");
        for (size_t i = 0; i != num_headers; ++i) {
            printf("%.*s: %.*s\n", (int)headers[i].name_len, headers[i].name,
                  (int)headers[i].value_len, headers[i].value);
        }

        // respond to the message 
        const char * response;
        int response_size; 

        // TEMPORARY 404 Message 
        HTTP_RESPONSE r;
        generate_404(&r);
        response_size = flatten_response_object(&response, &r);

        printf("Response (%d bytes):\n%s", response_size, response);

        send(clientfd, response, response_size, 0); 

        close(clientfd); 

        exit(-1);
    }
}