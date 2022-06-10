#include "header.h"

int Print_front(void)
{
    int input;
    
    
    
    printf(">> 도서관 서비스 <<\n\n");
    printf("1.회원가입   2.로그인   3.프로그램 종료\n\n");
    printf("번호를 선택하세요 : ");
    
    scanf("%d", &input);
    
    return  input;
}

