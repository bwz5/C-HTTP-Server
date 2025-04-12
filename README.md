# HTTP(S) Server written only in C 

## Build instructions for the Load Balancer (Normal HTTP): 
`make head`   
`./head` to run.   

## HTTPS Support:  
For SSL/TLS encryption, see the /security/server* files. Fill them with your certificate and key. 

Next, you must install `openssl` on your system, either with a package manager or from source. It can be found here:  https://github.com/openssl/openssl?tab=readme-ov-file.  
See the Makefile to change the "-L" argument on line 43 if your openssl is installed elsewhere. 

Then,  
`make head SECURE=1`  
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
* Create more pages for users to access 