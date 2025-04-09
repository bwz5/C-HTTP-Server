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
        1. Parse the HTTP request (Using external library) (Done)
        2. Process the Request (Done)
        3. Send back an HTTP Object (Need to decide what I want to send)

    Database Portion: 
        1. Create some database 
        2. On HTTP Requests, query the database accordingly 

# Build instructions: 
`make server`
`./server` to run. 

# Cleanup instructions: 
`make clean`

# Testing instructions:
`make client_test`
`./test_client`

To remove tests: 
`make clean_test`