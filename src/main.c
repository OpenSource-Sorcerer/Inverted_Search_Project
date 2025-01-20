#include "main.h"

/* 
 * Prints line on screen
 * Inputs: ----
 * Output: Prints line on output screen
 * Return Value: ----
 */
void print_line()
{
    printf("%15s"," ");
    for(int i = 0; i < 50; i++)     printf("-");
}

/* 
 * Prints loading text
 * Inputs: usage
 * Output: Prints loading text on output screen
 * Return Value: ----
 */
void loading(int usage)
{
    char *string_print1 = malloc(25 * sizeof(char));

    char *string_print2 = malloc(25 * sizeof(char));
    printf("\n");

    if(!(usage ^ 4))   //redirect //4
    {    
        strcpy(string_print1,"Redirecting MainPage[");
        strcpy(string_print2,"MainPage Redirected");
    }

    for(int i = 1; i <= 100; i+=2)
    {
        printf("%15s%s"," ",string_print1);
        for(int j = 1; j <= 100; j+=2)
        {
            if(j <= i)  printf("\033[1;44m-\033[0m");

            else printf(" ");    
        }
        printf("]%d%%",i+1);
        fflush(stdout);
        usleep(50000);
        printf("\r");
    }
    printf("\n%15s%s\n\n"," ",string_print2);

    free(string_print1); free(string_print2);
}

/* 
 * Prints Error Message
 * Inputs: ----
 * Output: Prints Error Message on output screen
 * Return Value: ----
 */
int print_error()
{
    print_line();   printf("------------------------------------");
    printf("\n%15s\033[1mERROR : ./a.out : \033[1;37;41mINVALID ARGUMENTS\033[0m\n\n"," ");
    printf("\n%15s\033[1mTo perform operations please pass like       : \033[1;37;43m./a.out <file1name.txt> <file2name.txt>\033[0m\n\033[0m"," ");
    print_line();   printf("------------------------------------");
    printf("\n");
    return 0;
}

/* 
 * Choosing valid integer value
 * Inputs: integer value
 * Output: user should choose valid integer
 * Return Value: integer value
 */
int invalid_input(int iter)
{
    while(iter)
    {
        printf("\n%15sPlease Enter correct option (1 - Continue) / (0 - Exit) : ", " ");
        scanf("%d",&iter);

        if((!(iter ^ 1)) || !iter)  break;
    }
    return iter;
}

/* 
 * Checks database availability
 * Inputs: -----
 * Output: print the statement on screen
 * Return Value: FAILURE / SUCCESS
 */
int chk_Database_available(void)
{
    if((!(nibble.create_flag)) && (!(nibble.update_flag)))
    {
        print_line();
        printf("\n%15s\033[1mINFO   :   \033[1;37;41m:::%s:::\033[0m\n"," ","DATABASE NOT CREATED / UPDATED");
        print_line();
        loading(4);
        return FAILURE;
    }
    return SUCCESS;
}

/* 
 * Main function
 * Inputs: Command Line Arguments
 * Output: Execution starts here
 * Return Value: 0
 */
int main(int argc, char *argv[])
{
	/* Declare the pointers */
    Hash *head1 = malloc(28 * sizeof(Hash));

    File *head2 = NULL;

    M_Node *head3 = NULL;

    S_Node *head4 = NULL;

    Update *head5;

    /*Update flag values*/
    nibble.update_flag = 0;
    nibble.create_flag = 0;

    if(read_validate(argc, argv, &head2) == FAILURE)    {    print_error();  goto exit;    }

    else if(create_hashtable(head1, 28) == FAILURE)      {    print_error();  goto exit;    }
    
    printf("\n\n%56s\033[1;44m%s\033[0m\n\n", " ", " INVERTED SEARCH ");
    nibble.flag1 = 1;
    while(nibble.flag1) 
    {
        printf("\n%25s"," ");
        print_line();
        printf("\n%41s%49s\n%41s%21s\033[1;30;47m%s\033[0m%22s\n%41s%49s\n%25s","|","|","|"," "," MENU ","|","|","|"," ");
        print_line();

        printf("\n%41s%49s\n%41s%11s%21s%17s\n%41s%49s\n%41s%11s%21s%17s\n%41s%49s","|","|","|"," ","1.CREATE DATABASE","|","|","|","|"," ","2.SEARCH DATABASE","|","|","|");
        
        printf("\n%41s%11s%21s%17s\n%41s%49s\n%41s%11s%19s%19s\n%41s%49s","|"," ","3.UPDATE DATABASE","|","|","|","|"," ","4.SAVE DATABASE","|","|","|");

        printf("\n%41s%11s%22s%16s\n%41s%49s\n%41s%11s%10s%28s\n%41s%49s\n%25s","|"," ","5.DISPLAY DATABASE","|","|","|","|"," ","6.EXIT","|","|","|"," ");
        print_line();

        printf("\n\n%15s\033[1mPlease enter an option : \033[0m"," ");
        int opt = 0;

        start:
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                if(nibble.create_flag)
                {
                    print_line();
                    printf("\n%15s\033[1mINFO   :   \033[1;37;43m:::%s:::\033[0m\n"," ","DATABASE ALREADY CREATED");
                    print_line();
                    loading(4);
                }
                else
                    if(createDatabase(&head1, &head2, &head3, &head4) == FAILURE)   print_error();
                break;

            case 2:
                if(searchDatabase(&head1, &head2, &head3, &head4) == FAILURE)   print_error();
                break;

            case 3:
                if(nibble.update_flag || nibble.create_flag)
                {
                    print_line();
                    printf("\n%15s\033[1mINFO   :   \033[1;37;43m:::%s:::\033[0m\n"," ","DATABASE ALREADY CREATED OR UPDATED");
                    print_line();
                    loading(4);
                }
                else
                    if(updateDatabase(&head1, &head2, &head3, &head4, &head5) ==  FAILURE)  print_error();
                break;

            case 4:
                if(saveDatabase(&head1, &head2, &head3, &head4) == FAILURE)     print_error();
                break;

            case 5:
                if(displayDatabase(&head1, &head2, &head3, &head4) == FAILURE)  print_error(); 
                break;

            case 6:
                printf("\n%15s\033[1;41m:::!!!EXIT!!!:::\033[0m\n"," ");
                printf("\n\n%15s\033[1;37;43m!ARE YOU SURE!\033[0m (1 - Yes) / (0 - No) : ", " ");
                int flag = 0;
                scanf("%d",&flag);
                if(!(flag))  nibble.flag1 = 1;
                else if(flag ^ 1 && flag ^ 0)     nibble.flag1 = invalid_input(flag);
                else if(flag ^ 0)  nibble.flag1 = !(flag);
                break;

            default:
                printf("\n%15s\033[1;31;47m:::Invalid Input:::\033[0m\n\n%15s\033[1mPlease enter a correct option\033[0m (Ex : 2) : "," "," ");
                goto start;
        }
    }   
    exit:
    printf("\n%82s\n","\033[1;44m THANK YOU \033[0m");
    printf("\n");
    return 0;
}