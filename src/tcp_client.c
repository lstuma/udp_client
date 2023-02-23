#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>


int establish_connection(char* address, int port)
{
    int sock;
    struct sockaddr_in serveraddress;
	struct sockaddr_in client;

	// create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	// check that socket works
	if (sock == -1) {
		printf("[!] An error has occured while trying to create socket on local machine - Exiting!\n");
		return -1;
	}
	else
		printf("[+] Socket has successfully been created..\n");

	// set 0
	bzero(&serveraddress, sizeof(serveraddress));

	// assign address family (ipv4), address, port
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr(address);
	serveraddress.sin_port = htons(port);

	// connect to server
	if(!connect(sock, (struct sockaddr*)&serveraddress, sizeof(serveraddress)))
	{
		printf("[+] Connection successfull..\n");
		return sock;
	}
	else {
		printf("[!] Connection failed - Extiting!\n");
		exit(0); return -1;
	}
}

int sends(int sock, char* msg)
{
    printf("[*] Sending: %s", msg);
    write(sock, msg, sizeof(msg));
}

char* receives(int sock)
{
    char msg[512];
    bzero(msg, sizeof(msg));

    read(sock, msg, sizeof(msg));
    printf("[*] Received: %s", msg);
    return msg;
}

int main()
{
	int sock;

	// allow sending of messages
    sock = establish_connection("192.168.1.115", 42068);

    // send message to server
    sends(sock, "Hello World!\n");
    sends(sock, "Bye World!\n");
    sends(sock, "World!\n");
    sends(sock, "Hey!\n");
    sends(sock, "Bye\n");

    // receive message from server
    while(1)
    receives(sock);

	// close socket
	close(sock);

	return 0;
}
