#include "/home/dj/VSC/C_Cpp/Project/lib/mylib.h"

#define MAX 80
#define PORT 9326
#define SIZE 2048
// external variables
extern int isVerbose;

char cli[SIZE] = "/client";
char imgName[SIZE];
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
    printf("[Path]: cliPath: %s \n", cliPath);
    snprintf(imgPath, sizeof(imgPath)+sizeof(cliPath), "%s/image", cliPath);
    snprintf(fullPath, sizeof(fullPath)+sizeof(imgPath), "%s/%s", imgPath, imgName);
    printf("[Path]: imgPath: %s \n", imgPath);
    printf("[Path]: fullPath: %s \n", fullPath);

}
int print_usage(usageErr errnum)
{
    printf("Wrong usage, please follow this example:\nclient/client -I Img2.jpg -v -g -b -m -h\n");
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
    filter myFilter;
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
                strncpy(imgName, optarg, sizeof(imgName));
                verbose("[Case]: Case I set");
                errnum = USG_OK;
                break;
            case 'v':
                if(atoi(optarg))
                {
                    isVerbose = 1;
                    verbose("[Case]: Case verbose set");
                }
                else
                {
                    verbose("[Case]: wrong verbose something");
                    print_usage(USG_VERBOSE);
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
                    myFilter.filterCounter++;
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
                errnum = USG_W_ARG;
        }
    }
    // printf("[Arguments]: Inside getargs imgname = %s \n", imgName);
    // printf("[Arguments]: %d filters required\n", myFilter.filterCounter);

    return myFilter;
}

int main(int argc, char* argv[])
{
    // variables
    // isVerbose = 0;

    int socketDescriptor, connDescriptor;
    struct sockaddr_in servAddr;
    errCode retVal;
    filter myFilter;

    myFilter=getArgs(argc, argv);
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
    send(socketDescriptor, &myFilter, sizeof(myFilter), 0); //send filters
    myPath();
    myWrite(socketDescriptor);
    // printf("%d", retVal);
    
    close(socketDescriptor);
}
