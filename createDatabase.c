#include "main.h"

/* 
 * Open file
 * Inputs: file pointer
 * Output: opens the file with read mode
 * Return Value: NULL / file address, based on file availability
 */
FILE *openFile(File *f_name)
{
    FILE *fptr = fopen(f_name->file_name, "r");
    if(fptr == NULL)
    {
        perror("fopen");
	    fprintf(stderr, "ERROR: Unable to open file %s\n", f_name->file_name);

	    return NULL;
    }
    return fptr;
}

/* 
 * Close file
 * Inputs: file head pointer
 * Output: closes all the file, presemt in the file linked list
 * Return Value: SUCCESS / FAILURE, based on file availability
 */
int closeFiles(File *head2)
{
    File *temp = head2;

    //print_list(head2);
    while(temp != NULL)
    {
        FILE *fptr = fopen(temp->file_name, "r");
        if(fptr == NULL)
        {
            perror("fopen");
	        fprintf(stderr, "ERROR: Unable to close the file %s\n", temp->file_name);

	        return FAILURE;
        }
        fclose(fptr);
        temp = temp->link;
    }
    return SUCCESS;
}

/* 
 * Checks given character
 * Inputs: character
 * Output: checks given character is digit ot not
 * Return Value: SUCCESS / FAILURE, based on character
 */
int is_digit(char ch)
{
    return (ch >= '0' && ch <= '9') ? SUCCESS : FAILURE;
}

/* 
 * Checks given character
 * Inputs: character , integer pointer
 * Output: checks  given character is alphabet or not
 * Return Value: SUCCESS / FAILURE, based on character
 */
int is_alpha(char ch, int *index)
{
    if(ch >= 'a' && ch <= 'z')      {     (*index) = ch - 'a';   return SUCCESS;     }

    else if(ch >= 'A' && ch <= 'Z') {     (*index) = ch - 'A';   return SUCCESS;     }

    else return FAILURE;
}

/* 
 * Find the index
 * Inputs: string
 * Output: index value of given string
 * Return Value: index value
 */
int findIndex(char *str)
{
    int index = 0;

    if(is_digit(str[0]) == SUCCESS) return 26;                   //digit

    else if(is_alpha(str[0], &index) == SUCCESS) return index;   //alphabet
    
    else return 27;                                              //special character
}

/* 
 * Creates Main node
 * Inputs: hash table head pointer, index, main node pointer, filecount, word
 * Output: creates main node based on the key on hash table
 * Return Value: NULL, Main_node address based on main node creation
 */
M_Node *createMainNode(Hash **head1, int index, M_Node **head3, int filecount, char *word)
{
    M_Node *new_ = malloc(sizeof(M_Node));
    if(new_ == NULL)    return NULL;

    new_->fileCount = 1;
    strcpy(new_->word, word);
    new_->mainlink = NULL;
    new_->sublink = NULL;
    if((*head1)[index].link == NULL) //first node
    {
        *head3 = new_;
        (*head1)[index].link = new_;
    }  
    else
    {
        //traverse to the last main node
        M_Node *temp = (*head1)[index].link;
        while(temp->mainlink != NULL)
            temp = temp->mainlink;

        temp->mainlink = new_;
    }
    return  new_;
}

/* 
 * Creates Sub node
 * Inputs: hash table head pointer, index, main node pointer, sub node pointer, wordcount, filename
 * Output: creates main node based on the main node address
 * Return Value: SUCCESS / FAILURE, based on sub node creation
 */
int createSubNode(Hash **head1, int index, M_Node *mainNode, S_Node **head4, int wordcount, char *filename)
{
    S_Node *new_ = malloc(sizeof(S_Node));
    if(new_ == NULL)    return FAILURE;

    new_->wordCount = wordcount;
    strcpy(new_->fileName, filename);
    new_->link = NULL;

    if(mainNode->sublink == NULL)//first main node's first subnode
    {
        *head4 = new_;
        mainNode->sublink = new_;
    }
    else
    {
        //traverse to the last sub node in the main node
        S_Node *temp = mainNode->sublink;
        while(temp->link != NULL)
            temp = temp->link;
        
        temp->link = new_;
    }
    return SUCCESS;
}

/* 
 * Creates Database
 * Inputs: hash table head pointer, flle head pointer, main node pointer, sub node pointer
 * Output: creates database based on file names passed through CMD
 * Return Value: SUCCESS / FAILURE, based on Database creation
 */
int createDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4)
{
    //Read data from files
    char *word = malloc(100 * sizeof(char));
    File *temp = *head2;
    M_Node *main_Node = NULL;
    int f_count = 1, w_count = 1;
    while(temp != NULL)
    {
        //open files 
        FILE *fp = openFile(temp);
        if(fp == NULL)  return FAILURE;
        char ch;
        //Get a word from a file
        while(ch = fscanf(fp,"%s",word) != EOF)
        {
            int index = findIndex(word);    //find index

            (*head1)[index].key = index;
            //Add main node and sub node to hashtable if hashtable's index link is NULL
            if((*head1)[index].link == NULL)
            {
                //create main node and subnode
                main_Node = createMainNode(head1, index, head3, f_count, word);
                if(main_Node == NULL)   return FAILURE;

                if(createSubNode(head1, index, main_Node, head4, w_count, temp->file_name) == FAILURE) return FAILURE;
            }
            else //Already nodes are present
            { 
                //Check the words in main node
                M_Node *temp1 = (*head1)[index].link;
                while(temp1 != NULL)
                {
                    nibble.flag3 = 0;
                    //check the same word is present or not
                    if(!strcmp(word, temp1->word))  //if same word
                    {
                        nibble.flag3 = 1;
                        //check filename in sub node
                        S_Node *temp2 = temp1->sublink;
                        while(temp2 != NULL)
                        {
                            nibble.flag2 = 0;
                            if(!strcmp(temp2->fileName, temp->file_name))  //if same filename
                            {
                                temp2->wordCount += 1;
                                nibble.flag2 = 1;
                                break;
                            }
                            temp2 = temp2->link;
                        }
                        if(!(nibble.flag2)) //different filename
                        {
                            if(createSubNode(head1, index, temp1, head4, w_count, temp->file_name) == FAILURE) return FAILURE;
                            temp1->fileCount += 1;
                        }
                    }
                    if(nibble.flag3)    break;
                    temp1 = temp1->mainlink;
                }
                if(!(nibble.flag3)) //different word
                {
                    //create main node and subnode
                    main_Node = createMainNode(head1, index, head3, f_count, word);
                    if(main_Node == NULL)   return FAILURE;
                    
                    if(createSubNode(head1, index, main_Node, head4, w_count, temp->file_name) == FAILURE) return FAILURE;
                }
            }
        }
        temp = temp->link;
    }
    if(closeFiles(*head2) == FAILURE)   return FAILURE;
    free(word);
    print_line();
    printf("\n%15s\033[1mINFO   :   \033[1;42m:::%s:::\033[0m\n"," ","DATABASE CREATED");
    printf("\n%15s"," ");     print_list(*head2);
    print_line();
    loading(4);
    nibble.create_flag = 1;
    return SUCCESS;
}