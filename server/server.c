#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326

errCode myTransfer(int socketDescriptor)
{
    int n;
    FILE *fp;
    char *filename = "rcv.jpg";
    char buffer[6500];

    fp = fopen(filename, "w");
    while (1) {
    n = recv(socketDescriptor, buffer, 6500, 0);
    if (n <= 0){
        break;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, 6500);
    }
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

    int size;
    read(connDescriptor, &size, sizeof(int));

    char p_array[size];
    char* current = p_array;
    FILE* img = fopen("./server/image/img.jpg", "w");
    int nb = read(connDescriptor, p_array, size);

    while (nb > 0)
    {
        fwrite(p_array, 1, sizeof(p_array), img);
        nb = read(connDescriptor, p_array, size);
    } 
    fclose(img);
    // myTransfer(connDescriptor);


    close(socketDescriptor);
    
}