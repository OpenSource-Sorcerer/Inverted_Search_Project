#include "main.h"

/* 
 * Save Database
 * Inputs: hash table head pointer, flle head pointer, main node pointer, sub node pointer
 * Output: data from hashtable stroed in one .txt file
 * Return Value: SUCCESS / FAILURE, based on saving Database
 */
int saveDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4)
{
    //check Database created or not
    if(chk_Database_available() == FAILURE) return SUCCESS;
    //read file from user
    char bckup_file[50];
    getchar();
    printf("%15sEnter a File Name to save the Database : "," ");
    scanf("%s",bckup_file);
    //validate the file
    if(!(strstr(bckup_file, ".txt")))   return FAILURE;

    FILE *fp = fopen(bckup_file, "w"); 

    for(int i = 0; i < 28; i++)
    {
        if((*head1)[i].link != NULL)
        {
            //main node present
            M_Node *temp1 = (*head1)[i].link;
            while(temp1 != NULL)
            {
                fprintf(fp,"#%d;%s;%d;",i, temp1->word,temp1->fileCount);
                S_Node *temp2 = temp1->sublink;
                do
                {
                    fprintf(fp,"%s;%d;",temp2->fileName,temp2->wordCount);
                    temp2 = temp2->link;
                }
                while(temp2 != NULL);
                fprintf(fp,"%c\n",'#');
                temp1 = temp1->mainlink;
            }
        }
    }
    print_line();
    printf("\n%15s\033[1mINFO   :   \033[1;42m:::%s:::\033[0m\n"," ","DATABASE SAVED");
    print_line();
    fclose(fp);
    loading(4);
    return SUCCESS;
}