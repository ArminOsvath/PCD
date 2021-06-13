#include "../lib/mylib.h"

#define MAX 80
#define PORT 9326
#define SIZE 2048

extern int isVerbose;

int main(int argc, char* argv[])
{
    int socketDescriptor;
    struct sockaddr_in servAddr;
    char buffer[1025] = "message";  //data buffer of 1K 


    int pwd = 1;
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == socketDescriptor)
    {
        verbose("[-] Socket creation failed");
    }
    else
    {
        verbose("[+] Socket creation success");
    }

    // cleaning adress
    bzero(&servAddr, sizeof(servAddr));

    // seting up ip and port
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("192.168.159.128");
    servAddr.sin_port = htons(PORT);

    // connect to the server
    if(0 != connect(socketDescriptor, (struct sockaddr*)&servAddr, sizeof(servAddr)))
    {
        verbose("[-] Failed to connect to the server");
        exit(0);
    }
    else
    {
        verbose("[+] Connection success.");
    }
    send(socketDescriptor, &buffer, sizeof(buffer), 0);

    send(socketDescriptor, &pwd, sizeof(pwd), 0);

    char buff[MAX]= "exit";
    write(socketDescriptor, buff, sizeof(buff));
    
    
    close(socketDescriptor);
}
