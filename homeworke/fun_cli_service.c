#include "header.h"

enum mod {book_ser=1, my_book, Edit_info,Withdrawal, logout, program_end};

extern CLIENT **cli;
extern int cli_size;

extern int bok_size;
extern BOOK **bok;

extern int brw_size;
extern BORROW **brw;

//학번을 가지고 다님

void Print_cli_service(char *s)
{
    enum mod m;
    
    while(1)
    {
        printf("\n>> 회원 메뉴 <<\n\n");
        printf("1.도서명 검색  2.대여 목록\n");
        printf("3.개인정보수정  4.회원 탈퇴\n");
        printf("5.로그아웃  6.프로그램 종료\n\n");
        printf("번호를 입력하여주세요 :");

        scanf("%d", &m);

        switch(m)
        {
            case book_ser:
                serch_book();
                break;
            case my_book:
                Print_borrow_book(s);
                break;
            case Edit_info:
                edit_info(s);
                break;
            case Withdrawal:
                // 모두 반납한 상태면 회원탈퇴를 한다.
                break;
            case logout:
                return;
                break;
            case program_end:
                exit(0);
                break;
            default:
                //
                break;
        }
    }
    
}

void Print_borrow_book(char *s)
{
    int i;
    int mod = 0;
    
    for(i=0;i<brw_size-1;i++)
    {
        if(strcmp(s, brw[i]->borrow_sn) == 0)
        {
            printf("도서번호 : %d 도서명 : %s\n", brw[i]->borrow_book_number, brw[i]->borrow_book_name); //책이름
        }
        mod = 1;
    }
    
    if(mod == 0)
    {
        printf("대여한 도서가 없습니다.\n");
    }
}

void edit_info(char *s)
{
    int i;
    CLIENT* temp = (CLIENT*)malloc(sizeof(CLIENT));
    
    strcpy(temp->sn, s);
    
    printf("비밀번호 : ");
    scanf("%s", temp->pn);

    printf("이름 : ");
    scanf("%s", temp->name);

    printf("주소 : ");
    scanf("%s", temp->add);

    printf("전화번호 : ");
    scanf("%s", temp->pw);
    
    
    for(i=0;i<cli_size-1;i++)
    {
        if(strcmp(cli[i]->sn,s) == 0)
        {
            cli[i] = temp;
        }
    }
    
    free(temp);
    
}
