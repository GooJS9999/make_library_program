#include "header.h"

extern CLIENT **cli;
extern int cli_size;

CLIENT* RegClient(void)
{
    CLIENT *temp = (CLIENT*)malloc(sizeof(temp));
    
    while(1)
    {
        printf("학번 : ");
        scanf("%s", temp->sn);
        if(check_double(temp->sn))
        {
            break;
        }
        else
        {
            printf("이미 동일한 학번이 있습니다. 다시 입력하세요\n");
        }
    }
    
    printf("비밀번호 : ");
    scanf("%s", temp->pn);

    printf("이름 : ");
    scanf("%s", temp->name);

    printf("주소 : ");
    scanf("%s", temp->add);

    printf("전화번호 : ");
    scanf("%s", temp->pw);
    
    
    return temp;
}

int check_double(char *s)
{
    int i;
    for(i=0;i<cli_size-1;i++)
    {
        if(strcmp(cli[i]->sn, s) == 0)
        {
            return 0;
        }
    }
    
    return 1;
}

void print_cli(int size)
{
    int i;
    for(i=0;i<size-1;i++)
    {
        printf("%s %s %s %s %s\n", cli[i]->sn, cli[i]->pn, cli[i]->name, cli[i]->add, cli[i]->pw);
    }
    
}


void Login(void)
{
    int i;
    char id[20];
    int per = 0;
    
    printf("아이디를 입력하세요 : ");
    scanf("%s", id);
    
    for(i=0;i<cli_size-1;i++)
    {
        if(strcmp(cli[i]->sn,id) == 0)
        {
            per = 1;
            break;
        }
    }
    
    
    if(strcmp(id, "admin") == 0)
    {
        admin();
    }
    else if(per == 1)
    {
        person(i);
    }
    else
    {
        printf("존재하지 않는 아이디 입니다.\n");
        return;
    }
    
}

int admin(void)
{
    char adminPw[20] = "1234";
    char pw[20];
    
    printf("비밀번호를 입력하세요 : ");
    scanf("%s", pw);
    
    if(strcmp(adminPw,pw) == 0)
    {
        Print_adm_service();
//        printf("어드민 로그인 성공\n");
        return 1;
    }
    else
    {
        printf("어드민 로그인 실패\n");
        return 0;
    }
    
    
}

int person(int i)
{
    char pw[20];
    
    printf("비밀번호를 입력하세요 : ");
    scanf("%s", pw);
    
    if(strcmp(cli[i]->pw, pw) == 0)
    {
        Print_cli_service();
//        printf("회원 로그인 성공\n");
        return 1;

    }
    else
    {
        printf("회원 로그인 실패\n");
        return 0;
    }
    
}
