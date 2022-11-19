#define SEARCH_FOR_PATTERN "grep search by pattern and print it on stdout"
#ifndef FUNC_PROTOTYPES
extern char search(char pattern[], char txt[]);
extern void e_print(int EXIT_STATUS);
extern void usage(char message[]);
#endif