#include "main.h"

FILE *fp = NULL;
char filename[50];

/* get file size
 * Input : file pointer
 * Output: EoF position in afile
 * Description: Calculating the file size by using fseek function
 */
uint get_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);
    uint position = (ftell(fptr));
    rewind(fptr);
    return position;
}

/* 
 * read and Validate CMD arguments
 * Inputs: count, cmd arguments, head pointer for file linked list
 * Output: Stores the valid file name into the file linked list
 * Return Value: FAILURE / SUCCESS, based on linked list 
 */
int read_validate(int argc, char *argv[], File **head2)
{
    int i = 1;
    //check the count
    if(argc < 2)    return FAILURE;

    else //count > 1
    {
        while(argv[i] != NULL)
        {
            if(strstr(argv[i], "."))
            {
                //check file extension
                if(!(strstr(argv[i], ".txt")))
                {
                    printf("\n%15s"," "); 
                    printf("\033[1mINFO   :   \033[1;37;41m %s \033[0m  =>  \033[1mThis file is not a '.txt' file\033[0m\n",argv[i]);
                    i++;
                    continue; //ignore the file
                }
                //check file existed or not
                strcpy(filename, argv[i]);
                fp = fopen(argv[i], "r");

                if(fp == NULL)  //file not found
                {

                    printf("\n%15s"," "); 
                    printf("\033[1mINFO   :   \033[1;37;41m %s \033[0m  =>  \033[1mThis file is not exist in the current directory\033[0m\n",argv[i]);
                    i++;
                    continue;   //ignore the file
                }
                else    //file found
                {
                    int position = get_file_size(fp);
                    //check file empty or not
                    if(position) //non empty
                    {
                        //check for duplicates
                        if(*head2 != NULL)
                        {  
                            File *temp = *head2;
                            while(temp != NULL)
                            {
                                if(!(strcmp(temp->file_name, filename)))    //duplicate file found
                                {
                                    printf("\n%15s"," "); 
                                    printf("\033[1mINFO   :   \033[1;37;41m %s \033[0m  =>  \033[1mThis file is repeated, so it will not store into the SLL\033[0m\n",filename);
                                    i++;  
                                    break;
                                }
                                temp = temp->link;
                            }
                            if(temp != NULL)    continue;   //ignore the file
                        }
                        //store file name //insert last
                        if(insert_at_last(head2, filename) == FAILURE)  return FAILURE; 
                        //print statement if file name inserted
                        else{
                            printf("\n%15s"," "); 
                            printf("\033[1mINFO   :   \033[1;37;42m %s \033[0m  =>  \033[1mInserting file name into file linked list successfull\033[0m\n",argv[i]);
                        } 
                    }
                    else 
                    {
                        printf("\n%15s"," "); 
                        printf("\033[1mINFO   :   \033[1;37;41m %s \033[0m  =>  \033[1mThis file is empty\033[0m\n",argv[i]);
                        i++;
                        continue; //ignore the file
                    }
                }
            }
            else 
            {

                printf("\n%15s"," "); 
                printf("\033[1mINFO   :   \033[1;37;41m %s \033[0m  =>  \033[1mThis file has no extension\033[0m\n",argv[i]);
                i++;
                continue; //ignore the file
            }
            i++;
        }
    }
    
    if(*head2 == NULL)
    {
        printf("\n%15s"," "); 
        printf("\033[1mINFO   :   \033[1mFiles are not there\n%15sCreate database is not possible\n\033[0m\n"," ");
        printf("\n%15s"," ");   print_list(*head2);
        printf("\n\n");
        return FAILURE;
    }
    else
    {
        printf("\n%15s"," ");    print_list(*head2);
    }
    return SUCCESS;
}

/* 
 * Creates HashTable
 * Inputs: head pointer for hash array, size
 * Output: creates hashtable based on the size
 * Return Value: SUCCESS
 */
int create_hashtable(Hash *head1, int size)
{
    for(int i = 0 ; i < size; i++)
    {
        head1[i].key = i;
        head1[i].link = NULL;
    }
    return SUCCESS;
}