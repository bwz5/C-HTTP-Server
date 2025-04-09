## HTTP Server written only in C 

# TODO: 
    TCP/IP CONNECTION: (Done) 
        1. Create socket 
        2. Specify socket address, port, protocol type 
        3. Bind socket fd to step 2's struct 
        4. Listen for a client connection 
        5. Connect to client 
        6. Process the client's request 

    HTTP Server Portion: 
        1. Parse the HTTP request (Using external library)
        2. Process the Request 
        3. Send back an HTTP Object 

    Database Portion: 
        1. Create some database 
        2. On HTTP Requests, query the database accordingly 

# Build instructions: 
`make server`

# Cleanup instructions: 
`make clean`