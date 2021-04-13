
typedef struct node{
    char a[2];
    struct node *prev;
    struct node *next;
}node;

typedef struct line{
    node *head;
    node *tail;
}line;

void init_line(line *l);//initializing

void append(line *l, char character);//for adding a node

void display(line l);//to display the line

int match_pattern(line l, char *pattern);// -c -m -r -l -n -h -H -q
//checking for pattern in line

//-o only match patterns simple grep , pattern maybe a substring or whole word

int caseinsensitive_matching(line l, char *pattern); //to make all letters to lowercase to match irrespective of case
//-i, --ignore-case

int match_whole_string(line l, char *pattern); // Select only those lines containing matches that form whole words
// -w, --word-regexp
//Select only those lines containing matches that form whole words.

void destroy_line(line *l); //to delete a line

int non_matching_pattern(line l, char *pattern); //to select non-matching lines
//-v --invert-match

int caseinsensitive_whole(line l, char *pattern);
