#include "http_response.h"
#include <stdlib.h>
#include <string.h>

int flatten_response_object(const char ** response, HTTP_RESPONSE * http_response){
    // Calculate buffer length
    int buffer_len = strlen(http_response->version) + 1 +   // space separator
                     strlen(http_response->status_code) + 1 + 
                     strlen(http_response->headers) + 4 + // TODO: CRLF only accounts for ONE HEADER PLUS the blank line after
                     strlen(http_response->reason_phrase) + 2 + // CRLF after status line
                     strlen(http_response->body);
    
    // Allocate memory for the complete response
    *response = (char *)malloc(buffer_len + 1);  // +1 for null terminator
    if (*response == NULL) {
        perror("malloc failed");
        return -1;
    }

    // Construct the response string.
    int written = sprintf(*response, "%s %s %s\r\n%s\r\n\r\n%s", // carriage return for HTTP formatting 
        http_response->version, 
        http_response->status_code, 
        http_response->reason_phrase, 
        http_response->headers, 
        http_response->body);

    return written;
}

void generate_404(HTTP_RESPONSE * hr){
    hr->version = "HTTP/1.1";
    hr->status_code = "404"; 
    hr->reason_phrase = "Not Found";

    hr->headers="Content-Type: text/html; charset=UTF-8";

    hr->body = 
        "<!DOCTYPE HTML PUBLIC >\r\n"
        "<html>\r\n"
        "<head>\r\n"
        "   <title>404 Not Found</title>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "<h1>Not Found</h1>\r\n"
        "<p>The requested URL was not found on this server.</p>\r\n"
        "</body>\r\n"
        "</html>\r\n";
}

void generate_home(HTTP_RESPONSE * hr){
    hr->version = "HTTP/1.1";
    hr->status_code = "200"; 
    hr->reason_phrase = "OK";

    hr->headers="Content-Type: text/html; charset=UTF-8";

    hr->body = 
        "<!DOCTYPE HTML PUBLIC >\r\n"
        "<html>\r\n"
        "<head>\r\n"
        "   <title>Home Page</title>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "<h1>Home Page!</h1>\r\n"
        "<p>Welcome to the home page of the HTTP Server in C Project.</p>\r\n"
        "</body>\r\n"
        "</html>\r\n";
}