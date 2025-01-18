#ifndef MAIN_H
#define MAIN_H

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "ctype.h"
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

typedef unsigned int uint;

typedef unsigned char uch;

/*Structues Declaration*/
typedef struct FileNames
{
    char file_name[50];
    struct FileNames *link;
}File;

typedef struct HashTable
{
    int key;
    struct MainNode *link;
}Hash;

typedef struct MainNode
{
    int fileCount;
    char word[100];
    struct SubNode *sublink;
    struct MainNode *mainlink;
}M_Node;

typedef struct SubNode
{
    int wordCount;
    char fileName[50];
    struct SubNode *link;
}S_Node;

typedef struct UpdateInfo
{
    int index;
    char word[100];
    int fileCount;
    int wordCount;
    char fileName[50];
}Update;

/* Uisng Bit Fields for flags */
struct NIBBLE
{
    uch flag1 : 1;
    uch flag2 : 1;
    uch flag3 : 1;
    uch flag4 : 1;
    uch create_flag : 1;
    uch update_flag : 1;
};

/* Initializing structure for flags */
struct NIBBLE nibble;

/* Include the prototypes here */

/*Read and Validate*/
int read_validate(int argc, char *argv[], File **head2);

/*Create HashTable*/
int create_hashtable(Hash *HT, int size);

/*Create Database*/
int createDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4);

/*Search Database*/
int searchDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4);

/*Update Database*/
int updateDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4, Update **head5);

/*Save Database*/
int saveDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4);

/*Display Database*/
int displayDatabase(Hash **head1, File **head2, M_Node **head3, S_Node **head4);

/*Open a File*/
FILE *openFile(File *head2);

/*Find Index*/
int findIndex(char *str);

/*Create subnode*/
int createSubNode(Hash **head1, int index, M_Node *mainNode, S_Node **head4, int wordcount, char *filename);

/*Create Mainnode*/
M_Node *createMainNode(Hash **head1, int index, M_Node **head3, int filecount, char *word);

/*Insert at Last*/
int insert_at_last(File **head, char filename[]);

/*Get File Size*/
uint get_file_size(FILE *fptr);

/*Print List*/
void print_list(File *head);

/*Loading text*/
void loading(int usage);

/*Print Vertical Line*/
void print_line();

/*Check DataBase Availability*/
int chk_Database_available(void);

#endif
