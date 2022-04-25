#include "../lib/mylib.h"
#include <arpa/inet.h>
#include <sys/time.h>
#include <netinet/in.h> 

#define MAX 80
#define PORT 8080
#define SIZE 2048
#define TRUE 1
#define FALSE 0
extern int isVerbose;
char srv[SIZE] = "/server";
char imgName[SIZE];
char srvPath[SIZE];
char imgPath[SIZE];
char fullPath[SIZE];
char dirpath[SIZE];
int pathchecker = 0;
errCode myRead(int connDescriptor)
{
    int imgfd;
    struct stat stbuf;
    ssize_t bts;
    off_t* offt = 0;

    read(connDescriptor, &stbuf.st_size, sizeof(stbuf.st_size));
    if(isVerbose)
        printf("got the size %ld\n", stbuf.st_size);

    verbose("[+] Reading the size");
    printf("Fullpath is: %s \n", fullPath);
    imgfd = open(fullPath, O_CREAT|O_WRONLY, 0600);
    if(isVerbose)
        printf("imgfd %d \n", imgfd);
    printf("open errno: %s\n", strerror(errno));
    

    verbose("[+] Opened the image successfully");

    bts = sendfile(imgfd, connDescriptor, offt, stbuf.st_size);

    if(isVerbose)
    {
        printf("bts = %ld \n",bts);
        printf("errno: %s\n", strerror(errno));
    }

    close(imgfd);

    verbose("[+] Wrote the image successfully");
    return RET_NO_ERR;
}

void myPath()
{
        if(strstr(srvPath,"server") == NULL)
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
        }

    if(isVerbose)
        printf("[Path]: srvPath: %s \n", srvPath);

    if (pathchecker == 0)
    {
        snprintf(imgPath, sizeof(imgPath)+sizeof(srvPath), "%s/image", srvPath);
        // snprintf(fullPath, sizeof(fullPath)+sizeof(imgPath), "%s/%s", imgPath, imgName);
        snprintf(dirpath, sizeof(dirpath)+sizeof(srvPath), "%s/%s", srvPath, "output/");
        pathchecker ++;
    }
    snprintf(fullPath, sizeof(fullPath)+sizeof(imgPath), "%s/%s", imgPath, imgName);

    if(isVerbose)
    {
        printf("[Path]: imgName: %s \n", imgName);
        printf("[Path]: imgPath: %s \n", imgPath);
        printf("[Path]: dirpath: %s \n", dirpath);
        printf("[Path]: fullPath: %s \n", fullPath);
    }

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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
            if (0 == pid)
            {
                printf("[+Gray]:Entering forkit, img name is: %s ,\n", imgName);
                printf("Entering forkit, srvPath is: %s ,\n", srvPath);
                printf("Entering forkit, fullPath is: %s ,\n", fullPath);
                printf("Value of filter gray is: isGray:%d \n", myFilter.isGray);
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
            if (pid < 0)
            {
                printf("Exiting fork <0");
                exit(0);
            }
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
        char *name =strtok(imgName,".");
        printf("name: %s \n",name);

        printf("in_file->d_name: %s \n",in_file->d_name);
        printf("imgName: %s \n",imgName);
        if(strstr(in_file->d_name, name))
        {
            strncpy(filename, in_file->d_name, sizeof(filename));
            snprintf(filepath, sizeof(filepath)+sizeof(in_file->d_name), "%s%s", dirpath,in_file->d_name);
            if(isVerbose)
                printf("opening file %s\n",filepath);

            send(connDescriptor, filename, sizeof(filename), 0); //send img name

            int imgfd;
            struct stat stbuf;
            off_t* offt = 0;
            ssize_t bts;

            imgfd = open(filepath, O_RDONLY);
            if(isVerbose)
                printf("imgfd %d \n", imgfd);

            // get size
            fstat(imgfd, &stbuf);
            verbose("[+] Got the size of the image");


            verbose("[+] Writing the image");
            // send the size
            write (connDescriptor, &stbuf.st_size, sizeof(stbuf.st_size));
            if(isVerbose)
                printf("stbuf size %ld \n", stbuf.st_size);

            // send the bytes
            bts = sendfile(connDescriptor, imgfd, offt, stbuf.st_size);

            if(isVerbose)
            {
                printf("bts = %ld \n",bts);
                // printf("errno: %s\n", strerror(errno));
            }
            close(imgfd);
            
            verbose("[+] Writing the image success");
        }
    }
}
void *server_main(void *str)
{
    int opt = TRUE;
    int client_socket[50], max_clients = 50, activity, i, val, sd;
    int max_sd;
    char *message = "Connected to the client version 1:* \r\n";
    char buffer[1025];  //data buffer of 1K 

    int pwd;

    int socketDescriptor, connDescriptor, len;
    struct sockaddr_in servAddr, client;
    filter myFilter;
    int status;
    pid_t pid;

    fd_set readfds;

    for (i = 0; i< max_clients; i++)
    {
        client_socket[i] = 0;
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

    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
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

    printf("Listener on port %d \n", PORT);  

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

    printf("waiting for connections ...");

    while(TRUE)
    {
        // clear socket set
        FD_ZERO(&readfds);

        // add master socket to set
        FD_SET(socketDescriptor, &readfds);
        max_sd = socketDescriptor;

        for(i = 0; i< max_clients; i++)
        {
            sd = client_socket[i];
            if (sd > 0)
                FD_SET(sd ,&readfds);
            if(sd > max_sd)
                max_sd = sd;
        }
        activity = select ( max_sd + 1, &readfds, NULL, NULL, NULL);
        if(( activity < 0) && (errno != EINTR))
        {
            printf("Select error");
        }

        if(FD_ISSET(socketDescriptor, &readfds))
        {
            if((connDescriptor = accept(socketDescriptor, (struct sockaddr*)&client, (socklen_t*)&len)) < 0)
            {
                perror("Accept");
                exit(EXIT_FAILURE);
            }
        
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , connDescriptor , inet_ntoa(client.sin_addr) , ntohs(client.sin_port)); 

            for(i = 0; i < max_clients; i++)
            {
                if(client_socket[i] == 0)
                {
                    client_socket[i] = connDescriptor;
                    printf("Adding to list of sockets as %d\n" , i);  
                       break; 
                }
            }
        }
        
        //else it's operations on sockets

        for ( i = 0; i< max_clients; i++)
        {
            sd = client_socket[i];
            if(FD_ISSET(sd, &readfds))
            {
                if((val = recv( sd , buffer, sizeof(buffer),0)) == 0)
                {
                    getpeername(sd , (struct sockaddr*)&client ,
                        (socklen_t*)&len);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(client.sin_addr) , ntohs(client.sin_port)); 

                    close (sd);
                    client_socket[i] = 0;
                }
                else
                {
                    recv(sd, &pwd, sizeof(pwd), 0);
                    if (pwd == 0)
                    {
                        printf("Client connected \n");
                        recv(sd, &imgName, sizeof(imgName), 0);
                        printf("This is the name i received %s\n" , imgName);  
                        recv(sd, &myFilter, sizeof(myFilter), 0); //recieve myfilter
                        isVerbose = myFilter.isVerbose;
                        if(isVerbose)
                            printf("[Connection]: Filter counter  %d \n", myFilter.filterCounter);
                        myPath();
                        myRead(sd);

                        pid = fork();
                        if(0 > pid)
                        {
                            printf("[-] Error in making pid1");
                        }
                        else if(0 == pid)
                        {
                            
                            verbose("preparing for forkit inside main");
                            forkIt(myFilter);
                        }
                        else
                        {
                            while((pid = wait(&status) > 0))
                            {
                                if(isVerbose)
                                    printf("[C]: Parent : %ld, Me = %ld you are outside\n",(long)getppid(),(long)getpid());
                            };
                        }

                        if(isVerbose)
                            printf("errno: %s\n", strerror(errno));
                            
                        if(isVerbose)
                            printf("I should be before myDirs\n");

                        myDirs(sd);

                        if(isVerbose)
                            printf("I should be last\n");
                            // system("rm -rf /home/dj/VSC/C_Cpp/PCD/PCD/server/output/*");
                            // system("rm -rf /home/dj/VSC/C_Cpp/PCD/PCD/server/image/*");
                    }
                    else if(pwd == 1)
                    {
                        sd = connDescriptor;
                        printf("Adding to list of sockets as %d\n" , i);

                        printf("Admin connected \n");
                        char buff[MAX];
                        read(sd, buff, sizeof(buff));
                        if (strncmp("exit", buff, 4) == 0) {
                            printf("Server Exit...\n");
                            pthread_exit(NULL);
                        }
                    }
  
                }
            }
        }

    }
    
}