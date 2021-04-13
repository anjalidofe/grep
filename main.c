#include <stdio.h>
#include <stdlib.h>
#include "ll.h"
#include <string.h>
#include "header.h"
#include <dirent.h>
#include <windows.h>

int main(int argc, char *argv[]){
    int static flag = 0;
    int static option = 0;
    int i = 0;
    int num = 0;

    if(argc == 2 && strcmp(argv[1], "-r") == 0){ //recursively prints all files in the directory
        char path[100] = "..";
        listFiles(path);
        system("Color 0C");
    }
    else if(argc < 3 && strcmp(argv[1], "--help") != 0 && strcmp(argv[1], "--version") != 0 && strcmp(argv[1], "-V") != 0){
        printf("  Usage :  grep [OPTION(S)] PATTERN [FILENAME] \n  Use '--help' for more information.");
        exit(0);
    }
    else if(strcmp(argv[1], "--help") == 0 && argv[2] == NULL){
        usage();
        system("Color D0");
        exit(0);
    }
    else if((strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0) && argv[2] == NULL){
        printf("  Version of GREP is DSA project version 2021\n");
        printf("  COPYRIGHT 2021 by Anjali Ajay Dofe");
        system("Color 50");
        exit(0);
    }
    else{
        if (argv[1][0] != '-'){ //to match pattern without using any options
            if(argc == 3){  //pattern filename
                flag = 0;
                i = 2;
                option = EXP;
                openfile(argv[i], option, argv[1], flag, num, 0);
                 system("Color 05");
            }
            else if(argc > 3){ //grep for multiple files
                flag = 1; // pattern file1 file2 file3.....
                i = 2;
                option = EXP;
                while(i < argc){
                    openfile(argv[i], option, argv[1], flag, num, 0);
                    printf("\n");
                    system("Color 03");
                    i += 1;
                }
            }
        }
        else if (argv[1][0] == '-' && argv[1][1] != 'm' && (strcmp(argv[1],"-e") != 0) && (strcmp(argv[2],"-e") != 0)
                 && argv[1][1] != 'r' && strcmp(argv[2],"-H") != 0 && strcmp(argv[2],"-h") != 0 && argv[1][1] != 'l' &&
                 strcmp(argv[1],"-n") != 0 && strcmp(argv[2],"-n") != 0 && (strcmp(argv[1],"-ci") != 0) && (strcmp(argv[1],"-cv") != 0)
                  && (strcmp(argv[1],"-vi") != 0) && (strcmp(argv[1],"-cvi") != 0) && (strcmp(argv[1],"-vw") != 0)
                  && (strcmp(argv[1],"-cvw") != 0) && (strcmp(argv[1],"-cw") != 0) && (strcmp(argv[1],"-iw") != 0)
                  && (strcmp(argv[1],"-h") != 0) && (strcmp(argv[1],"-H") != 0)) { //-v or -i or -w

			if(argc > 4){ //if multiple files
				i = 3; // -option pattern file1 file2 file3....
				flag = 1; //when multiple files print filenames too
				while(i < argc){
					option = types(argv[1][1], option);
					openfile(argv[i], option, argv[2], flag, num, 0);
					printf("\n");
                    system("Color 0A");
					i++;
				}
			}
			else if(argc == 4){ //if single textfile
				option = types(argv[1][1], option); //-option pattern filename
				i = 3;
				openfile(argv[i], option, argv[2], flag, num,0);
                system("Color 0B");
			}
        }
        else if((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"-H") == 0)){
			if(strcmp(argv[1],"-h") == 0)
				flag = 0;
			else
				flag = 1;
			if(argc == 4){ //for single file
				i = 3;
				option = EXP;
				openfile(argv[i], option ,argv[2], flag, num, 0);
                system("Color 06");
			}
            else if(argc > 4){ //for multiple files
                if(strcmp(argv[1],"-h") == 0)
                    flag = 0;
                else
                    flag = 1;
                i = 3;
                option = EXP;
                while(i < argc){
                    openfile(argv[i], option, argv[2], flag, num, 0);
                    printf("\n");
                    system("Color 08");
                    i++;
                }
            }
        }
        else if(argv[1][0] == '-' && argv[1][1] == 'm' && (strcmp(argv[3],"-e") != 0)){ //for -m
            if(strcmp(argv[3],"-H") == 0){ //format ./anjaligrep -m NUMBER -H pattern filename
                if (argc == 6){
                    flag = 1;
                    option = types(argv[1][1], option);
                    i = 5;
                    openfile(argv[i], option ,argv[4], flag, atoi(argv[2]), 0); //atoi to convert string to integer
                    system("Color 03");
                }
                else{ //for multiple files
                    flag = 1;
                    i = 5;
                    while(i < argc){
                        option = types(argv[1][1], option);
                        openfile(argv[i], option, argv[4], flag, atoi(argv[2]), 0);
                        system("Color 09");
                        printf("\n");
                        i++;
                    }
                }
            }
            if(strcmp(argv[3],"-h") == 0){//format ./anjaligrep -m NUMBER -h pattern filename
                if (argc == 6){
                    flag = 0;
                    option = types(argv[1][1], option);
                    i = 5;
                    openfile(argv[i], option, argv[4], flag, atoi(argv[2]) ,0);
                    system("Color 0A");
                }
                else{
                    flag = 0;
                    i = 5;
                    while(i < argc){ //for multiple files
                        option = types(argv[1][1], option);
                        openfile(argv[i], option, argv[4], flag, atoi(argv[2]), 0);
                        system("Color 0C");
                        printf("\n");
                        i++;
                    }
                }
            }
            if (argc == 5 && strcmp(argv[3], "-H") != 0 && (strcmp(argv[3], "-h") != 0)){ //format : ./anjaligrep -m NUMBER pattern filename
                flag = 0;
                option = types(argv[1][1], option);
                i = 4;
                openfile(argv[i], option, argv[3], flag, atoi(argv[2]), 0);
            }
            else if((strcmp(argv[3], "-H") != 0) && argc > 5 && (strcmp(argv[3], "-h") != 0) &&(strcmp(argv[3], "-n") != 0) ){
                flag = 1;  //format : ./anjaligrep -m NUMBER pattern file1 file2 file3.....
                i = 4;
                while(i < argc){ //for multiple files
                    option = types(argv[1][1], option);
                    openfile(argv[i], option, argv[3], flag, atoi(argv[2]),0);
                    system("Color 0D");
                    printf("\n");
                    i++;
                }
            }
            else if((strcmp(argv[3], "-n") == 0) && (strcmp(argv[4], "-h") != 0) && (strcmp(argv[4], "-H") != 0)){
                int option1 = LINENUMBER;  //format : ./anjaligrep -m NUMBER -n pattern filename
                if (argc == 6){
                    option = types(argv[1][1], option);
                    openfile(argv[5], option,argv[4],0,atoi(argv[2]),option1);
                    system("Color 0D");
                }
                else{
                    i = 5;
                    while(i < argc){ //for multiple files
                        option = types(argv[1][1], option);
                        openfile(argv[i], option, argv[4], 1, atoi(argv[2]), option1);
                        system("Color 0E");
                        printf("\n");
                        i++;
                    }
                }
            }
            else if((strcmp(argv[3], "-n") == 0) && (strcmp(argv[4], "-h") == 0)){
                int option1 = LINENUMBER; //format : ./anjaligrep -m NUMBER -n -h pattern filename
                if (argc == 7){
                    option = types(argv[1][1], option);
                    openfile(argv[6], option, argv[5], 0, atoi(argv[2]), option1);
                    system("Color 0E");
                }
                else{
                    i = 6;
                    while(i < argc){ //multiple files
                        option = types(argv[1][1],option);
                        openfile(argv[i], option, argv[5], 0, atoi(argv[2]), option1);
                        system("Color 0F");
                        printf("\n");
                        i++;
                    }
                }
            }
            else if((strcmp(argv[3], "-n") == 0) && (strcmp(argv[4], "-H") == 0)){
                int option1 = LINENUMBER; //format : ./anjaligrep -m NUMBER -n -H pattern filename
                if (argc == 7){
                    option = types(argv[1][1], option);
                    openfile(argv[6], option, argv[5], 1, atoi(argv[2]), option1);
                }
                else{
                    i = 6;
                    while(i < argc){ //for multiple files
                        option = types(argv[1][1], option);
                        openfile(argv[i], option, argv[5], 1, atoi(argv[2]), option1);
                        system("Color 0F");
                        printf("\n");
                        i++;
                    }
                }
            }
        }
        else if((strcmp(argv[1], "-m") == 0) || (strcmp(argv[1],"-e") == 0) || (strcmp(argv[2], "-e") == 0)){
            if((strcmp(argv[1], "-e") == 0)){ //format : ./anjaligrep -e pattern filename
                if (argc == 4){
                    flag = 0;
                    i = 3;
                    option = EXP;
                    openfile(argv[i], option, argv[2], flag, 0, 0);
                    system("color 0B");
                }
                if(argc > 4){
                    int j;
                    flag  = 1;
                    option = EXP;
                    i = 3;
                    j = 2;
                    while(i < argc + 1){ //multiple patterns // ./anjaligrep -e pattern filename -e pattern2 filename2...
                        openfile(argv[i], option, argv[j], flag, 0, 0);
                        system("Color 02");
                        printf("\n");
                        i = i + 3;
                        j = j + 3;
                    }
                }
            }
            else if (strcmp(argv[2], "-e") == 0){
                if (argc == 5){ //option i.e argv[1] can be i, w, v, c
                    flag = 0;
                    i = 4;
                    option = types(argv[1][1], option);
                    openfile(argv[i], option, argv[3], flag, 0, 0);
                    system("Color 02");
                }
                if(argc > 5){ // ./anjaligrep -option -e pattern1 file1 -option -e pattern2 file2....
                    int j, k = 1; //option
                    flag = 1;
                    i = 4; //filename
                    j = 3; //pattern
                    while(i < argc){
                        option = types(argv[k][1], option);
//                        if(k > 1 && option == MAXIMUM)
//                            openfile(argv[i], option, argv[j], flag, argv[k][2], 0);
//                        else{
                        openfile(argv[i], option, argv[j], flag, 0, 0);
                        system("Color 02");
                        printf("\n");
                        //}
                        i = i + 4;
                        j = j + 4;
                        k = k + 4;
                    }
                }
            }
            else if(strcmp(argv[1], "-m") == 0 && (strcmp( argv[3], "-n") != 0)){
                if(argc == 6){ // ./anjaligrep -m NUMBER -e pattern filename
                    option = MAXIMUM;
                    openfile(argv[5], option, argv[4], flag, atoi(argv[2]), 0);
                    system("color 0B");
                }
                if(argc > 6){ // ./anjaligrep -m NUMBER -e pattern filename -option -e pattern filename
                    int j, k = 6;
                    flag = 1;
                    i = 5; //filename
                    j = 4; //pattern
                    option = MAXIMUM;
                    openfile(argv[5], option, argv[4], flag, atoi(argv[2]), 0);
                    while(i < argc - 1){
                        i = i + 4;
                        j = j + 4;
                        printf("\n");
                        option = types(argv[k][1], option);
                        openfile(argv[i], option, argv[j], flag, 0, 0);
                        system("Color 02");
                        k = k + 4;
                    }
                }
            }
        }
        else if(argv[2][0] == '-' && argv[2][1] == 'H'){
            int option1 = 0;
            if(argc == 5){
                if(strcmp(argv[1], "-n") == 0){ // ./anjaligrep -n -H pattern filename
                    option1 = LINENUMBER;
                    option = EXP;
                }
                else{ // c or i or v or w
                    option = types(argv[1][1], option); // ./anjaligrep -option -H pattern filename
                }
                openfile(argv[4], option, argv[3], 1, 0, option1);
                system("Color 04");
            }
            if(argc > 5){ // ./anjaligrep -option -H pattern file1 file2 file3...........
                flag = 1; //for multiple files
                i = 4;
                if(strcmp(argv[1], "-n") == 0){
                    option1 = LINENUMBER;
                    option = EXP;
                }
                else{ // c or i or v or w
                    option = types(argv[1][1], option);
                }
                while(i < argc){
                    openfile(argv[i], option, argv[3], flag, 0, option1);
                    system("Color 04");
                    printf("\n");
                    i++;
                }
            }
        }
        else if(argv[2][0] == '-' && argv[2][1] == 'h'){
            int option1 = 0;  // ./anjaligrep -n -h pattern filename
            if(argc == 5){
                if(strcmp(argv[1], "-n") == 0){
                    option1 = LINENUMBER;
                    option = EXP;
                }
                else{
                    option = types(argv[1][1], option);
                }
                openfile(argv[4], option, argv[3], 0, 0, option1);
                system("Color 04");
            }
            if(argc > 5){ //for multiple files
                flag = 0;
                i = 4;
                if(strcmp(argv[1],"-n") == 0){
                    option1 = LINENUMBER;
                    option = EXP;
                }
                else{
                    option = types(argv[1][1], option);
                }
                while(i<argc){
                    openfile(argv[i], option, argv[3], flag, 0, option1);
                    system("Color 04");
                    printf("\n");
                    i++;
                }
            }
        }
        else if(((strcmp(argv[1],"-n") == 0) && argv[2][0] == '-') || ((strcmp(argv[2], "-n") == 0) && argv[1][0] == '-')){
            int option1 = LINENUMBER;
            if(strcmp(argv[2], "-h") == 0){ // ./anjaligrep -n -h pattern filename
                if(argc == 5){
                    if(strcmp(argv[1],"-n") == 0){
                        openfile(argv[5], EXP, argv[3], 0, 0, option1);
                    }
                }
                if(argc > 5){
                    i = 4;
                    while(i < argc){
                        if(strcmp(argv[1], "-n") == 0){
                            openfile(argv[i], EXP, argv[3], 0, 0, option1);
                            system("Color 04");
                            printf("\n");
                        }
                        i++;
                    }
                }
            }
            if(strcmp(argv[3], "-h") == 0){
                if(argc == 6){
                    if(strcmp(argv[1], "-n") == 0){  // ./anjaligrep -n -option -h pattern filename
                        option = types(argv[2][1], option);
                        openfile(argv[5], option , argv[4], 0, 0, option1);
                        system("Color 04");
                    }
                    else if(strcmp(argv[2],"-n") == 0){  // ./anjaligrep -option -n -h pattern filename
                        option = types(argv[1][1], option);
                        openfile(argv[5], option, argv[4], 0, 0, option1);
                        system("Color 04");
                    }
                }
                if(argc > 6){ //multiple files
                    i = 5;
                    while(i < argc){
                        if(strcmp(argv[1], "-n") == 0){
                            option = types(argv[2][1], option);
                            openfile(argv[i], option, argv[4], 0, 0, option1);
                            system("Color 08");
                            printf("\n");
                        }
                        else if(strcmp(argv[2],"-n") == 0){
                            option = types(argv[1][1], option);
                            openfile(argv[i], option, argv[4], 0, 0, option1);
                            system("Color 09");
                            printf("\n");
                        }
                        i++;
                    }
                }
            }
            else if(strcmp(argv[3], "-H") == 0){
                if(argc == 6){
                    if(strcmp(argv[1], "-n") == 0){ // ./anjaligrep -n -option -H pattern filename
                        option = types(argv[2][1], option);
                        openfile(argv[5], option, argv[4], 1, 0, option1);
                         system("Color 09");
                    }
                    else if(strcmp(argv[2], "-n") == 0){ // ./anjaligrep -option -n -H pattern filename
                        option = types(argv[1][1], option);
                        openfile(argv[5], option, argv[4], 1, 0, option1);
                        system("Color 09");
                    }
                }
                else if(argc > 6){ //for multiple files
                    i = 5;
                    while(i<argc){
                        if(strcmp(argv[1], "-n") == 0){
                            option = types(argv[2][1], option);
                            openfile(argv[i], option, argv[4], 1, 0, option1);
                            system("Color 0A");
                            printf("\n");
                        }
                        else if(strcmp(argv[2], "-n") == 0){
                            option = types(argv[1][1], option);
                            openfile(argv[i], option, argv[4], 1, 0, option1);
                            system("Color 0A");
                            printf("\n");
                        }
                        i++;
                    }
                }
            }
            if (argc == 5){
                flag = 0;
                if(strcmp(argv[1], "-n") == 0){ // ./anjaligrep -n -option pattern filename
                    option = types(argv[2][1], option);
                    openfile(argv[4], option, argv[3], 0, 0, option1);
                    system("Color 0A");
                }
                else if(strcmp(argv[2], "-n") == 0){// ./anjaligrep -option -n pattern filename
                    option = types(argv[1][1], option);
                    openfile(argv[4], option, argv[3], 0, 0, option1);
                    system("Color 0A");
                }
            }
            if(argc > 5 && (strcmp(argv[3], "-h") != 0) && (strcmp(argv[3],"-H") != 0)){
                flag = 1;
                i = 4;
                while(i < argc){ //for multiple files
                    if(strcmp(argv[1],"-n") == 0){ // ./anjaligrep -n -option pattern file1 file2 file3...
                        option = types(argv[2][1], option);
                    }
                    else if(strcmp(argv[2],"-n") == 0){ // ./anjaligrep -option -n pattern file1 file2....
                        option = types(argv[1][1], option);
                    }
                    openfile(argv[i], option,argv[3],flag,0, option1);
                    printf("\n");
                    i++;
                }
            }
        }
		else if(strcmp(argv[1],"-n") == 0 && (strcmp(argv[3],"-h") != 0)){
			int option1 = LINENUMBER;
			if (argc == 4){ // ./anjaligrep -n pattern filename
				flag = 0;
				i = 3;
				option = EXP;
				openfile(argv[i], option , argv[2], 0, 0, option1);
				system("Color 01");
			}
			if (argc > 4){ //for multiple files
				flag = 1;
				i = 3;
				option = EXP;
				while(i < argc){
					openfile(argv[i], option, argv[2], flag, 0, option1);
					system("Color 0A");
					printf("\n");
					i++;
				}
			}
		}
        else if((strcmp(argv[1],"-ci") == 0) || (strcmp(argv[1],"-cv") == 0) || (strcmp(argv[1], "-cw") == 0)){
            int option1;
            if(argv[1][2] == 'i'){ //ci
				option1 = COUNTCASEINSENSITIVE;
				option = CASEINSENSITIVE;
			}
            else if( argv[1][2] == 'v'){ //cv
				option1 = COUNTINVERTMATCH;
				option = INVERTMATCH;
			}
            else{ //cw
				option1 = COUNTWHOLEWORD;
				option = WHOLEWORD;
            }
            if (argc == 4){
                openfile(argv[3], option, argv[2], 0, num, option1);
                system("Color 02");
            }
            else if(argc > 4){ //for multiple files
                i = 3;
                while(i < argc){
                    openfile(argv[i], option, argv[2], 1, num, option1);
                    printf("\n");
                    system("Color 09");
                    i++;
                }
            }

        }
        else if(strcmp(argv[1],"-vi") == 0 || strcmp(argv[1],"-cvi") == 0){
            option = INVERTMATCH;
            int option1 = CASEINSENSITIVE;
            if(argv[1][1] == 'c'){
				num = 1;
			}
            if (argc == 4){
                openfile(argv[3], option, argv[2],0,num, option1);
                system("Color 01");
            }
            else if(argc > 4){ //for multiple files
                flag = 1;
                i = 3;
                while(i < argc){
                    openfile(argv[i], option, argv[2], flag, num, option1);
                    printf("\n");
                    system("Color 09");
                    i++;
                }
            }

        }
        else if(strcmp(argv[1],"-cvw") == 0){
            option = INVERTMATCH;
            int option1 = WHOLEWORD;
            if(argv[1][1] == 'c'){
				num = 1;
			}
            if (argc == 4){
                openfile(argv[3], option, argv[2], 0, num, option1);
                system("Color 09");
            }
            else if(argc > 4){
                flag = 1;
                i = 3;
                while(i < argc){ //for multiple files
                    openfile(argv[i], option, argv[2], flag, num, option1);
                    printf("\n");
                    system("Color 09");
                    i++;
                }
            }
        }
        else if(strcmp(argv[1],"-iw") == 0){
            option = CASEINSENSITIVEWHOLE;
            if (argc == 4){ // format ./anjaligrep -iw pattern <filename>
                openfile(argv[3], option, argv[2], 0, 0, 0);
                system("Color 0B");
            }
            else if(argc > 4){
                i = 3;
                while(i < argc){ //when multiple files
                    openfile(argv[i], option, argv[2], 1, 0, 0);
                    printf("\n");
                    system("Color 09");
                    i++;
                }
            }

        }
        else if((strcmp(argv[1],"-r") == 0) || (strcmp(argv[1],"-l") == 0)){
            if(argv[2][0] == '-'){ //when there is other flag along with -r or -l flag
                option = types(argv[2][1], option);
                filename(option, argv[3], ".");
                system("Color 0D");
     		}
            else{
                option = types(argv[1][1], option); //when only -l or -r flag is there format : ./proj -l pattern
                filename(option, argv[2], ".");
                system("Color 01");
            }
        }
    }
}



