#include "main.h"

int status = 0;

/* 
 * Open file
 * Inputs: file pointer
 * Output: opens the file with read mode
 * Return Value: NULL / file address, based on file availability
 */
FILE *open_file_chk(char *file_name)
{
    FILE *fptr = fopen(file_name, "r");
    if(fptr == NULL)    return NULL;
    
    return fptr;
}

/* 
 * Delete same file name
 * Inputs: file head pointer, string
 * Output: deletes the duplicate file name present in the file linked list
 * Return Value: 0 / 1, based on file deletion
 */
int delete_same_file(File **head, char *filename)
{
    File *temp = *head;
    File *prev;
    while(temp != NULL)
    {
        if(!(strcmp(filename, temp->file_name)))//same file name
        {
            if(temp == *head)   *head = temp->link;
            else    prev->link = temp->link;
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->link;
    }
    return 0;
}

/* 
 * Updates Database
 * Inputs: hash table head pointer, flle head pointer, main node pointer, sub node pointer
 * Output: Update databse with data present on backup file
 * Return Value: SUCCESS / FAILURE, based on update Database
 */
int updateDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4, Update **head5)
{
    //read file from user
    char bckup_file[50];
    getchar();
    printf("%15sEnter a File Name to save the Database : "," ");
    scanf("%s",bckup_file);
    
    //validate the file
    if(!(strstr(bckup_file, ".txt")))   goto print_err;

    //check status
    FILE *fp = open_file_chk(bckup_file);
    if(fp == NULL)   goto print_err;
    
    //check the chars in that file
    char ch;
    if((ch = fgetc(fp)) == '#') // first char valid
    {
        uint position_end = get_file_size(fp);
        fseek(fp, -2, SEEK_END);
        uint pos = ftell(fp);

        if((ch = fgetc(fp)) == '#') //last char valid
        {
            rewind(fp);pos = 0;
            M_Node *main_Node = NULL;
            int index = 0;
            //run loop until reachees last character
            while(1)
            {
                if(pos == position_end)   break;
            
                fscanf(fp,"#%d;%[^;];%d;",&((*head5)->index),(*head5)->word,&((*head5)->fileCount));

                //go to the index create main node
                index = (*head5)->index,
                (*head1)[index].key = index;

                //create main node 
                main_Node = createMainNode(head1, (*head1)[index].key, head3, (*head5)->fileCount, (*head5)->word);
                if(main_Node == NULL)   return FAILURE;

                int temp_f_count = (*head5)->fileCount;

                //Create subnodes based on file count
                while(temp_f_count)
                {
                    //S_Node *temp1 = main_Node->sublink;
                    fscanf(fp,"%[^;];%d;",(*head5)->fileName, &((*head5)->wordCount));

                    if(createSubNode(head1, (*head1)[index].key, main_Node, head4, (*head5)->wordCount, (*head5)->fileName) == FAILURE) return FAILURE;

                    //compare file name from backup file with files from cmd
                    status = delete_same_file(head2, (*head5)->fileName); //if same file file => delete that file name from list
                    
                    temp_f_count--;
                }
                fscanf(fp,"#\n");
                main_Node = main_Node->mainlink;
                pos = ftell(fp);
            }
        }
    }
    else
    {
        print_err:
        print_line();
        printf("\n%15s\033[1mINFO   :   \033[1;37;41m %s \033[0m  =>  \033[1mThis file doesn't have the database\033[0m\n"," ",bckup_file);
        printf("\n%15s"," ");     print_list(*head2);
        print_line();
        loading(4);
        return SUCCESS;
    }
    
    if(*head2 != NULL)  
    {
        print_line();
        printf("\n\n\n%15s"," ");
        print_list(*head2);
        printf("\n\n");
    }
    print_line();
    printf("\n%15s\033[1mINFO   :   \033[1;42m:::%s:::\033[0m\n"," ","DATABASE UPDATED");
    print_line();
    loading(4);
    nibble.update_flag = 1;
    return SUCCESS;
}