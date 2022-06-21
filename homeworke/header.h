#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//isbn이 같으면 도서명이 같아야한다.


typedef struct {
    char sn[20];
    char pw[20];
    char name[20];
    char add[20];
    char pn[20];
    char YorN;
} CLIENT;

typedef struct {
    char book_name[20];
    char book_publisher[20];
    char book_author[20];
    char ISBN[14];
    char collection[20];
    int book_number;
    char YorN;
} BOOK;

typedef struct {
    char borrow_sn[20];
    int borrow_book_number;
    char borrow_book_name[20];
    //대여일자
    //반납일자
} BORROW;


int Print_front(void);

CLIENT* RegClient(void);


void Login(void);

int admin(void);

int person(int);

int check_double(char *);

//fun_cli_service
void Print_cli_service(char *); // 파라미터로 학번을 들고다님.

void Print_borrow_book(char *);

void edit_info(char *);


//fun_adm_service
void Print_adm_service(void);

BOOK* add_book(void);

int book_check_double(char *);

void rearrange(BOOK *);

void Print_bok_list(void);

int is_number(char *);

void del_book(void);

void rental(void);

void Print_cli(void);

void return_book(void);

void serch_book(void);


#endif /* header_h */
