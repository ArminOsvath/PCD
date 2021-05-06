#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326
#define SIZE 2048

extern int isVerbose;
char srv[SIZE] = "/server";
char imgName[SIZE];
char srvPath[SIZE];
char imgPath[SIZE];
char fullPath[SIZE];

errCode myRead(int connDescriptor)
{
    // get size
    int size;
    read(connDescriptor, &size, sizeof(int));
    verbose("[+] Reading the size");

    // byte variables
    char bytes[size];
    FILE* img = fopen(fullPath, "w");
    verbose("[+] Opened the image successfully");
    
    // read the bytes
    int rByte = read(connDescriptor, bytes, size);
    while (rByte > 0)
    {
        fwrite(bytes, 1, sizeof(bytes), img);
        rByte = read(connDescriptor, bytes, size);
    } 
    fclose(img);

    verbose("[+] Wrote the image successfully");
    return RET_NO_ERR;
}

void myPath()
{
    if (getcwd(srvPath, sizeof(srvPath)) != NULL) 
    {
        // printf("Current working dir: %s\n", proj);
        strncat(srvPath, srv, SIZE);
        // printf("proj: %s\n", proj);
        verbose("[+] Set the PWD");
        memset(srv, '\0', SIZE);
        strncpy(srv, srvPath, SIZE);
    }
    else
    {
        verbose("[-] Failed to set the PWD");
    }
    printf("srvPath: %s \n", srvPath);
    snprintf(imgPath, sizeof(imgPath)+sizeof(srvPath), "%s/image", srvPath);
    snprintf(fullPath, sizeof(fullPath)+sizeof(imgPath), "%s/%s", imgPath, imgName);
    printf("imgPath: %s \n", imgPath);
    printf("fullPath: %s \n", fullPath);

}

int main(int argc, char* argv[])
{
    // isVerbose = 0;
    int socketDescriptor, connDescriptor, len;
    struct sockaddr_in servAddr, client;
    errCode retVal;

    // set path

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
    recv(connDescriptor, &imgName, sizeof(imgName), 0);
    myPath();
    myRead(connDescriptor);


    close(socketDescriptor);
    
}