#include "mylib.h"
#define BUF_SIZE 8192
#define min(m,n) ((m) < (n) ? (m) : (n))
int isVerbose = 1;
errCode verbose(char* myStr)
{
    if(isVerbose)
    {
        printf("%s \n",myStr);
    }
}

ssize_t
sendfile(int out_fd, int in_fd, off_t *offset, size_t count)
{
    off_t orig;

    if (offset != NULL) {

        /* Save current file offset and set offset to value in '*offset' */

        orig = lseek(in_fd, 0, SEEK_CUR);
        if (orig == -1)
            return -1;
        if (lseek(in_fd, *offset, SEEK_SET) == -1)
            return -1;
    }

    size_t totSent = 0;

    while (count > 0) {
        size_t toRead = min(BUF_SIZE, count);

        char buf[BUF_SIZE];
        ssize_t numRead = read(in_fd, buf, toRead);
        if (numRead == -1)
            return -1;
        if (numRead == 0)
            break;                      /* EOF */

        ssize_t numSent = write(out_fd, buf, numRead);
        if (numSent == -1)
            return -1;
        count -= numSent;
        totSent += numSent;
    }

    if (offset != NULL) {

        /* Return updated file offset in '*offset', and reset the file offset
           to the value it had when we were called. */

        *offset = lseek(in_fd, 0, SEEK_CUR);
        if (*offset == -1)
            return -1;
        if (lseek(in_fd, orig, SEEK_SET) == -1)
            return -1;
    }

    return totSent;
}