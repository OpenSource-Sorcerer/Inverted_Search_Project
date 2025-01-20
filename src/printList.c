#include "main.h"

void print_list(File *head)
{
	if (head == NULL)
	{
		printf("NULL\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head -> file_name);
		    head = head -> link;
	    }
	    printf("NULL\n");
    }
}