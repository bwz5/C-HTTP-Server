#include "src/server.h" 

int main(){
    server serve = create_server(); 

    while (1){
        write_to_connection(&serve, "Hello there\n"); 
        sleep(2); 
    }

    return 0; 
}