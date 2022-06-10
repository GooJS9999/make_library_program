#include "header.h"

enum mod {book_ser=1, my_book, Edit_info,Withdrawal, logout, program_end};

extern CLIENT **cli;
extern int cli_size;

void Print_cli_service(void)
{
    enum mod m;
    
    printf("\n>> 회원 메뉴 <<\n\n");
    printf("1.도서명 검색  2.대여 목록\n");
    printf("3.개인정보수정  4.회원 탈퇴\n");
    printf("5.로그아웃  6.프로그램 종료\n\n");
    printf("번호를 입력하여주세요 :");
    
    scanf("%d", &m);

    switch(m)
    {
        case book_ser:
            break;
        case my_book:
            break;
        case Edit_info:
            break;
        case Withdrawal:
            break;
        case logout:
            break;
        case program_end:
            break;
        default:
            break;
    }
    
}

