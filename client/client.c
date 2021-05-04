#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"
#include <sys/stat.h>

#define MAX 80
#define PORT 9326

// external variables
extern int isVerbose;

errCode myWrite(int socketDescriptor)
{
    // file var
    char* filename = "./client/image/Image.jpg";
    FILE* img = fopen(filename, "r");
    
    // get size
    int size;
    fseek(img, 0, SEEK_END);
    size = ftell(img);
    fseek(img, 0, SEEK_SET);

    // printf("size: %ld \n", size);

    if (img == NULL) 
    {
        perror("[-] Error file might be empty or wrong file.");
        exit(1);
    }

    // send the size
    write (socketDescriptor, &size, sizeof(size));

    char buffer[size];

    // send the bytes
    int nb = fread(buffer, 1, sizeof(buffer), img);
    while(!feof(img))
    {
        write(socketDescriptor, buffer, sizeof(buffer));
        nb = fread(buffer, 1, sizeof(buffer), img);
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



    retVal = myWrite(socketDescriptor);
    // printf("%d", retVal);
    
    close(socketDescriptor);
}
