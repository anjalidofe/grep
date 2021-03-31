#include <stdio.h>
#include <stdlib.h>
#include "ll.h"
#include <string.h>
#include "header.h"
#include <windows.h>

int main(int argc, char *argv[]){

    int static option = 0;
    int static option1 = 0;

    if(argc < 3 && strcmp(argv[1], "--help") != 0 && strcmp(argv[1], "--version") != 0 && strcmp(argv[1], "-V") != 0){
        printf("  Usage :  grep [OPTION...] PATTERNS [FILE...] \nUse '--help' for more information.");
        exit(0);
    }
    else if(strcmp(argv[1], "--help") == 0 && argv[2] == NULL){
        usage();
        system("Color 03");
        exit(0);
    }
    else if((strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0) && argv[2] == NULL){
        printf("  Version of GREP is DSA project version 2021\n");
        system("Color 05");
        exit(0);
    }
    else{
        if(argc > 3 && argc < 5){
            if((strcmp(argv[1], "-i") == 0)){ //case insensitive matching
                option = types(argv[1][1], option);
                system("Color 06");
                openfile(argv[3], option, argv[2], 0);
            }
            else if((strcmp(argv[1], "-w") == 0)){ //whole word matching
                option = types(argv[1][1], option);
                system("Color 05");
                openfile(argv[3], option, argv[2], 0);
            }
            else if((strcmp(argv[1], "-v") == 0)){ //unmatching
                option = types(argv[1][1], option);
                system("Color 0A");
                openfile(argv[3], option, argv[2], 0);
            }
            else if((strcmp(argv[1], "-o") == 0)){ //only matching
                option = types(argv[1][1], option);
                system("Color 09");
                openfile(argv[3], option, argv[2], 0);
            }
        }
        else if(argc == 5) {
            if((strcmp(argv[1], "-v") == 0) && (strcmp(argv[2], "-i") == 0)){
                option = types(argv[1][1], option);
                option1 = types(argv[2][1], option1);
                openfile(argv[4], option, argv[3], option1);
            }
            else if((strcmp(argv[1], "-v") == 0) && (strcmp(argv[2], "-w") == 0)){
                option = types(argv[1][1], option);
                option1 = types(argv[2][1], option1);
                openfile(argv[4], option, argv[3], option1);
            }
        }



    }
}
//int main()
//{
//    line l;
//    init_line(&l);
//    append(&l, 'H');
//    append(&l, 'e');
//    append(&l, 'l');
//    append(&l, 'l');
//    append(&l, 'o');
//    append(&l, ' ');
//    append(&l, 'W');
//    append(&l, 'o');
//    append(&l, 'r');
//    append(&l, 'l');
//    append(&l, 'd');
//    //append(&l, ' ');
//    append(&l, '.');
//
//    display(l);
//    printf("\n");
//    for(int j = 0; j <3; j++){
//    char check[50];
//    printf("Enter pattern you want to check for : ");
//    gets(check);
//    //int i = match_pattern(l, check);
//    int i = match_whole_string(l, check);
//    if(i)
//        printf("Pattern matched\n");
//    else
//        printf("Pattern not matched\n");
//    }
//    destroy_line(&l);
//    return 0;
//}
