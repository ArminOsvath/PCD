#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326

errCode myTransfer(int socketDescriptor)
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
  
        // read the message from client and copy it in buffer
        read(socketDescriptor, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("Server echo <%d>: %s \n Server <%d> : ", getpid(), buff,  getpid());
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;
  
        // and send that buffer to client
        write(socketDescriptor, buff, sizeof(buff));
  
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
    return RET_NO_ERR;
}

int main()
{
    int socketDescriptor, connDescriptor, len;
    struct sockaddr_in servAddr, client;
    errCode retVal;

    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == socketDescriptor)
    {
        verbose("[-] Socket creation failed");
        exit(0);
    }
    else
    {
        verbose("[+] Socket creation success");
    }

    bzero(&servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);

    if(0 != bind(socketDescriptor,(struct sockaddr*)&servAddr, sizeof(servAddr)))
    {
        verbose("[-] Binding failed");
        exit(0);
    }
    else
    {
        verbose("[+] Binding success");
    }

    if(0 != listen(socketDescriptor,5))
    {
        verbose("[-] Listening failed");
        exit(0);
    }
    else
    {
        verbose("[+] Listening success, client connected");
    }

    len = sizeof(client);
    connDescriptor = accept(socketDescriptor, (struct sockaddr*)&client, &len);

    if(0 > connDescriptor)
    {
        verbose("[-] Connection with the client failed");
        exit(0);
    }
    else
    {
        verbose("[+] Connection success, client connected");
    }


    myTransfer(connDescriptor);

    close(socketDescriptor);
    
}