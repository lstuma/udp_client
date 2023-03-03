#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>


int udpopen()
{
    int sock;

    // create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    // check that socket works
    if (sock == -1)
        return 0;

    return sock;
}

void makeaddress(char* address, short int port, struct sockaddr_in* sockaddress)
{
    // set 0
    bzero(sockaddress, sizeof(sockaddress));

    // assign address family (ipv4), address, port
    sockaddress -> sin_family = AF_INET;
    sockaddress -> sin_addr.s_addr = inet_addr(address);
    sockaddress -> sin_port = htons(port);
}

int udpsend(int sock, char* msg, char* address, short int port)
{
    // destionation address
    struct sockaddr_in serveraddress;
    makeaddress(address, port, &serveraddress);

    int pos = 0; int length = strlen(msg);
    while(pos < length) {
        pos += sendto(sock, msg+pos, strlen(msg+pos), MSG_CONFIRM, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    }
}

void udpreceive(int sock, char* msg_out)
{
    int pos = 0;
    pos += read(sock, msg_out, 4096);
}

int udpclose(int sock)
{
  // Returns 1 if successful, otherwise returns 0
  return 1+close(sock);
}