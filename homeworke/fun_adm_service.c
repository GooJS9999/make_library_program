#include "header.h"

enum mod {book_add=1, book_del, book_rental, book_return, book_serch, member_list, logout, program_end};
enum mod_member_list {name_serch = 1, student_number_serch, every_serch, back};



extern CLIENT **cli;
extern int cli_size;

extern int bok_size;
extern BOOK **bok;

extern int brw_size;
extern BORROW **brw;





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
                rental();
                break;
            case book_return:
                return_book();
                break;
            case book_serch:
                serch_book();
      //          Print_bok_list();
                break;
            case member_list:
                Print_cli();
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

// 1.도서 등록
BOOK* add_book(void)
{
    int i;
    int mod = 0;
    
    BOOK *temp = (BOOK*)malloc(sizeof(temp));
    
    printf("도서명 : ");
    scanf("%s", temp->book_name);

    printf("출판사 : ");
    scanf("%s", temp->book_publisher);

    printf("저자명 : ");
    scanf("%s", temp->book_author);
    
    
    //isbn이 같으면 이름도 같아야 한다.
    while(1)
    {
    printf("ISBM : ");
    scanf("%s", temp->ISBN);
        
        mod = 0;
        if(strlen(temp->ISBN) == 13 && is_number(temp->ISBN))
        {
            for(i=0;i<bok_size-1;i++)
            {
                //중복이 있음.
                if(strcmp(temp->ISBN, bok[i]->ISBN) == 0)
                {
                    //이름이 같나?
                    if(strcmp(bok[i]->book_name, temp->book_name) != 0)
                    {
                        printf("같은 ISBN코드의 책과 이름이 다릅니다.\n");
                        mod = 1;
                    }

                }
            }
        }
        else
        {
            printf("13개의 정수를 입력하세요.");
            continue;
        }
        
        if(mod == 0)break;
        
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
        if(strcmp(bok[i]->ISBN, s->ISBN) == 0)
        {
            while(strcmp(bok[i]->ISBN, s->ISBN) == 0)
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
            if(strcmp(bok[i]->book_name, serch) == 0 || strcmp(bok[i]->ISBN, serch) == 0)
            {
                if(del_num == bok[i]->book_number && bok[i]->YorN == 'Y')
                {
                    //도서 삭제가 이상함..
                    for(j=i;j<bok_size-2;j++)
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

// 3.도서 대여
void rental(void)
{
    int i;
    int input;
    
    int temp_cli = 0;
    
    int del_num;
    int mod =0, mod_YorN = 0, rent_mod = 0, bok_mod = 0;

    char rental_sn[20];

    char serch[20];
    
    printf("\n>>도서 대여<<.\n\n");
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
                    
                    printf("도서명:%4s 출판사:%4s\n책저자:%3s ISBN:%13s\n저장소:%5s 도서번호:%4d\n", bok[i]->book_name, bok[i]->book_publisher, bok[i]->book_author, bok[i]->ISBN, bok[i]->collection, bok[i]->book_number);
                    
                    printf("\n대여 가능 여부 : %c\n\n", bok[i]->YorN);
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
                    
                    printf("\n대여 가능 여부 : %c\n\n", bok[i]->YorN);
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
    
    //-------------------------------------------------------------
    
    if(mod == 1 && mod_YorN == 1)
    {
        printf("학번 입력 : ");
        scanf("%s", rental_sn);
        
        for(i=0;i<cli_size-1;i++)
        {
            if(strcmp(cli[i]->sn, rental_sn) == 0)
            {
                rent_mod = 1; //학생 있음
                temp_cli = i;
            }
        }
        
        
        
        if(rent_mod == 1)
        {
            printf("도서 번호 입력 : ");
            scanf("%d", &del_num);
            for(i=0;i<bok_size-1;i++)
            {
                if(del_num == bok[i]->book_number )
                {
                    
                    if(brw_size == 1)
                    {
                        brw = (BORROW**)malloc(sizeof(BORROW*));
                    }
                    else
                    {
                        brw = (BORROW**)realloc(brw, brw_size * sizeof(BORROW*));
                    }
                    
                    brw[brw_size-1] = (BORROW*)malloc(sizeof(BORROW));
                    strcpy(brw[brw_size-1]->borrow_sn, cli[temp_cli]->sn);
                    brw[brw_size-1]->borrow_book_number = bok[i]->book_number;
                    strcpy(brw[brw_size-1]->borrow_book_name,bok[i]->book_name);

                    //반납일자 대여일자 표시
                    
                    brw_size++;
                    
                    
                    //대여할때.
                    bok[i]->YorN = 'N';
                    cli[temp_cli]->YorN = 'Y';
                    printf("도서를 대여하였습니다.\n");
                    
                    bok_mod = 1;
                }
                
            }
            
            if(bok_mod == 0)
            {
                printf("해당 도서는 존재하지 않습니다.\n");
            }
            
        }
        else
        {
            printf("해당 학번의 학생은 존재하지 않습니다.\n");
        }
    }
    else
    {
        printf("\n대여 가능한 도서가 없습니다.\n");
    }
    
    
    
}

// 4.도서 반납
void return_book(void)
{
    int i, j;
    int mod = 0;
    int del_mod = 0;
    char serch[20];
    int temp_bn;
    
    
    printf("학번을 입력하세요 : ");
    scanf("%s", serch);
    
    for(i=0;i<cli_size-1;i++)
    {
        if(strcmp(serch, cli[i]->sn) == 0)
        {
            mod = 1;
        }
    }
    
    if(mod == 1)
    {
        for(i=0;i<brw_size-1;i++)
        {
            if(strcmp(serch, brw[i]->borrow_sn) == 0)
            {
                printf("도서번호 : %d 도서명 : %s\n", brw[i]->borrow_book_number, brw[i]->borrow_book_name); // 잘못됌
            }
        }
        
        printf("반납할 도서번호를 입력하세요 : ");
        scanf("%d", &temp_bn);
        
        for(i=0;i<brw_size-1;i++)
        {
            if(temp_bn == brw[i]->borrow_book_number)
            {
                //해당 대여 리스트 삭제
                for(j=i; j<brw_size-2; j++)
                {
                    brw[j] = brw[j+1];
                }
                
                brw_size--;
                
                brw = (BORROW**)realloc(brw,brw_size*sizeof(BORROW*));
                
                del_mod = 1;
            }
        }
        
        for(i=0;i<bok_size-1;i++)
        {
            if(temp_bn == bok[i]->book_number)
            {
                bok[i]->YorN = 'Y';
            }
        }
        
        if(del_mod == 0)
        {
            printf("해당 도서번호가 없습니다.\n");
        }
        
        
    }
    else
    {
        printf("헤당 학번의 학생은 없습니다.\n");
    }
    
}


// 5.도서 검색
void serch_book(void)
{
    int i;
    int input = 0;
    
    char serch[20];
    
    while(1)
    {
        printf("\n\n>>도서 검색<<\n\n");
        printf("1.이름 검색  2.ISBN 검색\n");
        printf("3.전체 검색  4.이전 메뉴\n");
        
        printf("번호를 입력하세요 : ");
        scanf("%d", &input);
        
        switch(input)
        {
            case 1:
                
                printf("도서명을 입력하세요 : ");
                scanf("%s", serch);
                
                for(i=0;i<bok_size-1;i++)
                {
                    if(strcmp(bok[i]->book_name, serch) == 0)
                    {
                        printf("도서명:%4s 출판사:%4s\n책저자:%3s ISBN:%13s\n저장소:%5s 책넘버:%4d\n", bok[i]->book_name, bok[i]->book_publisher, bok[i]->book_author, bok[i]->ISBN, bok[i]->collection, bok[i]->book_number);
                        
                        printf("\n대여 가능 여부 : %c\n\n", bok[i]->YorN);
                    }
                }
                
                if(bok_size == 1)
                {
                    printf("검색할 도서가 없습니다.");
                }
                
                break;
            case 2:
                
                printf("ISBN을 입력하세요 : ");
                scanf("%s", serch);
                
                for(i=0;i<bok_size-1;i++)
                {
                    if(strcmp(bok[i]->ISBN, serch) == 0)
                    {
                        printf("도서명:%4s 출판사:%4s\n책저자:%3s ISBN:%13s\n저장소:%5s 책넘버:%4d\n", bok[i]->book_name, bok[i]->book_publisher, bok[i]->book_author, bok[i]->ISBN, bok[i]->collection, bok[i]->book_number);
                        
                        printf("\n대여 가능 여부 : %c\n\n", bok[i]->YorN);
                    }
                }
                
                if(bok_size == 1)
                {
                    printf("검색할 도서가 없습니다.");
                }
                
                break;
            case 3:
                for(i=0;i<bok_size-1;i++)
                {
                    printf("도서명:%4s 출판사:%4s\n책저자:%3s ISBN:%13s\n저장소:%5s 책넘버:%4d\n", bok[i]->book_name, bok[i]->book_publisher, bok[i]->book_author, bok[i]->ISBN, bok[i]->collection, bok[i]->book_number);
                    
                    printf("\n대여 가능 여부 : %c\n\n", bok[i]->YorN);
                }
                
                if(bok_size == 1)
                {
                    printf("검색할 도서가 없습니다.");
                }
                
                break;
            case 4:
                return;
                break;
            default:
                
                break;
        }
    }

}


// 6.회원 목록
void Print_cli(void)
{
    int i;
    enum mod_member_list m;
    char input[20];
    
    
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
                
                printf("이름을 입력하세요 : ");
                scanf("%s", input);
                
                
                for(i=0;i<cli_size-1;i++)
                {
                    if(strcmp(input, cli[i]->name) == 0)
                    {
                        printf("이름:%s 학번:%s\n주소:%s  전화번호:%s\n비밀번호:%s\n\n", cli[i]->name, cli[i]->sn, cli[i]->add, cli[i]->pn, cli[i]->pw);

                    }
                }
                
                break;
            case student_number_serch:
                
                printf("학번을 입력하세요 : ");
                scanf("%s", input);
                
                
                for(i=0;i<cli_size-1;i++)
                {
                    if(strcmp(input, cli[i]->sn) == 0)
                    {
                        printf("\n학번:%s  이름:%s\n주소:%s  전화번호:%s\n비밀번호:%s", cli[i]->sn ,cli[i]->name, cli[i]->add, cli[i]->pn, cli[i]->pw);
                    }
                }
                
                break;
                
            case every_serch:
                
                for(i=0;i<cli_size-1;i++)
                {
                    printf("이름:%s 학번:%s\n주소:%s  전화번호:%s\n비밀번호:%s", cli[i]->name, cli[i]->sn, cli[i]->add, cli[i]->pn, cli[i]->pw);
                }
                
                if(cli_size == 1)
                {
                    printf("회원이 존재하지 않습니다.\n");
                }
                
                break;
                
            case back:
                return;
                break;

            default:
                printf("잘못입력하였습니다. 다시 입력하세요\n");
                break;
                
        }
    }

}

/*
 char sn[20];
 char pw[20];
 char name[20];
 char add[20];
 char pn[20];
 */



/*
 char book_name[20];
 char book_publisher[20];
 char book_author[20];
 char ISBN[20];
 char collection[20];
 int book_number[7];
 */
