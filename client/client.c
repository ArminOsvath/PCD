#include "../lib/mylib.h"

#define MAX 80
#define PORT 8080
#define SIZE 2048
// external variables
extern int isVerbose;

char cli[SIZE] = "/client";
char imgName[SIZE];
char cliPath[SIZE];
char imgPath[SIZE];
char fullPath[SIZE];
char dirpath[SIZE];


errCode myWrite(int socketDescriptor)
{
    // file var
    struct stat stbuf;
    off_t* offt = 0;
    ssize_t bts;
    int imgfd;
    
    imgfd = open(fullPath, O_RDONLY);

    if(isVerbose)
        printf("imgfd %d \n", imgfd);

    // get size
    fstat(imgfd, &stbuf);
    verbose("[+] Got the size of the image");

    verbose("[+] Writing the image");
    // send the size
    write (socketDescriptor, &stbuf.st_size, sizeof(stbuf.st_size));
    if(isVerbose)
        printf("stbuf size %ld \n", stbuf.st_size);

    bts = sendfile(socketDescriptor, imgfd, offt, stbuf.st_size);

    if(isVerbose)
    {
        printf("bts = %ld \n",bts);
        printf("errno: %s\n", strerror(errno));
    }

    close(imgfd);
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

    if(isVerbose)
        printf("[Path]: cliPath: %s \n", cliPath);

    snprintf(imgPath, sizeof(imgPath)+sizeof(cliPath), "%s/image", cliPath);
    snprintf(fullPath, sizeof(fullPath)+sizeof(imgPath), "%s/%s", imgPath, imgName);
    snprintf(dirpath, sizeof(dirpath)+sizeof(cliPath), "%s/%s", cliPath, "output/");

    if(isVerbose)
    {
        printf("[Path]: imgPath: %s \n", imgPath);
        printf("[Path]: dirpath: %s \n", dirpath);
        printf("[Path]: fullPath: %s \n", fullPath);
    }

}
int print_usage()
{
    printf("Wrong usage, please follow this example:\nclient/client -I Img2.jpg -v 1 -g -b -m -h\n");
    printf("-I /path : Image required  \n");
    printf("-v 1/0 : Verbose required \n");
    printf("-b : binary optional\n");
    printf("-B : blur optional\n");
    printf("-c : contour optional\n");
    printf("-e : equalized historigram optional\n");
    printf("-G : gaussian blur optional\n");
    printf("-g : gray optional\n");
    printf("-h : HSV optional\n");
    printf("-m : median optional\n");
    printf("-s : sobel optional\n");
    exit(0);
}
filter getArgs(int argc, char* argv[])
{
    usageErr errnum;
    filter myFilter = {0};
    int opt; //getlong integer

    //creere structura pentru getopt_long
    static struct option long_options[] =
    {
        {"image",               required_argument,  0,  'I'},
        {"verbose",             required_argument,  0,  'v'},
        {"binary",              optional_argument,  0,  'b'},
        {"blur",                optional_argument,  0,  'B'},
        {"contour",             optional_argument,  0,  'c'},
        {"equalizedhistogram",  optional_argument,  0,  'e'},
        {"gblur",               optional_argument,  0,  'G'},
        {"gray",                optional_argument,  0,  'g'},
        {"HSV",                 optional_argument,  0,  'h'},
        {"median",              optional_argument,  0,  'm'},
        {"sobel",               optional_argument,  0,  's'},
        {"0",                   0,                  0,  0  }  
    };

    //index getopt_long
    int long_index = 0;
        //while reading parameters
    while((opt = getopt_long(argc, argv,"I:v:bBceGghms",
            long_options,&long_index)) != -1 )
    {
        switch(opt)
        {
            case 'I':
                //variabila se transforma intr-un numar pozitiv
                if(optarg)
                {
                    strncpy(imgName, optarg, sizeof(imgName));
                    verbose("[Case]: Case I set");
                }
                break;
            case 'v':
                if(atoi(optarg))
                {
                    myFilter.isVerbose = 1;
                    verbose("[Case]: Case verbose set");
                }
                else if (0 == atoi(optarg))
                {
                    myFilter.isVerbose = 0;
                    verbose("[Case]: Case verbose set 0");
                }
                else
                {
                    verbose("[Case]: wrong verbose something");
                    print_usage();
                }
                break;
            case 'b':
                if(!myFilter.isBinary)
                {
                    myFilter.isBinary = 1;
                    verbose("[Case]: Case b set");
                    myFilter.filterCounter++;
                }
                break;
            case 'B':
                if(!myFilter.isBlur)
                {
                    myFilter.isBlur = 1;
                    verbose("[Case]: Case B set");
                    myFilter.filterCounter++;
                }
                break;
            case 'c':
                if(!myFilter.isContour)
                {
                    myFilter.isContour = 1;
                    verbose("[Case]: Case c set");
                    myFilter.filterCounter = myFilter.filterCounter+2;
                }
                break;
            case 'e':
                if(!myFilter.isEqHis)
                {
                    myFilter.isEqHis = 1;
                    verbose("[Case]: Case e set");
                    myFilter.filterCounter++;
                }
                break;
            case 'G':
                if(!myFilter.isGblur)
                {
                    myFilter.isGblur = 1;
                    verbose("[Case]: Case G set");
                    myFilter.filterCounter++;
                }
                break;
            case 'g':
                if(!myFilter.isGray)
                {
                    myFilter.isGray = 1;
                    verbose("[Case]: Case g set");
                    myFilter.filterCounter++;
                }
                break;
            case 'h':
                if(!myFilter.isHSV)
                {
                    myFilter.isHSV = 1;
                    verbose("[Case]: Case h set");
                    myFilter.filterCounter++;
                }
                break;
            case 'm':
                if(!myFilter.isMedian)
                {
                    myFilter.isMedian = 1;
                    verbose("[Case]: Case m set");
                    myFilter.filterCounter++;
                }
                break;
            case 's':
                if(!myFilter.isSobel)
                {
                    myFilter.isSobel = 1;
                    verbose("[Case]: Case s set");
                    myFilter.filterCounter++;
                }
                break;
            default: 
                //Default exit
                print_usage();
        }
    }
    if(myFilter.isVerbose)
    {
        printf("[Arguments]: Inside getargs imgname = %s \n", imgName);
        printf("[Arguments]: %d filters required\n", myFilter.filterCounter);
    }

    return myFilter;
}

int main(int argc, char* argv[])
{
    int socketDescriptor;
    struct sockaddr_in servAddr;
    errCode retVal;
    filter myFilter;
    char buffer[1025] = "message";  //data buffer of 1K 
    int pwd = 0;

    myFilter=getArgs(argc, argv);
    isVerbose=myFilter.isVerbose;
    printf("[Args]: #of args %d\n",myFilter.filterCounter);
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
    servAddr.sin_addr.s_addr = inet_addr("192.168.117.129");
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
    if(isVerbose)
        printf("printf filcounter %d \n", myFilter.filterCounter);

    send(socketDescriptor, &buffer, sizeof(buffer), 0);
    // printf("buffeR: %s \n", buffer);
    // write (socketDescriptor, &buffer, sizeof(buffer));
    send(socketDescriptor, &pwd, sizeof(pwd), 0);

    send(socketDescriptor, &imgName, sizeof(imgName), 0); //send img name
    
    send(socketDescriptor, &myFilter, sizeof(myFilter), 0); //send filters
    myPath();
    myWrite(socketDescriptor);

    char recvName[SIZE];
    for(int i = 0; i<myFilter.filterCounter; i++)
    {
        struct stat stbuf;
        ssize_t bts;
        off_t* offt = 0;

        recv(socketDescriptor, &recvName, sizeof(recvName), 0);
        if(isVerbose)
            printf("[+] recvName: %s\n", recvName);

        verbose("[+] Reading the size");
        read(socketDescriptor, &stbuf.st_size, sizeof(stbuf.st_size));
        if(isVerbose)
            printf("got the size %ld\n", stbuf.st_size);

        bzero(fullPath, sizeof(fullPath));
        snprintf(fullPath, sizeof(fullPath)+sizeof(recvName), "%s/%s", dirpath, recvName);

        // byte variables
        int imgfd = open(fullPath, O_CREAT|O_WRONLY, 0600);
        if(isVerbose)
            printf("imgfd %d \n", imgfd);
        verbose("[+] Opened the image successfully");
        bts = sendfile(imgfd, socketDescriptor, offt, stbuf.st_size);
        if(isVerbose)
        {
            printf("bts = %ld \n",bts);
            printf("errno: %s\n", strerror(errno));
        }
        close(imgfd);
    }
    close(socketDescriptor);


}
