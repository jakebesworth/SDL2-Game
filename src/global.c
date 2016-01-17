#ifndef __CSTD__
#define __CSTD__
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#endif

#ifndef __CSYSTEM__
#define __CSYSTEM__
#include <unistd.h>
#include <time.h>
#ifndef F_OK
#define F_OK 0
#endif
#endif

char * getDate()
{
    char * date = NULL;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    date = asctime(timeinfo);

    if(date[strlen(date)-1] == '\n')
    {
        date[strlen(date)-1] = '\0';
    }

    return date;
}
