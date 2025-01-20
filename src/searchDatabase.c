#include "main.h"

/* 
 * Search Database
 * Inputs: hash table head pointer, flle head pointer, main node pointer, sub node pointer
 * Output: search a word in database
 * Return Value: SUCCESS / FAILURE, based on Data found or not
 */
int searchDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4)
{
    //check Database created or not
    if(chk_Database_available() == FAILURE) return SUCCESS;

    //read a word
    char find_word[100];
    getchar();
    printf("%15sEnter a Word to search the Database : "," ");
    scanf("%s",find_word); 
    int index = findIndex(find_word);

    //compare with every word in hashtable
    for(int i = 0; i < 28; i++)
    {
        if((*head1)[i].link != NULL)
        {
            //main node present
            M_Node *temp1 = (*head1)[i].link;
            while(temp1 != NULL)
            {
                if(!(strcmp(temp1->word, find_word)))//if same word
                {
                    nibble.flag4 = 1;
                    printf("\n%15sWord \033[1;37;44m %s \033[0m present in \033[1;37;44m %d \033[0m files\n"," ",temp1->word,temp1->fileCount);
                    S_Node *temp2 = temp1->sublink;
                    do
                    {
                        printf("\n%15sIn file, \033[1;37;44m %s \033[0m \033[1;37;44m %d \033[0m times\n"," ",temp2->fileName,temp2->wordCount);
                        temp2 = temp2->link;
                    }
                    while(temp2 != NULL);
                }
                temp1 = temp1->mainlink;
            }
        }
    }
     
    print_line();
    if(!(nibble.flag4))   printf("\n%15s\033[1mINFO   :   \033[1;37;41m%s\033[0m\n"," ","DATA NOT FOUND"); 

    else    printf("\n%15s\033[1mINFO   :   \033[1;42m:::%s:::\033[0m\n"," ","DATA FOUND");
    print_line();
    loading(4);
    return SUCCESS;
}