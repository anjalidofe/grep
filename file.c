#include "header.h"
#include "ll.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void usage() {
    printf("  DSA MINIPROJECT GREP\n");
    printf("  --Anjali Dofe, MIS No. 111903137\n");
    printf("  Usage :  grep [OPTION...] PATTERNS [FILE...]\n");
    printf("  --help : outputs a usage message and exits\n");
    printf("  -V or --version : outputs version number of GREP and exits\n");
    printf("  -w : for matching whole words\n");
    printf("  -v : for invert matching i.e., non matching\n");
    printf("  -i : for matching case insensitive pattern\n");
    printf("  -v -i : for printing case insensitive non matching pairs\n");
    printf("  -v -w : for printing whole word non matching pairs\n");

    return;
}

int types(char type, int option){
    if(type == 'i'){
        option = CASEINSENSITIVE;
    }
    else if(type == 'v'){
       option = INVERTMATCH;
    }
    else if(type == 'w') {
        option = WHOLEWORD;
    }
    else if(type == 'o'){
        option = ONLYMATCH;
    }
    return option;
}

int openfile(char *filename, int option, char *pattern, int option1){
    char ch;
    line l1;
    init_line(&l1);
    FILE *fp;
    int boolean = 0, boolean1 = 0;
    fp = fopen(filename, "r+");
    if (fp==NULL){
        printf("Invalid file argument");
		exit(0);
    }
    else{
		while((ch = getc(fp)) != EOF ){
            if (ch!='\n' && ch !='\0'){
                append(&l1,ch);
            }
            else{
                if (option == INVERTMATCH && option1 != CASEINSENSITIVE && option1 != WHOLEWORD){
                    boolean = non_matching_pattern(l1, pattern);
                    if(boolean){
                        display(l1);
                    }
                }
                else if(option == WHOLEWORD){
                    boolean = match_whole_string(l1, pattern);
                    if(boolean){
                        display(l1);
                    }
                }
                else if(option == CASEINSENSITIVE){
                    boolean = caseinsensitive_matching(l1,pattern);
                    if(boolean){
                        display(l1);
                    }
                }
                else if(option == INVERTMATCH && option1 == CASEINSENSITIVE){
                    boolean1 = caseinsensitive_matching(l1,pattern);
                    if(!boolean1){
                        display(l1);
                    }
                }
                else if(option == INVERTMATCH && option1 == WHOLEWORD){
                    boolean1 = match_whole_string(l1,pattern);
                    if(!boolean1){
                        display(l1);
                    }
                }
                else if(option == ONLYMATCH){
                    boolean = match_pattern(l1, pattern);
                    if(boolean)
                        display(l1);
                }
                destroy_line(&l1);

            }
        }
        fclose(fp);
    }
    return 0;
}
