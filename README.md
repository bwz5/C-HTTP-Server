# HTTP Server written only in C 

## Build instructions: 
`make server`
`./server` to run. 
This starts a server on your localhost IP on port 8080.

## Cleanup instructions: 
`make clean`

## Testing instructions:
`make client_test`
`./test_client`

To remove tests: 
`make clean_test`

## Further work: 
* Add support for other HTTP Request Methods other than GET 

## TODO:
* Create servers that will accept connections to the HEAD and then parse the message, returning a response 

, connect them to a network (using connect()), create bash scripts for them to run ./server on startup 


