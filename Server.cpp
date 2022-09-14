#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(){

    // create socket
    int socket_description = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_description == -1){
        cout << "Unable to create socket" << endl;
        return 1;
    }

    struct sockaddr_in server;
    struct sockaddr_in client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8421);

    // bind to port
    if(bind(socket_description,(struct sockaddr*) &server, sizeof(server)) < 0){
        cout << "Unable to bind to port" << endl;
        return 1;
    }
    cout << "Socket bound, waiting for client..." << endl;

    // listen for client
    listen(socket_description, 3);

    int c = sizeof(struct sockaddr_in);
    int new_socket = accept(socket_description, (struct sockaddr*) &client, (socklen_t*)&c);
    if(new_socket < 0){
        cout << "Failed to accept client connection" << endl;
        return 1;
    }

	char client_message[100];
    cout << "Client connection accepted" << endl;

    // Receive message from client
    int read_size;
    while((read_size = recv(new_socket, client_message, 100, 0)) > 0){
        // Print Client Message
        cout << "Client: " << client_message << endl;
    }

    if(read_size == 0){
        cout << "Client disconnected" << endl;
    }
    else if(read_size == -1){
        cout << "Server could not receive message from client" << endl;
        return 1;
    }

    close(socket_description);

    return 0;
}