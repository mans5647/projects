#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PROGRAM_NAME "wcn"
#define VERSION 1.0
#define VENDOR "none"
#define BUFFER_SZ 100
#define STATE_IN 1
#define STATE_OUT 0
void usage_msg() 
{
printf("%s. Counts a little more than usual WC. Usage: wcnew [OPTIONS]..(f)..[..FILE..]\n ",PROGRAM_NAME);
printf("	Options: \n");
printf("	(no options) - prog counts: characters, words, strings, new lines, TABulations, SPACES. This is default\n");
printf("	f, fr -- reads file stream, and counts above declared thinngs\n");
printf("	C, symbols -- counts only chars\n");
printf("	W, words -- counts only words\n");
printf("	L, lines -- count only lines\n");
printf("	#, space -- reads only spaces\n");
printf("	+, combine -- combine counting units\n");
printf("	\t\t\n");
printf("	\t\n");
printf("	[ Name: %s ][ Version %.1f ][ Vendor: %s ]", PROGRAM_NAME, VERSION, VENDOR);
printf("	\n");
printf("	Try: `wc_new hlp` or `wc help-in-hall` for investigation\n");
}
void phelp() // get help from: wc_new hlp
{
	printf("OKEY\n");
}
	int main(int argc, char *argv[])
{
int wc_WORD, wc_CHAR, wc_NLINE, wc_STATE, wc_USIN, wc_TAB, wc_SPACE, wc_SPEC, wc_NUM, lines; // wc_USIN - user input in cicle
 	wc_WORD = wc_CHAR = wc_NLINE = wc_TAB = wc_SPACE = wc_SPEC = wc_NUM = lines = 0;
		wc_STATE = STATE_OUT;
	if (argc <= 1) // sumple mode. NO ARGS
	{
		while ((wc_USIN = getchar()) != EOF)
		{
			++wc_CHAR;
		if (wc_USIN == '\n')
			++wc_NLINE;
		if (wc_USIN == ' ')
			++wc_SPACE;
		if (wc_USIN == '\t')
			++wc_TAB;
		if (wc_USIN == ' ' || wc_USIN == '\t' || wc_USIN == '\n')
			wc_STATE = STATE_OUT;
		else if (wc_STATE == STATE_OUT)
		//
		{
			wc_STATE = STATE_IN;
			++wc_WORD;
		} 
		/* */
		}
	printf("\n");
	printf("\tCharacters: %d | Words: %d | Lines: %d | Tabs: %d | Spaces: %d\n\n", wc_CHAR, wc_WORD, wc_NLINE, wc_TAB, wc_SPACE);
	}     else if (!strcmp(argv[1], "C") || !strcmp(argv[1], "symbols")) 
	  {
		for (wc_CHAR; getchar() != EOF; ++wc_CHAR)
			;
		printf("\n");
		printf("\tCharacters: %d\n\n", wc_CHAR);
		exit(EXIT_SUCCESS);
	  }   else if (!strcmp(argv[1], "W") || !strcmp(argv[1], "words"))
	    {
		while ((wc_USIN = getchar()) != EOF)
		{
			if (wc_USIN == '\t' || wc_USIN == '\n' || wc_USIN == ' ')
				wc_STATE = STATE_OUT;
		       	else if (wc_STATE == STATE_OUT)
			{
				wc_STATE = STATE_IN;
				++wc_WORD;
			}	
		}
		printf("\n");
		printf("\tWords: %d\n\n", wc_WORD);
		exit(EXIT_SUCCESS);
	    } else if (!strcmp(argv[1], "L") || !strcmp(argv[1], "lines"))
	      {
		      while((wc_USIN = getchar()) != EOF)
		      {
			      if (wc_USIN == '\n')
				      ++wc_NLINE;
		      }
		      printf("\n");
	      printf("\tLines: %d\n\n", wc_NLINE);
	      exit(EXIT_SUCCESS);
	      }
	      else if (!strcmp(argv[1], "sS") || !strcmp(argv[1], "specsym"))
	      {
		      while ((wc_USIN = getchar()) != EOF)
		      {
			      ++wc_CHAR;
			      if (wc_USIN >= '0' && wc_USIN <='9')
				      ++wc_NUM;
			      else
				      ++wc_SPEC;
		      }
	      printf("Spec-symbols: %d", wc_SPEC);
	      exit(EXIT_SUCCESS);
	      } else if (!strcmp(argv[1], "N") || !strcmp(argv[1], "Numbers")) 
	     	 {
			 while ((wc_USIN = getchar()) != EOF)
			 {
				 ++wc_CHAR;
				 if (wc_USIN >= '0' && wc_USIN <= '9')
					 ++wc_NUM;
			 }
		 printf("Numbers: %d", wc_NUM);
		 exit(EXIT_SUCCESS);
		 } 
	       else if (!strcmp(argv[1], "s##") || !strcmp(argv[1], "spaces"))
	       {
		       while ((wc_USIN = getchar()) != EOF)
		       {
			       ++wc_CHAR;
			       if (wc_USIN == ' ')
				       ++wc_SPACE;
		       }
		 printf("\tSpaces: %d\n\n", wc_SPACE);
		 exit(EXIT_SUCCESS);
	       } else if (!strcmp(argv[1], "hlp") || !strcmp(argv[1], "help-in-hall"))
	       {
		       usage_msg();
		       phelp();
		       
	       } 
}
