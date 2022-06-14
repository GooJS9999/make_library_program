#include "header.h"

enum mod {book_add=1, book_del, book_rental, book_return, book_serch, member_list, logout, program_end};
enum mod_member_list {name_serch = 1, student_number_serch, every_serch, back};



extern CLIENT **cli;
extern int cli_size;

extern int bok_size;
extern BOOK **bok;


void Print_adm_service(void)
{
    BOOK *temp = (BOOK*)malloc(sizeof(temp));

    enum mod m;
    while(1)
    {
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
                     printf("중복된 책 입니다.\n");
                    rearrange(temp);
                 }
                 else
                 {
                     printf("중복된 책이 아닙니다.\n");
                     temp->book_number = 1000000+(bok_size-1);
                     bok[bok_size-1] = temp;
                 }
                bok_size++;
                break;
            case book_del:
                del_book();
                break;
            case book_rental:
                Print_bok_list();

                break;
            case book_return:
                break;
            case book_serch:
                break;
            case member_list:
                
                print_cli();
                
                
                break;
            case logout:
                return;
                break;
            case program_end:
                exit(0);
                break;
            default:
                printf("잘못 입력하였습니다. 다시 입력하세요.\n");
                break;
        }
    }
    
}

// 도서 등록
BOOK* add_book(void)
{

    BOOK *temp = (BOOK*)malloc(sizeof(temp));
    
    printf("도서명 : ");
    scanf("%s", temp->book_name);

    printf("출판사 : ");
    scanf("%s", temp->book_publisher);

    printf("저자명 : ");
    scanf("%s", temp->book_author);
    
    while(1)
    {
    printf("ISBM : ");
    scanf("%s", temp->ISBN);
        
        if(strlen(temp->ISBN) == 13 && is_number(temp->ISBN))
        {
            break;
        }
        else
        {
            printf("13개의 정수를 입력하세요.");
        }
    }
    
    printf("소장처 : ");
    scanf("%s", temp->collection);
    
    temp->YorN = 'Y';
    
    return temp;
}

// 문자열이 모두 정수인지 체크
int is_number(char *s)
{
    int i;
    for(i=0;i<13;i++)
    {
        if( (s[i] < 0+'0') || (s[i] > 9+'0'))
        {
            return 0;
        }
    }
    
    return 1;
}

// 도서 중복 체크
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

// 도서 정렬
void rearrange(BOOK *s)
{
    int i,j;
    int mod = 0;
    
    for(i=0;i<bok_size-1;i++)
    {
        if(strcmp(bok[i]->book_name, s->book_name) == 0)
        {
            while(strcmp(bok[i]->book_name, s->book_name) == 0)
            {
                i++;
                mod = 1;
            }
        }
        if(mod)break;
    }
    
    for(j=0; j<bok_size-1-i; j++)
    {
        bok[bok_size-1-j] = bok[bok_size-2-j];
    }
    bok[i] = s;
    bok[i]->book_number = bok[i-1]->book_number+1;

    for(j=i+1;j<bok_size;j++)//?
    {
        bok[j]->book_number+=1;
    }
    
}

void Print_bok_list(void)
{
    int i;
    for(i=0;i<bok_size-1;i++)
    {
        printf("도서명:%4s 출판사:%4s 책저자:%3s ISBN:%13s 저장소:%5s 책넘버:%4d\n", bok[i]->book_name, bok[i]->book_publisher, bok[i]->book_author, bok[i]->ISBN, bok[i]->collection, bok[i]->book_number);
        
    }
    
}

// 2.도서 삭제
void del_book(void)
{
    int i, j;
    int input;
    int mod =0, mod_YorN = 0, del_mod = 0;
    char serch[20];
    
    int del_num;
    
    printf("\n>>도서 삭제<<.\n\n");
    printf("1.도서명 검색.    2.ISBN 검색\n");
    printf("번호를 입력하세요 : ");
    scanf("%d", &input);
    
    if(input == 1)
    {
        printf("도서명 입력 : ");
        scanf("%s", serch);
        printf("\n\n");
        
        for(i=0;i<bok_size-1;i++)
        {
            if(strcmp(bok[i]->book_name, serch) == 0)
            {
                
                while(strcmp(bok[i]->book_name, serch) == 0)
                {
                    
                    printf("도서명:%4s 출판사:%4s\n책저자:%3s ISBN:%13s\n저장소:%5s 책넘버:%4d\n", bok[i]->book_name, bok[i]->book_publisher, bok[i]->book_author, bok[i]->ISBN, bok[i]->collection, bok[i]->book_number);
                    
                    printf("\n삭제 가능 여부 : %c\n\n", bok[i]->YorN);
                    mod = 1;
                    
                    if(bok[i]->YorN == 'Y')
                    {
                        mod_YorN = 1;
                    }
                    
                    i++;
                    if(i >= bok_size-1)
                    {
                        break;
                    }
                }
            }
        }
        
        
    }
    else if(input == 2)
    {
        printf("ISBN 입력 : ");
        scanf("%s", serch);
        printf("\n\n");
        
        for(i=0;i<bok_size-1;i++)
        {
            if(strcmp(bok[i]->ISBN, serch) == 0)
            {
                
                while(strcmp(bok[i]->ISBN, serch) == 0)
                {
                    
                    printf("도서명:%4s 출판사:%4s\n책저자:%3s ISBN:%13s\n저장소:%5s 책넘버:%4d\n", bok[i]->book_name, bok[i]->book_publisher, bok[i]->book_author, bok[i]->ISBN, bok[i]->collection, bok[i]->book_number);
                    
                    printf("\n삭제 가능 여부 : %c\n\n", bok[i]->YorN);
                    mod = 1;
                    
                    if(bok[i]->YorN == 'Y')
                    {
                        mod_YorN = 1;
                    }
                    
                    i++;
                    if(i >= bok_size-1)
                    {
                        break;
                    }
                }
            }
        }

    }
    else
    {
        printf("잘못 입력 하였습니다.\n");
    }
    
    if(mod == 1 && mod_YorN == 1)
    {
        printf("도서 번호 입력 : ");
        scanf("%d", &del_num);
        
        
        for(i=0;i<bok_size-1;i++)
        {
            if(strcmp(bok[i]->book_name, serch) == 0)
            {
                if(del_num == bok[i]->book_number && bok[i]->YorN == 'Y')
                {

                    for(j=0;j<bok_size-2;j++)
                    {
                        bok[j] = bok[j+1];
                        bok[j]->book_number -= 1;
                    }
                    
                    bok_size--;
                    bok = (BOOK**)realloc(bok, bok_size * sizeof(BOOK*));
                    
                    
                    del_mod = 1;
                }
                else if(del_num == bok[i]->book_number && bok[i]->YorN == 'N')
                {
                    printf("삭제불가능한 도서 입니다..\n");
                    del_mod = 1;
                }
            }
        }
        
        if(del_mod == 0)
        {
            printf("도서번호를 잘못 입력하였습니다.\n");
        }
        
        
    }
    else
    {
        printf("\n삭제 가능한 도서가 없습니다.\n");
    }
    
    
}

// 6.회원 목록
void print_cli(void)
{
    enum mod_member_list m;
    
    while(1)
    {
        printf("\n\n>>회원 목록<<\n\n");
        printf("1.이름 검색    2.학번 검색\n");
        printf("3.전체 검색    4.이전 메뉴\n");
        
        printf("번호를 입력하세요 : ");
        scanf("%d", &m);
        //ㅁㄴㅇㄹㄴㅁㅇㄹ11111
        switch(m)
        {
            case name_serch:
                break;
            case student_number_serch:
                break;
            case every_serch:
                break;
            case back:
                break;

            default:
                printf("잘못입력하였습니다. 다시 입력하세요\n");
                break;
                
        }
    }
    /*
    int i;
    for(i=0;i<cli_size-1;i++)
    {
        printf("%s %s %s %s %s\n", cli[i]->sn, cli[i]->pn, cli[i]->name, cli[i]->add, cli[i]->pw);
    }
    */
}




/*
 char book_name[20];
 char book_publisher[20];
 char book_author[20];
 char ISBN[20];
 char collection[20];
 int book_number[7];
 */
