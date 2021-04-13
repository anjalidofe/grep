#include "header.h"
#include "ll.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>


void usage() {
    printf("  DSA MINIPROJECT GREP\n");
    printf("  --Anjali Dofe, MIS No. 111903137\n");
    printf("  Usage :  grep [OPTION...] PATTERNS [FILE...]\n");
    printf("  --help : outputs a usage message and exits\n");
    printf("  -V or --version : outputs version number of GREP and exits\n");
    printf("  -w : for matching whole words\n");
    printf("  -v : for invert matching i.e., non matching\n");
    printf("  -i : for matching case insensitive pattern\n");
    printf("  -h : for printing without filename\n");
    printf("  -H : for printing with filename\n");
    printf("  -l : for printing filename with match when filename is not specified\n");
    printf("  -r : for printing all filenames with matches\n");
    printf("  -n : for printing line number of matched lines\n");
    printf("  -m # : for printing upto # matched lines (considering # is a number)\n");
    printf("  -c : to print the count of matched lines\n");
    printf("  for multi-word patterns or patterns with spaces add them in \" \" commas\n");


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
    else if(type == 'l'){
        option = FILENAME;
    }
    else if (type == 'c'){
        option = COUNT;
    }
    else if(type == 'm'){
        option = MAXIMUM;
    }
    else if(type == 'e'){
        option = EXP;
    }
    else if(type == 'n'){
        option = LINENUMBER;
    }
    else if(type == 'r'){
        option = RECURSION;
    }
    return option;
}


int openfile(char *filename, int option, char *pattern, int flag, int num, int option1){ //flag 1 for H and 0 for h and num is for -m
    int j = 0, k = 0, l = 0, m = 0, n = 0, z = 0, f = 0;
    char ch;
    line l1;
    init_line(&l1);
    FILE * fp;
    int boolean = 0, count = 0, boolean1 = 0;
    fp = fopen(filename, "r"); //opening file in read mode
    if (fp == NULL){
        printf("Invalid file argument");
        exit(0);
    }
    else{
        while((ch = getc(fp)) != EOF ){
            if (ch != '\n' && ch != '\0'){
                append(&l1, ch);
            }
            else{
                k++; //for line number
                if (option == EXP || option == RECURSION || option == FILENAME){
						boolean = match_pattern(l1, pattern);
						if(boolean){
							if(flag){
								if(option == FILENAME && num == 1){ //only when num is 1 print file name this is to avoid printing file name again and again
									printf(" %s \n",filename);
									num++;
									continue;
								}
								if(option != FILENAME && flag == 1) //whenever flag is 1 print filename
									printf(" %s : ",filename);
							}
							if(option1 == LINENUMBER)
								printf(" %d : ", k);

							if(option != FILENAME)
								display(l1);
						}
				}
                else if (option == INVERTMATCH && option1 != CASEINSENSITIVE && option1 != WHOLEWORD){
                    boolean = non_matching_pattern(l1, pattern);
                    if(boolean){
                        if(option1 == COUNTINVERTMATCH) // ci
                            m++;
                        if(flag && option1 != COUNTINVERTMATCH){
                            printf(" %s : ",filename);
                        }
                        if(option1 == LINENUMBER)
                            printf(" %d : ", k);
                        if(option1 != COUNTINVERTMATCH)
                            display(l1);
                    }
                }
                else if(option == WHOLEWORD){
                    boolean = match_whole_string(l1, pattern);
                    if(boolean){
                        if(option1 == COUNTWHOLEWORD) // cw
                            f++;
                        if(flag && option1 != COUNTWHOLEWORD){
                            printf(" %s : ",filename);
                        }
                        if(option1 == LINENUMBER)
                            printf(" %d : ", k);
                        if(option1 != COUNTWHOLEWORD)
                            display(l1);
                    }
                }
                else if (option == COUNT){ //counting number of times pattern has appeared in file
                    boolean = match_pattern(l1, pattern);
                    if(boolean){
                        count = count + 1;
                    }
                }
                else if(option == CASEINSENSITIVE){
                    boolean = caseinsensitive_matching(l1, pattern);
                    if(boolean){
                        l++;
                        if(flag && option1 != COUNTCASEINSENSITIVE){
                            printf(" %s : ",filename);
                        }
                        if(option1 == LINENUMBER)
                            printf(" %d : ", k);
                        if(option1 != COUNTCASEINSENSITIVE)
                            display(l1);
                    }
                }
                else if(option == MAXIMUM){ //-m
                    boolean = match_pattern(l1, pattern);
                    if(boolean && j < num && j != num){
                        if(flag){
                            printf(" %s : ",filename);
                        }
                        if(option1 == LINENUMBER)
                            printf(" %d : ", k);
                        display(l1);
                    }
                    if(boolean){ //after each match increment j until it reaches num
                        j++;
                    }
                }
                else if(option == INVERTMATCH && option1 == CASEINSENSITIVE){ //-v -i
                    boolean1 = caseinsensitive_matching(l1, pattern);
                    if(!boolean1){
                        if(num == 1)
                            n++;
                        if(flag && num != 1){
                            printf(" %s : ",filename);
                        }
                        if(num != 1)
                            display(l1);
                    }
                }
                else if(option == INVERTMATCH && option1 == WHOLEWORD){
                    boolean1 = match_whole_string(l1,pattern);
                    if(!boolean1){
                        if(num == 1)
                            z++;
                        if(flag && num != 1){
                            printf(" %s : ",filename);
                        }
                        if(num != 1)
                            display(l1);
                    }
                }
                else if(option == CASEINSENSITIVEWHOLE){
                    boolean = caseinsensitive_whole(l1, pattern);
                    if(boolean){
                        if(flag){
                            printf(" %s: ",filename);
                        }
                        display(l1);
                    }
                }
                destroy_line(&l1);
            }
        }
        fclose(fp);
        if(option == COUNT && flag == 0)
			printf(" %d\n",count);
        if(option1 == FILENAME)
			printf(" %d : ", k);
        else if(option == COUNT && flag == 1){
			printf(" %s :  ",filename);
			printf(" %d \n",count);
        }
        else if((option1 == COUNTCASEINSENSITIVE && flag == 0))
			printf(" %d\n",l);
        else if((option1 == COUNTWHOLEWORD && flag == 0))
			printf(" %d\n",f);
        else if((option1 == COUNTINVERTMATCH && flag == 0))
			printf(" %d\n",m);
        else if((option1 == COUNTCASEINSENSITIVE && flag == 1)){
			printf(" %s :  ",filename);
			printf(" %d \n",l);
        }
        else if((option1 == COUNTINVERTMATCH && flag == 1)){
            printf(" %s :  ",filename);
            printf(" %d \n",m);
        }
        else if((option1 == COUNTWHOLEWORD && flag == 1)){
			printf(" %s:  ",filename);
			printf(" %d \n",f);
        }
        else if(option1 == CASEINSENSITIVE && num == 1 && flag == 1){
            printf(" %s :  ",filename);
            printf(" %d \n",n);
        }
        else if(option1 == CASEINSENSITIVE && num == 1 && flag == 0)
            printf(" %d \n",n);
        else if(option1 == WHOLEWORD && num == 1 && flag == 1){
            printf(" %s :  ",filename);
            printf(" %d \n",z);
        }
        else if(option1 == WHOLEWORD && num == 1 && flag == 0)
            printf(" %d \n",z);
	}
	return 0;
}

void filename(int option, char *pattern, char *name){
    char path1[1000];
    int static flag1;
    DIR *dir;
    struct dirent *entry; //structure having member char d_name[]
    if (!(dir = opendir(name))) //if unable to open directory
        return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1000];
            if (strcmp(entry->d_name, ".") != 0 || strcmp(entry->d_name, "..") != 0)
                continue;
            snprintf(path, sizeof(path), "%s->%s", name, entry->d_name);
            strcpy(path1, path);
            flag1 = 1;
            filename(option, pattern, path);
        }
        else{
            if(strcmp(entry->d_name, "111903137_GREP.cbp") != 0){
                if(flag1 != 1){
                openfile(entry->d_name, option, pattern, 1, 1, 0);
                }
                else{
                snprintf(path1, sizeof(path1), "%s->%s", name, entry->d_name);
                openfile(path1, option, pattern, 1, 1, 0);
                }
            }
        }
    }
    closedir(dir);
}

void listFiles(const char *path){
    struct dirent *dp;
    DIR *dir = opendir(path);
    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        printf(" %s\n",dp->d_name);

    }
    // Close directory stream
    closedir(dir);
}
