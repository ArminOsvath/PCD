#ifndef MYLIB_H
#define MYLIB_h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <arpa/inet.h>
typedef struct filter
{
    bool isGray;
    bool isBinary;
    bool isBlur;
    bool isContour;
    bool isEqHis;
    bool isGblur;
    bool isHSV;
    bool isMedian;
    bool isSobel;
    int filterCounter;
}filter;

typedef enum usageErr
{
    USG_OK       = 0,
    USG_VERBOSE  = 1,
    USG_W_ARG    = 2,
    USG_W_NUM    = 3,
    USG_MANY     = 4,

    USG_ERR      = 5,

}usageErr;
typedef enum errCode
{
    RET_NO_ERR = 0,
    


    RET_ERR = 5
}errCode;

errCode verbose(char* myStr);

#endif //MYLIB_H