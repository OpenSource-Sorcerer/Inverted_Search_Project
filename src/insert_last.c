#include "main.h"

int insert_at_last(File **head, char filename[])
{
    //create a node
    File *new_;
    new_ = malloc(sizeof(File));
    
    if(new_ == NULL)    return FAILURE;
    strcpy(new_->file_name, filename);
    new_->link = NULL;
    
    //if empty list
    if(*head == NULL)
    {
        *head = new_;
        return SUCCESS;
    }
    
    //if non empty list
    File *temp = *head;
    while(temp->link != NULL)
    {
        temp = temp->link;
    }
    
    temp->link = new_;
    return SUCCESS;
}