#include "header.h"

enum mod {book_add=1, book_del, book_rental, book_return, book_serch, member_list, logout, program_end};

extern CLIENT **cli;
extern int size;

void Print_adm_service(void)
{
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
