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
char dirpath[SIZE];

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
        
        snprintf(filename, sizeof(filename)+sizeof(in_file->d_name), "%s%s", dirpath,in_file->d_name);
        printf("opening file %s\n",filename);
        send(connDescriptor, in_file->d_name, sizeof(in_file->d_name), 0); //send img name
        verbose("Sent file name \n");
        entry_file = fopen(filename, "r");
        if (entry_file == NULL)
        {
            printf("Error : Failed to open entry file - %s\n", strerror(errno));

            return 1;
        }
        while (fgets(buffer, BUFSIZ, entry_file) != NULL)
        {
            int size;
            fseek(entry_file, 0, SEEK_END); // img pointer to eof position
            size = ftell(entry_file); // number of bytes from the beginning of the file
            fseek(entry_file, 0, SEEK_SET); // img pointer to beginning
            printf("[+] Got the size of the image %s\n",filename);
            write (connDescriptor, &size, sizeof(size));

            char buffer[size];

            // send the bytes
            int nb = fread(buffer, 1, sizeof(buffer), entry_file);
            while(!feof(entry_file))
            {
                write(connDescriptor, buffer, sizeof(buffer));
                nb = fread(buffer, 1, sizeof(buffer), entry_file);
            }
            verbose("[+] Writing the image success");

        }

        fclose(entry_file);
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

    // myDirs(connDescriptor);

    close(socketDescriptor);
    
}