#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326
#define SIZE 2048
// external variables
extern int isVerbose;

char cli[SIZE] = "/client";
char imgName[SIZE] = "Image.jpg";
char cliPath[SIZE];
char imgPath[SIZE];
char fullPath[SIZE];

errCode myWrite(int socketDescriptor)
{


    // file var
    FILE* img = fopen(fullPath, "r");
    
    // get size
    int size;
    fseek(img, 0, SEEK_END); // img pointer to eof position
    size = ftell(img); // number of bytes from the beginning of the file
    fseek(img, 0, SEEK_SET); // img pointer to beginning
    verbose("[+] Got the size of the image");
    // printf("size: %ld \n", size);

    if (img == NULL) 
    {
        verbose("[-] Error file might be empty or wrong file.");
        exit(1);
    }

    verbose("[+] Writing the image");
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
    verbose("[+] Writing the image success");
    return RET_NO_ERR;
}

void myPath()
{
    if (getcwd(cliPath, sizeof(cliPath)) != NULL) 
    {
        // printf("Current working dir: %s\n", proj);
        strncat(cliPath, cli, SIZE);
        // printf("proj: %s\n", proj);
        verbose("[+] Set the PWD");
        memset(cli, '\0', SIZE);
        strncpy(cli, cliPath, SIZE);
    }
    else
    {
        verbose("[-] Failed to set the PWD");
    }
    printf("cliPath: %s \n", cliPath);
    snprintf(imgPath, sizeof(imgPath)+sizeof(cliPath), "%s/image", cliPath);
    snprintf(fullPath, sizeof(fullPath)+sizeof(imgPath), "%s/%s", imgPath, imgName);
    printf("imgPath: %s \n", imgPath);
    printf("fullPath: %s \n", fullPath);

}

int main()
{
    // variables
    // isVerbose = 0;
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


    send(socketDescriptor, &imgName, sizeof(imgName), 0); //send img name
    myPath();
    myWrite(socketDescriptor);
    // printf("%d", retVal);
    
    close(socketDescriptor);
}
