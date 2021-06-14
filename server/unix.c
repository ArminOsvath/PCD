#include "../lib/mylib.h"


int unisock(const char* path)
{
    struct sockaddr_un sdname;
    int sd; 
    size_t size;
    sd = socket (PF_LOCAL, SOCK_DGRAM, 0);
    if (sd < 0) 
    {
        printf("[Unix]: sd < 0\n");
       
        pthread_exit (NULL);

    }
    sdname.sun_family = AF_LOCAL; 
    strncpy (sdname.sun_path, path, sizeof (sdname.sun_path));
    sdname.sun_path[sizeof (sdname.sun_path) - 1] = '\0';

    size = SUN_LEN(&sdname);

    /* Now BIND the socket */
    if (bind (sd, (const struct sockaddr *) &sdname, size) < 0) {
    //    perror ("bind");
        if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        {
            printf("[Unix]: Error: bind failed %s\n", strerror(errno));
            pthread_exit (NULL);
        }
        else 
        {
            printf("[Unix]: Bind success");
        }
    }


    return 1;
}

void *uni_main(void *str)
{
    const char *sd = (char*) str;
    if(unisock(sd))
    {
        while(1)
        {
            sleep(3);
            system("ps aux | grep server/threader | grep -v 'color' | grep -v 'grep' > out.txt"); 
            FILE* fp = fopen( "out.txt","r" );
            if (NULL != fp) {
                fseek (fp, 0, SEEK_END);
                int size = ftell(fp);
                fclose(fp);
                printf("\n[Unix]: before if \n");
                if (0 == size)
                {
                    printf("[Unix]: file is empty\n");
                    system("make runs");
                    exit(0);
                }
            }
        }
    }
        else
        {
            printf("[Unix]: socket fail\n");
        }
    pthread_exit (NULL) ;
}