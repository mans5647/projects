#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <signal.h>
#include <stdbool.h>
void sig_callb(int sig_num)
{
    printf("Terminated with signal: %d", sig_num);
    exit(EXIT_SUCCESS);
}
int main ()
{
 signal(SIGINT, sig_callb);
 while (true)
 {
    printf("PROGRAM RUNNING. To stop: Ctrl + C\n");
    sleep(2);
 }
}