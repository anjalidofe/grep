#define CASEINSENSITIVE 10
#define WHOLEWORD 20
#define INVERTMATCH 30
//#define ONLYMATCH 40
#define COUNT 50
#define MAXIMUM 60
#define EXP 70
#define LINENUMBER 80
#define COUNTINVERTMATCH 90
#define COUNTWHOLEWORD 100
#define COUNTCASEINSENSITIVE 110
#define CASEINSENSITIVEWHOLE 120
#define FILENAME 13
#define RECURSION 130

void usage();

int openfile(char *filename, int option, char *pattern, int flag, int num, int option1);

int types(char type, int option);

void filename(int option, char *pattern, char *name); // for -l and -r uses <dirent.h>

void listFiles(const char *path); //recursively to list all files in working directory
