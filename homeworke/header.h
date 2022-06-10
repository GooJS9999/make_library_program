#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sn[20];
    char pw[20];
    char name[20];
    char add[20];
    char pn[20];
} CLIENT;

typedef struct {
    char book_name[20];
    char book_publisher[20];
    char book_author[20];
    char ISBN[20];
    char collection[20];
    int book_number;
} BOOK;


int Print_front(void);

CLIENT* RegClient(void);
void print_cli(int);


void Login(void);

int admin(void);

int person(int);

int check_double(char *);

//fun_cli_service
void Print_cli_service(void);



//fun_adm_service
void Print_adm_service(void);

BOOK* add_book(void);

int book_check_double(char *);

#endif /* header_h */
