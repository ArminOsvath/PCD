#include "../lib/mylib.h"


int unisock(const char* path)
{
    struct sockaddr_un sdname;
    int sd; 
    size_t size;
    sd = socket (PF_LOCAL, SOCK_DGRAM, 0);
    if (sd < 0) 
    {
        exit(0);
    }
    sdname.sun_family = AF_LOCAL; 
    strncpy (sdname.sun_path, path, sizeof (sdname.sun_path));
    sdname.sun_path[sizeof (sdname.sun_path) - 1] = '\0';

    size = 0;
    /* You can use size = SUN_LEN (&sdname) ; instead */

    /* Now BIND the socket */
    if (bind (sd, (struct sockaddr *) &sdname, size) < 0) {
    //    perror ("bind");
    pthread_exit (NULL);
    }
}

void *uni_main(void *str)
{
    char *sd = (char*) str;
    while(1)
    {

        if(unisock(sd))
        {
            pid_t pid = fork();
            if(pid == 0)
            {
                system("ps aux | grep server/server | grep -v 'color' > out.txt");
                FILE* fp = fopen( "out.txt","r" );
                if (NULL != fp) {
                    fseek (fp, 0, SEEK_END);
                    int size = ftell(fp);

                    if (0 == size) {
                        printf("file is empty\n");
                        system("make runs");
                    }
                }
                fclose(fp);
            }
        }
    }
    // pthread_exit (NULL) ;
}