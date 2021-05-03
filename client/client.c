#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326

// external variables
extern int isVerbose;

errCode myTransfer(int socketDescriptor)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Client <%d> : ",getpid());
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(socketDescriptor, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(socketDescriptor, buff, sizeof(buff));
        printf("Client echo <%d> : %s", getpid(), buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }

    return RET_NO_ERR;
}

int main()
{
    // variables
    int socketDescriptor, connDescriptor;
    struct sockaddr_in servAddr;
    errCode retVal;

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

    retVal = myTransfer(socketDescriptor);
    printf("%d", retVal);
    
    close(socketDescriptor);
}
