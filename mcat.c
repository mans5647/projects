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
void concat(char arg[], char arg2[], char arg3[]);
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
    else if (!strcmp(argv[1], "-c") || !strcmp(argv[1], "--concat"))
    {
        if (argc <= 2)
        {
            error(argv[1]);
        }
        else if (argc <=3)
        {
            fprintf(stderr, "%s :%s: One file is not enough\n", NAME, argv[1]);
            exit(EXIT_FAILURE);
        }
        else if (argc <=4)
        {
            fprintf(stderr,"%s: %s: File-destination needed\n", NAME, argv[1]);
            exit(EXIT_FAILURE);
        }
        else 
            concat(argv[2],argv[3],argv[4]);
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
void concat(char arg[], char arg2[], char arg3[])
{
    FILE * fp1;
    FILE * fp2;
    FILE * fp3;
    fp1 = fopen(arg, "r");
    fp2 = fopen(arg2, "r");
    fp3 = fopen(arg3, "w+");
    char ch;
    if (fp1 == NULL)
    {
        fprintf(stderr, "%s: %s: No such file or directory\n", NAME, arg);
        exit(EXIT_FAILURE);
    }
    else if (fp2 == NULL )
    {
        fprintf(stderr, "%s: %s: No such file or directory\n", NAME, arg2);
        exit(EXIT_FAILURE);
    }
    else if (fp1 == NULL && fp2 == NULL)
    {
        fprintf(stderr, "%s: %s, %s: Specified files not found\n", NAME, arg,arg2);
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(fp1)) != EOF)
        fputc(ch, fp3);
    while ((ch = fgetc(fp2)) != EOF)
        fputc(ch, fp3);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    exit(EXIT_SUCCESS);
}