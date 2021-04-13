#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

//initializing the line
void init_line(line *l) {

    l->head = NULL;
    l->tail = NULL;
    return;
}

//for adding a node
void append(line *l, char character) {
    node *nn = (node*)malloc(sizeof(node));
    if(!nn)
        return;
    nn->prev = NULL;
    nn->next = NULL;
    nn->a[0] = character;
    nn->a[1] = '\0';
    //when it is the first node
    if(l->head == NULL && l->tail == NULL){
        l->head = nn;
        l->tail = nn;
        return;
    }
    else{
        nn->prev = l->tail;
        l->tail->next = nn;
        l->tail = nn;
        nn->next = NULL;
        return;
    }
    return;
}

void lower_case(char str[]){//to lower the case of string //to be used in caseinsensitive_matching function
    for(int i = 0; i <= strlen(str); i++){
    //ASCII value for A to Z is from 65 to 90 and a to z is from 97 to 122
        if(str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
    }
    return;
}

void display(line l){//to display the line i.e., every letter in the line
	node *ptr;
	ptr = l.head;
	while(ptr->next){
		printf("%c", ptr->a[0]);
		ptr = ptr->next;
	}
	if(ptr == l.tail){
		printf("%c \n", ptr->a[0]);
	}
	return;
}

int match_pattern(line l, char *pattern){//checking for pattern in line //searches for substrings
	char string[70];
	strcpy(string, pattern);
	//if no line return
	if (l.head == NULL){
		return 0;
	}
	line l1;
	//initialize new line so as to avoid making any changes in original line
	init_line(&l1);
	node *p;
	p = l.head;
	//copying data of line l into line l1
	while(p->next){
		append(&l1, p->a[0]);
		p = p->next;
	}
	if(p == l.tail){
		append(&l1, p->a[0]);
	}
	node *q;
	int i = 0;
	q = l1.head;
	//checking for matching patterns
	while((q->next)  && (string[i] != '\0')){
		if(string[i] == q->a[0]){
				q = q->next; //if one character matches of line and string increment i and also point to next character of line
				i++;

		}
		else{ //if the line character does not match pattern
            if(i != 0) //reset i to 0 as we need to check from beginning of pattern
                i = 0;
            else
                q = q->next; //incase i = 0 when the first character itself did not match just point to next character of line
		}
	}//when it comes out of while loop and it is last character of line
    if(q == l1.tail){ //if last letter of line also matches
        if(string[i] == q->a[0])
            i++;
	}
    if(string[i] == '\0') //only if the entire pattern has matched then it would reach '\0' character
        return 1;
    else //incase pattern has not matched
        return 0;
}

//-w Select only those lines containing matches that form whole words
int match_whole_string(line l, char *pattern){
	char string[70];
	strcpy(string, pattern);
	line l1;
	init_line(&l1);
	//if no line return
	if (l.head == NULL){
		return 0;
	}
	node *p;
	p = l.head;
	//copying data of line l into line l1
	while(p->next){
		append(&l1, p->a[0]);
		p = p->next;
	}
	if(p == l.tail){
		append(&l1, p->a[0]);
	}
	node *q;
	int i = 0;
	q = l1.head;
	//checking for matching of whole string
	while((q->next)  && (string[i]!='\0')){
		if(string[i] == q->a[0] ){
            q = q->next;
            i++;
        }
        else{//directly set i to 0 again so begins search from beginning of new word in line
            if(i != 0){
                i = 0;
            }
            else{
                q = q->next;
            }
        }
    }
	if(q == l1.tail){
		if(string[i] == q->a[0]){
            i++;
		}
	}
	//if the string ends with character other than letter still consider it as complete string if all letters/numbers match
    if((string[i] == '\0') && ((q->a[0] == ' ') || (q->a[0] == '(') || (q->a[0] == ')') || (q->a[0] == '[') ||
        (q->a[0] == ']')|| (q->a[0] == '/')|| (q->a[0] == '<')||(q->a[0] == '.')||(q->a[0] == '>')||
        (q->a[0] == '!')|| (q->a[0] == '-')||(q->a[0] == '*')||(q->a[0] == ',')||(q->a[0] == '"')||
        (q->a[0] == ';')||(q->a[0] == ':')|| q->a[0] == '\0')){
        return 1;
    }
    else
        return 0;
}

//to make all letters to lowercase to match irrespective of case
int caseinsensitive_matching(line l, char *pattern){
    char string[80];
	strcpy(string, pattern);

	line l1;
	init_line(&l1);

	node *p;
	if (l.head == NULL){
		return 0;
	}
	p = l.head;
	while(p->next){
		append(&l1, p->a[0]);
		p = p->next;
	}
	if(p == l.tail){
		append(&l1, p->a[0]);
	}
	lower_case(string);
	node *q;
	q = l1.head;
	while(q->next){
		lower_case(q->a);
		q = q->next;
	}
	if(q->next == NULL){
		lower_case(q->a);
	}
	int i=0;
	q = l1.head;
	while((q->next) && (string[i] != '\0')){
		if(string[i] == q->a[0]){
            q = q->next;
            i++;
        }
        else{
            if(i!=0){
                i=0;
            }
            else{
                q = q->next;
            }
        }
    }
	if(q == l1.tail){
		if(string[i] == q->a[0])
            i++;
	}
    if(string[i]=='\0'){
        return 1;
    }
    else{
        return 0;
    }
}

//to destroy a line
void destroy_line(line *l){
    node *p;

    if(l->head == NULL && l->tail == NULL)
        return;

    else{

        while(l->head != l->tail){
            p = l->tail;
            l->tail = p->prev;
            l->tail->next = NULL;
            p->prev = NULL;
            free(p);
        }
        p = l->tail;
        l->tail = NULL;
        l->head = NULL;
        free(p);
    }
}

int non_matching_pattern(line l, char *pattern) {
    //same as match pattern only the return values interchanged to unmatch
    char string[70];
    int i = 0;
    strcpy(string, pattern);//copying pattern into string
    line l1;
    init_line(&l1);
    node *p;
    if (l.head == NULL) { //return 0 if line is null
        return 0;
    }
    p = l.head;
    while(p->next) { //making node p point to line and copying into l1
        append(&l1, p->a[0]);
        p = p->next;
    }
    if(p == l.tail) {
        append(&l1, p->a[0]);
    }
    node *q;
    q = l1.head;
    while((q->next) && (string[i] != '\0')) {
        if(string[i] == q->a[0]) {
            q = q->next;
            i++;
        }

        else {
            if(i != 0) {
                i = 0;
            }
            else {
                q = q->next;
            }
        }
    }
    if(q == l1.tail) {
        if(string[i] == q->a[0])
            i++;
    }
    if(string[i] == '\0')
        return 0;
    else
        return 1;
}

int caseinsensitive_whole(line l, char *pattern){ //for matching case insensitive whole word string patterns
    char string[70];
	strcpy(string, pattern);
	line l1;
	init_line(&l1);
	node *p;
	if (l.head == NULL){
		return 0;
	}
	p = l.head;
	while(p->next){
		append(&l1, p->a[0]);
		p = p->next;
	}
	if(p == l.tail){
		append(&l1, p->a[0]);
	}
	lower_case(string);
	node *q;
	q = l1.head;
	while(q->next){
		lower_case(q->a);
		q = q->next;
	}
	if(q->next == NULL){
		lower_case(q->a);
	}
	int i = 0;
	q = l1.head;
	while((q->next)  && (string[i]!='\0')){
		if(string[i] == q->a[0] ){
				q = q->next;
				i++;
				continue;
        }
        else{
            if(i != 0){
                i = 0;
            }
            else{
                q = q->next;
            }
        }
    }
	if(q == l1.tail){
		if(string[i] == q->a[0])
				i++;

	}
    if((string[i] == '\0') && ((q->a[0] == ' ') || (q->a[0] == '(') || (q->a[0] == ')')
                || (q->a[0] == '[') || (q->a[0] == ']')|| (q->a[0] == '/')||
                (q->a[0] == '<')||(q->a[0] == '.')||(q->a[0] == '>')||
                (q->a[0] == '!')|| (q->a[0] == '-')||(q->a[0] == '*')||(q->a[0] == ',')
                ||(q->a[0] == '"')||(q->a[0] == ';')||(q->a[0] == ':')|| q->a[0] == '\0')){
        return 1;
    }
    else{
        return 0;
    }
}
