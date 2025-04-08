#include "src/server.h"

int main(){

    server Server; 

    create_server(&Server);
    run_server(&Server); 
    
    return 0; 
}