#include "header.h"

enum manu {signup = 1, login = 2, ex = 3};
int cli_size = 1;
CLIENT **cli;

int bok_size = 1;
BOOK **bok;


int brw_size = 1;
BORROW **brw;


int main()
{
    enum manu input;
    CLIENT *temp = (CLIENT*)malloc(sizeof(temp));

    int mod = 0;
    

    
    while(1)
    {
        input = Print_front();
        switch(input)
        {
            case signup:
                
                if(cli_size == 1)
                {
                    cli = (CLIENT**)malloc(sizeof(CLIENT*));
                }
                else
                {
                    cli = (CLIENT**)realloc(cli, cli_size * sizeof(CLIENT*));
                }
                cli[cli_size-1] = (CLIENT*)malloc(sizeof(CLIENT));
                temp = RegClient();
                cli[cli_size-1] = temp;
                cli_size++;
                
 //               print_cli(size);
                
                break;
                
            case login:
                Login();
                
                
                break;
                
                
            case ex:
                mod = 1;
                break;
                
            default:
                printf("\n잘못 입력하였습니다. 다시 입력하세요.\n\n");
                
        }
        
        if(mod)
            break;
    }
    
    
    
    return 0;
}

