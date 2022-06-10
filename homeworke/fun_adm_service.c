#include "header.h"

enum mod {book_add=1, book_del, book_rental, book_return, book_serch, member_list, logout, program_end};

extern CLIENT **cli;
extern int cli_size;

extern int bok_size;
extern BOOK **bok;


void Print_adm_service(void)
{
    BOOK *temp = (BOOK*)malloc(sizeof(temp));

    enum mod m;
    
    printf("\n>> 관리자 메뉴 <<\n\n");
    printf("1.도서 등록  2.도서 삭제\n");
    printf("3.도서 대여  4.도서 반납\n");
    printf("5.도서 검색  6.회원 목록\n");
    printf("7.로그아웃   8.프로그램 종료\n\n");
    printf("번호를 입력하여주세요 :");
    
    scanf("%d", &m);
    
    switch(m)
    {
        case book_add:
            
            if(bok_size == 1)
            {
                bok = (BOOK**)malloc(sizeof(BOOK*));
            }
            else
            {
                bok = (BOOK**)realloc(bok, bok_size * sizeof(BOOK*));
            }
            bok[bok_size-1] = (BOOK*)malloc(sizeof(BOOK));
            temp = add_book();
             if(book_check_double(temp->book_name))
             {
               // 도서번호 순서 재정렬.
             }
             else
             {
                 temp->book_number = 1000000+(bok_size-1);
             }
             
            bok[bok_size-1] = temp;
            bok_size++;
            
            
            break;
        case book_del:
            break;
        case book_rental:
            break;
        case book_return:
            break;
        case book_serch:
            break;
        case member_list:
            break;
        case logout:
            break;
        case program_end:
            break;
        default:
            break;
    }
    
    
}

BOOK* add_book(void)
{
    BOOK *temp = (BOOK*)malloc(sizeof(temp));
    
    printf("도서명 : ");
    scanf("%s", temp->book_name);

    printf("출판사 : ");
    scanf("%s", temp->book_publisher);

    printf("저자명 : ");
    scanf("%s", temp->book_author);

    printf("ISBM : ");
    scanf("%s", temp->ISBN);
    
    printf("소장처 : ");
    scanf("%s", temp->collection);
    
    
    return temp;
}

int book_check_double(char *s)
{
    int i;
    
    for(i=0;i<bok_size-1;i++)
    {
        if(strcmp(bok[i]->book_name,s) == 0)
        {
            return 1;
        }
    }
    return 0;
}



/*
 char book_name[20];
 char book_publisher[20];
 char book_author[20];
 char ISBN[20];
 char collection[20];
 int book_number[7];
 */
