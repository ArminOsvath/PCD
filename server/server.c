#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326

errCode myRead(int connDescriptor)
{
    // get size
    int size;
    read(connDescriptor, &size, sizeof(int));

    // byte variables
    char bytes[size];
    FILE* img = fopen("./server/image/img.jpg", "w");

    // read the bytes
    int rByte = read(connDescriptor, bytes, size);
    while (rByte > 0)
    {
        fwrite(bytes, 1, sizeof(bytes), img);
        rByte = read(connDescriptor, bytes, size);
    } 
    fclose(img);

    return RET_NO_ERR;
}

int main()
{
    int socketDescriptor, connDescriptor, len;
    struct sockaddr_in servAddr, client;
    errCode retVal;

    // set path
    char srv[9] = "/server";
    char proj[2048];
    if (getcwd(proj, sizeof(proj)) != NULL) 
    {
        // printf("Current working dir: %s\n", proj);
        strncat(proj, srv, 9);
        // printf("srv: %s\n", proj);
    }

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

    myRead(connDescriptor);


    close(socketDescriptor);
    
}