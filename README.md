# HTTP Server written only in C 

## Build instructions for the Load Balancer: 
`make head`   
`./head` to run.   
  
## Build instructions for Individual Servers: 
*Note* You must change the IP address at the top of src/server/sever.c to be the IP of the load balancer. 
`make server`   
`./server` to run.   

## Cleanup instructions: 
`make clean`

## Testing instructions:
`make client_test`  
`./test_client`  
To remove tests:   
`make clean_test` 

## Further work: 
* Create a HTTP Response file, and then use html_tags.h to generate real responses by writing to that file, then send the entire file as the response 