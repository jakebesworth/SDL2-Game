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

#include "global.h"

char * fileGetContents(char * filename)
{
    FILE * fp = NULL;
    char * string = NULL;
    int end;

    if(filename == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: file variable NULL\n", getDate(), __FILE__, __LINE__);
        return NULL;
    }

    fp = openFile(filename, "r");

    if(fp == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: cannot open file {%s}\n", getDate(), __FILE__, __LINE__, filename);
        return NULL;
    }

    /* Read contents in one go into variable */
    fseek(fp, 0, SEEK_END);
    end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    string = calloc(end, (sizeof(char) * end + 1));

    if(string == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Fatal Error: Malloc return NULL, system out of memory\n", getDate(), __FILE__, __LINE__);
    }
    else if(fread(string, 1, end, fp) != end)
    {
       fprintf(stderr, "[%s][%s: %d]Warning: fread unsuccessful\n", getDate(), __FILE__, __LINE__);
    }

    fclose(fp);

    return string;
}

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

FILE * openFile(char * filename, char * mode)
{
    FILE * fp = NULL;
    int length;

    if(filename == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Filename NULL\n", getDate(), __FILE__, __LINE__);
        return NULL;
    }

    if(mode == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: Mode NULL\n", getDate(), __FILE__, __LINE__);
        return NULL;
    }

    length = (strlen(filename) - 1);

    /* Disallow ending newlines */
    if(filename[length] == '\n')
    {
        filename[length] = '\0';
    }

    /* Check if file exists */
    if((access(filename, F_OK)) != 0)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: File \"%s\" does not exist\n", getDate(), __FILE__, __LINE__, filename);
        return NULL;
    }

    fp = fopen(filename, mode);

    if(fp == NULL)
    {
        fprintf(stderr, "[%s][%s: %d]Warning: File \"%s\" could not be opened\n", getDate(), __FILE__, __LINE__, filename);
    }

    return fp;
}
