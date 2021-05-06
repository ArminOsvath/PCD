#ifndef MYLIB_H
#define MYLIB_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>

typedef enum errCode
{
    RET_NO_ERR = 0,
    


    RET_ERR = 5
}errCode;

errCode verbose(char* myStr);

#endif //MYLIB_H