#ifndef C_STD_HEADER_FILES
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <conio.h>
#endif

#ifndef OWN_H_FILES
#include "search.h"
#include "manual.h"
#endif

#define E_MESSAGE \
"\n" \
"-l -- print lines of pattern \n"                 \
"-c -- cout pattern repeats \n"                   \
"-n -- disabling register depening \n"            \
"-w -- search by giving word pattern \n"          \



void usage(char message[])
{
    fprintf(stderr, "\n\t %s\n\n%s",SEARCH_FOR_PATTERN, message);
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
    if (argc <= 1)
        usage(E_MESSAGE);
    else if (strcmp(argv[1], "-l") == 0) // ./gr argv[1]
    {
        if (argc <= 2)
        {
            printf("Error: file not specified for option %s", argv[1]);
            exit(1);
        }
        else
        {
            FILE * fs;
            char ch;
            fs = fopen(argv[2], "r");
            if (fs == NULL)
                fprintf(stderr,"Error: no such file \n");
            while ((ch = fgetc(fs)) != EOF)
            {
                printf("%c", ch);
            }
        }
    }
}