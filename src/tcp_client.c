#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>


int tcpconnect(char* address, int port)
{
    int sock;
    struct sockaddr_in serveraddress;
    struct sockaddr_in client;

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    // check that socket works
    if (sock == -1) {
        printf("[!] An error has occured while trying to create socket on local machine - Exiting!\n");
        return 0;
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
        return 0;
    }
}

int tcpsend(int sock, char* msg)
{
    int pos = 0; int length = strlen(msg);
    printf("LENGTH: %d\n", length);
    while(pos < length) {
        printf("[*] Sending: %s\n", msg+pos);
        pos += write(sock, msg+pos, sizeof(msg+pos));
    }
}

void tcpreceive(int sock, char* msg_out)
{
    read(sock, msg_out, sizeof(msg_out));
    printf("[*] Received: %s\n", msg_out);
}

int tcpclose(int sock)
{
  // Returns 1 if successful, otherwise returns 0
  return 1+close(sock);
}

int main()
{
    int sock;

    // allow sending of messages
    sock = tcpconnect("192.168.1.115", 42068);

    // send message to server
    tcpsend(sock, "Hello Server!\n");

    // close socket
    close(sock);

    return 0;
}
