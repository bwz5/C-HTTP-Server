#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <stdio.h> 



typedef struct {
    // Message Status-Line
    const char * version; 
    const char * status_code; 
    const char * reason_phrase; 

    const char * headers; 

    // Body 
    const char * body; 
} HTTP_RESPONSE; 

/* 
Returns a C-string of the HTTP_RESPONSE
*/
int flatten_response_object(const char ** response, HTTP_RESPONSE * http_response); 

/*
Returns a 404 "Not Found" HTML Response 
*/
void generate_404(HTTP_RESPONSE * hr); 

/*
Brings you to the HOME ("localhost:8080/") page
*/
void generate_home(HTTP_RESPONSE * hr); 

#endif 