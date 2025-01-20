#include "main.h"

/* 
 * Prints line on screen
 * Inputs: ----
 * Output: Prints line on output screen
 * Return Value: ----
 */
void line_print()
{
    printf("%15s"," ");
    for(int i = 0; i <= 100; i++)
        printf("-");
}

/* 
 * Display Database
 * Inputs: hash table head pointer, flle head pointer, main node pointer, sub node pointer
 * Output: Prints data from hashtable on the screen
 * Return Value: SUCCESS
 */
int displayDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4)
{
    //check Database created or not
    if(chk_Database_available() == FAILURE) return SUCCESS;

    printf("\n");
    print_line();
    printf("\n%15s\033[1mINFO   :   \033[1;42m:::%s:::\033[0m\n"," ","DATABASE lOADED");
    print_line();
    printf("\n");
    //run a loop to get main node in hashtable index

    //Headings
    line_print();

    printf("\n%15s|%100s\n%15s|\033[1m%56s\033[0m%44s\n%15s|%100s\n"," ","|"," "," DATABASE  ","|"," ","|");

    line_print();

    printf("\n%15s|   \033[1mINDEX\033[0m  |               \033[1mWORD\033[0m                |   \033[1mFILE_COUNT\033[0m  |     \033[1mFILE_NAME\033[0m     |    \033[1mWORDCOUNT\033[0m   |\n"," ");
   
    printf("%15s|%11s%36s%16s%20s%17s\n"," ","|","|","|","|","|");

    //line_print();
    nibble.flag1 = 0;
    for(int i = 0; i < 28; i++)
    {
        if((*head1)[i].link != NULL)
        {
            //main node present
            M_Node *temp1 = (*head1)[i].link;
            while(temp1 != NULL)
            {
                int len = strlen(temp1->word);
                line_print();
                printf("\n%15s|    %3d%4s%25s%11s%12d%4s"," ",i,"|",temp1->word,"|",temp1->fileCount,"|");
                S_Node *temp2 = temp1->sublink;
                do
                {
                    if(nibble.flag1)   printf("%15s|       %4s%25s%11s%12s%4s%15s%5s%12d%5s\n%15s|%11s%36s%16s%20s%17s\n"," ","|"," ","|", " ","|",temp2->fileName,"|",temp2->wordCount,"|"," ","|","|","|","|","|");
                    
                    else    printf("%15s%5s%12d%5s\n%15s|%11s%36s%16s%20s%17s\n",temp2->fileName,"|",temp2->wordCount,"|"," ","|","|","|","|","|");
        
                    temp2 = temp2->link;
                }
                while(temp2 != NULL && (nibble.flag1 = 1));
                nibble.flag1 = 0;
                temp1 = temp1->mainlink;
            }
        }
    }
    line_print();
    loading(4);
    nibble.flag1 = 1;
    return SUCCESS;
}