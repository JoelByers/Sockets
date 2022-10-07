#include <iostream>   
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

int main(){

    // create socket
    int socket_description = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_description == -1){
        cout << "Unable to create socket" << endl;
        return 1;
    }

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("0.0.0.0");
	server.sin_family = AF_INET;
    server.sin_port = htons(8421);

	if (connect(socket_description , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
        cout << "Unable to connect" << endl;
		return 1;
	}

    char client_message[3] = {'h','i','\0'};
    if( send(socket_description , &client_message, strlen(client_message) , 0) < 0)
	{
		cout << "Unable to send message to server";
		return 1;
	}
}