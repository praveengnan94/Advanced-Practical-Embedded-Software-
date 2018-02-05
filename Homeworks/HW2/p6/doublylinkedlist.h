/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 02/03/2018
* DESCRIPTION	: This file contains the various library files, macros and forward function
					declarations of doublylinkedlist.c
		  
* SOURCE FILES	: doublylinkedlist.c
****************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define offsetof(type, member) ((size_t) &((type *)0)->member)

#define GET_LIST_CONTAINER(ptr, type, member) ({               \
       const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
       (type *)( (char *)__mptr - offsetof(type,member) );})


typedef struct node {
	struct node *prev;
	struct node *next;
}node_t;

typedef struct info {
	uint32_t data;
	struct node mylist;
}info_t;


//Function declarations
node_t* insert_at_beginning(node_t*, uint32_t);
node_t* insert_at_end(node_t*, uint32_t);
node_t* insert_at_position(node_t*, uint32_t, uint32_t);

node_t* destroy(node_t*);
node_t* delete_from_beginning(node_t*);
node_t* delete_from_end(node_t*);
node_t* delete_from_position(node_t*, size_t);

size_t size(node_t*);
