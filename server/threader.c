#include "../lib/mylib.h"
#include <pthread.h>

#define UNSOCKET "/tmp/uni"
#define PORT 9326

void *uni_main (void *args) ;
void *server_main (void *args) ;
int main()
{
    pthread_t inet, uni;
    pthread_create(&uni, NULL, uni_main, UNSOCKET);
    int internetport = PORT;
    pthread_create(&inet, NULL, server_main, &internetport);

    pthread_join(uni, NULL);
    pthread_join(inet,NULL);

    return 0;
}