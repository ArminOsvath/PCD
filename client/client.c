#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"
#include <sys/stat.h>

#define MAX 80
#define PORT 9326

// external variables
extern int isVerbose;

errCode myTransfer(FILE* fp, char* filename, int socketDescriptor)
{

    fp = fopen(filename, "r");

    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    // printf("size: %ld \n", size);

    if (fp == NULL) 
    {
        perror("[-]Error in reading file.");
        exit(1);
    }

    write (socketDescriptor, &size, sizeof(size));

    char send_buffer[size];
        
    int nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    while(!feof(fp))
    {
        write(socketDescriptor, send_buffer, sizeof(send_buffer));
        nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    }
    return RET_NO_ERR;
}

int main()
{
    // variables
    int socketDescriptor, connDescriptor;
    struct sockaddr_in servAddr;
    errCode retVal;
    FILE* fp;
    char* filename = "./client/image/Image.jpg";

    // seting up socket
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
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
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



    retVal = myTransfer(fp, filename, socketDescriptor);
    // printf("%d", retVal);
    
    close(socketDescriptor);
}
