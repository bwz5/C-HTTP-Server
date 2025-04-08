#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include <stdio.h> 
#include <util/error.h>
#include <util/hashmap.h>
#include <util/vector.h> 

typedef enum {
    GET, 
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH
} HTTP_METHOD; 

typedef struct {
    HTTP_METHOD method; 
    const char * request_target; // absolute or relative filepath 
    const char * protocol; // usually always HTTP/1.1 

    // TODO: Need a hash map of the headers, so we can store 
    // Key: Value after processing 
    // hash_map<const char *, const char *> headers; 

    const char * body;
} HTTP_REQUEST; 

typedef struct {
    const char * protocol; 
    int status_code; 
    const char * status_text;

    // hash_map<const char *, const char *> Response_headers; 
    // hash_map<const char *, const char *> Representation_headers; 

    const char * body; 
} HTTP_RESPONSE; 

/*
Parses the HTTP message in [buffer]. 
*/
void parse_http(char * buffer, int buffer_len); 

#endif 