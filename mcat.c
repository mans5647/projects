#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUFFSIZE 4048
#define NAME "mcat" 


void error(char arg[])
{
    errno = 1;
    fprintf(stderr, "Option %s requires an argument\nError code: %i",arg, errno);
    exit(EXIT_FAILURE);
}
void redirect(char arg[]);
/*
*/
int main(int argc, char **argv)
{
    const char buffer[BUFFSIZE];
    if (argc <= 1)
    {
        while (fgets(buffer, BUFFSIZE, stdin))
        {
            fprintf(stdout, "%s", buffer);
        }
    }
    else if (!strcmp(argv[1], "-r"))
    {
        if (argc <= 2)
        {
            error(argv[1]);
        }
            FILE * readsm;
            int curfile = 0;
            if (argc > 2)
                curfile = 2;
            else curfile = 0;
            while (curfile < argc) 
            {
                if (argc > 2)
                {
                    readsm = fopen(argv[curfile], "r");
                    if (readsm == NULL) 
                    {
                        fprintf(stderr, "%s: %s: No such file or directory\n", NAME, argv[curfile]);
                        exit(1);
                    }
                }
                while (fgets(buffer, BUFFSIZE, readsm))
                {
                    fprintf(stdout, "%s", buffer);
                }
                fclose(readsm);
                curfile++;
            }
    }
    else if (!strcmp(argv[1], "-w"))
    {
        if (argc <= 2)
        {
            error(argv[1]);
        }
        redirect(argv[2]);
    }
    return 0;
}
void redirect(char arg[])
{
    FILE * writeto;
    writeto = fopen(arg, "w");
    char buf[BUFFSIZE], sym;
    for (int w = 0; w < BUFFSIZE; w++)
    {
        sym = fgetc(stdin);
        buf[w] = sym;
        if (feof(stdin))
        {
            fputs(buf, writeto);
            break;
        }
    }
    fclose(writeto);
    exit(EXIT_SUCCESS);
}