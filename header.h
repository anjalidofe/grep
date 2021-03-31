#define CASEINSENSITIVE 10
#define WHOLEWORD 20
#define INVERTMATCH 30
#define ONLYMATCH 40


void usage();
int openfile(char *filename, int option, char *pattern, int option1);
int types(char type, int option);
