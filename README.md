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
* Implement some form of load balancing 