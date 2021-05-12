#include "../lib/mylib.h"

#define MAX 80
#define PORT 9326
#define SIZE 2048

extern int isVerbose;
char srv[SIZE] = "/server";
char imgName[SIZE];
char srvPath[SIZE];
char imgPath[SIZE];
char fullPath[SIZE];
char dirpath[SIZE];

errCode myRead(int connDescriptor)
{
    // get size
    // int size;
    struct stat stbuf;
    ssize_t bts;
    off_t* offt = 0;
    read(connDescriptor, &stbuf.st_size, sizeof(stbuf.st_size));
    verbose("[+] Reading the size");
    printf("got the size %ld\n", stbuf.st_size);
    // byte variables
    // char bytes[size];
    // FILE* img = fopen(fullPath, "w");
    int imgfd = open(fullPath, O_CREAT|O_WRONLY, 0600);
    printf("imgfd %d \n", imgfd);
    verbose("[+] Opened the image successfully");
    bts = sendfile(imgfd, connDescriptor, offt, stbuf.st_size);
    printf("bts = %ld \n",bts);
    printf("errno: %s\n", strerror(errno));
    // read the bytes
    // int rByte = read(connDescriptor, bytes, size);
    // fwrite(bytes, 1, sizeof(bytes), img);
    // printf("rbyte: %d\n",rByte);
    // while (rByte > 0)
    // {
    //     rByte = read(connDescriptor, bytes, size);
    //     // printf("rbyte: %d\n",rByte);
    // } 
    close(imgfd);

    verbose("[++++++] Wrote the image successfully");
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
    printf("[Path]: srvPath: %s \n", srvPath);
    snprintf(imgPath, sizeof(imgPath)+sizeof(srvPath), "%s/image", srvPath);
    snprintf(fullPath, sizeof(fullPath)+sizeof(imgPath), "%s/%s", imgPath, imgName);
    snprintf(dirpath, sizeof(dirpath)+sizeof(srvPath), "%s/%s", srvPath, "output/");
    printf("[Path]: imgPath: %s \n", imgPath);
    printf("[Path]: dirpath: %s \n", dirpath);
    printf("[Path]: fullPath: %s \n", fullPath);

}
void forkIt(filter myFilter)
{
    int status;
    for(int i = 0; i < myFilter.filterCounter; i++)
    {
        if(myFilter.isGray)
        {
            myFilter.isGray = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: gray");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/gray.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
            
        }
        else if(myFilter.isBinary)
        {
            myFilter.isBinary = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: binary");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/binary.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
        else if(myFilter.isBlur)
        {
            myFilter.isBlur = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: blur");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/blur.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
        else if(myFilter.isContour)
        {
            myFilter.isContour = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: contourfill");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/contourfill.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
        else if(myFilter.isEqHis)
        {
            myFilter.isEqHis = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: equalizedhistogram");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/equalizedhistogram.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
        else if(myFilter.isGblur)
        {
            myFilter.isGblur = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: gblur");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/gblur.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
        else if(myFilter.isHSV)
        {
            myFilter.isHSV = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: hsv");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/hsv.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
        else if(myFilter.isMedian)
        {
            myFilter.isMedian = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: median");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3", "./scripts/median.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
        else if(myFilter.isSobel)
        {
            myFilter.isSobel = 0;
            pid_t pid = fork();
            if (0 == pid)
            {
                verbose("Executing script: sobel");
                fflush(stdout);
                execlp("/usr/bin/python3", "/usr/bin/python3",  "./scripts/sobel.py", srvPath, fullPath, imgName, NULL);
                printf("Execution error has happened \n");
            }
            else
                continue;
        }
    }
    while(wait(&status) > 0);
    exit(0);
}
int myDirs(int connDescriptor)
{
    DIR* FD;
    struct dirent* in_file;
    FILE    *entry_file;
    char    buffer[SIZE];
    char    filepath[SIZE];
    char    filename[SIZE];

    if (NULL == (FD = opendir(dirpath)))
    {
        printf("Error: failed to open input directory %s\n", strerror(errno));
        return 1;
    }

    while ((in_file = readdir(FD))) 
    {
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))    
            continue;
        strncpy(filename, in_file->d_name, sizeof(filename));
        snprintf(filepath, sizeof(filepath)+sizeof(in_file->d_name), "%s%s", dirpath,in_file->d_name);
        printf("opening file %s\n",filepath);
        send(connDescriptor, filename, sizeof(filename), 0); //send img name

        struct stat stbuf;
        off_t* offt = 0;
        ssize_t bts;

        // FILE* img = fopen(filepath, "r");
        int imgfd = open(filepath, O_RDONLY);
        printf("imgfd %d \n", imgfd);
        fstat(imgfd, &stbuf);
        // get size
        // int size = 1;
        // int size;
        // fseek(img, 0, SEEK_END); // img pointer to eof position
        // size = ftell(img); // number of bytes from the beginning of the file
        // fseek(img, 0, SEEK_SET); // img pointer to beginning
        verbose("[+] Got the size of the image");
        // printf("size: %ld \n", size);


        verbose("[+] Writing the image");
        // send the size
        write (connDescriptor, &stbuf.st_size, sizeof(stbuf.st_size));
        printf("stbuf size %ld \n", stbuf.st_size);

        // send the bytes
        bts = sendfile(connDescriptor, imgfd, offt, stbuf.st_size);
        printf("bts = %ld \n",bts);

        printf("errno: %s\n", strerror(errno));
        close(imgfd);
        
        verbose("[+++++++] Writing the image success");
    }
}
int main(int argc, char* argv[])
{
    int socketDescriptor, connDescriptor, len;
    struct sockaddr_in servAddr, client;
    filter myFilter;

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
    recv(connDescriptor, &myFilter, sizeof(myFilter), 0);
    printf("[Connection]: Filter counter  %d \n", myFilter.filterCounter);
    myPath();
    myRead(connDescriptor);

    pid_t pid = fork();
    int status;
    if(0 > pid)
    {
        verbose("error in making pid1");
    }
    else if(0 == pid)
    {
        printf("preparing for forkit inside main\n");
        forkIt(myFilter);
    }
    else
    {
        while((pid = wait(&status) > 0))
        {
            fprintf(stderr,"[C]: Parent : %ld, Me = %ld you are outside\n",(long)getppid(),(long)getpid());
        };
    }

    printf("I should be last\n");

    myDirs(connDescriptor);

    close(socketDescriptor);
    
}