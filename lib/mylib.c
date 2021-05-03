#include "mylib.h"
int isVerbose = 1;
errCode verbose(char* myStr)
{
    if(isVerbose)
    {
        printf("%s \n",myStr);
    }
}