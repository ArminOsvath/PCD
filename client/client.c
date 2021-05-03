#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326


int main()
{
    int socketDescriptor, connDescriptor;
    struct sockaddr_in servers, client;

    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == socketDescriptor)
    {
        
    }
    extern int isVerbose;
    verbose("Hello");
}