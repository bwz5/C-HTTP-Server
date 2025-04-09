/* TAKEN FROM GOOGLE'S GEMINI */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // TODO: Change the SERVER_IP 
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server!\n");

    // Send a message to the server
    char *message = "GET /hello.htm HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nHost: www.tutorialspoint.com\nAccept-Language: en-us\nAccept-Encoding: gzip, deflate\nConnection: Keep-Alive";

    if (send(sockfd, message, strlen(message), 0) < 0) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent: %s\n", message);

    // Receive a response from the server
    memset(buffer, 0, BUFFER_SIZE);
    if ((n = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) < 0) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);
    fflush(stdout);

    // Close the socket
    close(sockfd);
    return 0;
}