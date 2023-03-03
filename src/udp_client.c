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
    printf("LENGTH: %d\n", length);
    while(pos < length) {
        printf("[*] Sending: %s\n", msg+pos);
        pos += sendto(sock, msg+pos, strlen(msg+pos), MSG_CONFIRM, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    }
}

void udpreceive(int sock, char* msg_out, char* address)
{
    // source address (port does not matter here)
    struct sockaddr_in serveraddress;
    makeaddress(address, 65535, &serveraddress);

    int pos = 0;
    pos += recvfrom(sock, msg_out, strlen(msg_out), 4096, MSG_WAITALL, (struct sockaddr*)&serveraddress);
}

int udpclose(int sock)
{
  // Returns 1 if successful, otherwise returns 0
  return 1+close(sock);
}

int main()
{
    int sock;

    // allow sending of messages
    sock = udpopen();

    // send message to server
    udpsend(sock, "Hello Server!\n", "192.168.1.115", 42068);

    // close socket
    close(sock);

    return 0;
}
