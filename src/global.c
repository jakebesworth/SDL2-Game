/* Standard Include */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Standard System Include */
#include <unistd.h>
#include <time.h>

#ifndef F_OK
#define F_OK 0
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
