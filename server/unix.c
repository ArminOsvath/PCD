#include "../lib/mylib.h"


int unisock(const char* path)
{
    struct sockaddr_un sdname;
    int sd; 
    size_t size;
    sd = socket (PF_LOCAL, SOCK_DGRAM, 0);
    if (sd < 0) 
    {
       perror ("socket");
           pthread_exit (NULL);

    }
    sdname.sun_family = AF_LOCAL; 
    strncpy (sdname.sun_path, path, sizeof (sdname.sun_path));
    sdname.sun_path[sizeof (sdname.sun_path) - 1] = '\0';

    size = SUN_LEN(&sdname);
    /* You can use size = SUN_LEN (&name) ; instead */

    /* Now BIND the socket */
    if (bind (sd, (struct sockaddr *) &sdname, size) < 0) {
    //    perror ("bind");
    pthread_exit (NULL);
    }
    return 1;
}

void *uni_main(void *str)
{
    char *sd = (char*) str;
    while(1)
    {
        int *status;
        if(unisock(sd))
        {
            pid_t pid = fork();
            if(pid == 0)
            {
                system("ps aux | grep server/server | grep -v 'color' > out.txt");    
            }
            wait(status);
            FILE* fp = fopen( "out.txt","r" );
            if (NULL != fp) {
                fseek (fp, 0, SEEK_END);
                int size = ftell(fp);
                printf("\n [Unix]: before if \n");
                if (0 == size)
                {
                    printf("[Unix]: file is empty\n");
                    pid_t pid2 = fork();
                    if (0 == pid2)
                    {
                        system("make runs");
                    }
                }
            }
            fclose(fp);
        }
    }
    pthread_exit (NULL) ;
}