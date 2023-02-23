#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()


int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddress;
	struct sockaddr_in client;

	// create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// check that socket works
	if (sockfd == -1) {
		print("[!] An error has occured while trying to create socket on local machine - Exiting!\n");
		return 1;
	}
	else
		printf("[+] Socket has successfully been created..\n");

	// set 0
	bzero(&servaddress, sizeof(servaddress));

	// assign address family (ipv4), address, port
	servaddress.sin_family = AF_INET;
	servaddress.sin_addr.s_addr = inet_addr("192.168.1.115");
	serveraddress.sin_port = htons(42069);

	// connect to server
	if(connect(sockfd, (struct sockaddr)&serveraddress), sizeof(serveraddress))
	{
		printf("[+] Connection successfull..\n");
	}
	else {
		printf("[!] Connection failed - Extiting!\n");
		exit(0); return 1;
	}

	// close socket
	close(sockfd);

	return 0;
}