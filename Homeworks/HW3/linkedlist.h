/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 02/18/2018
* DESCRITPTION  : This program all definitions for the linked list implementations
      
* SOURCE FILES  : threads.c
* HEADER FILES  : threads.h, customsignal.h

REFERENCE LINKS : https://stackoverflow.com/questions/14544539/linked-lists-in-c
****************************************************************/

/* Link list node */
struct Node
{
    int key;
    struct Node* next;
};
struct Node* head = NULL;

/* Given a reference (pointer to pointer) to the head
  of a list and an int, push a new node on the front
  of the list. */
void push(struct Node** head_ref, int new_key)
{
    /* allocate node */
    struct Node* new_node =
            (struct Node*) malloc(sizeof(struct Node));
 
    /* put in the key  */
    new_node->key  = new_key;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}

void print(struct Node* head_ref)
{
	struct Node * temp;

	temp=head;
	while(temp!=NULL)
	{
		printf("%d\n",temp->key);
		temp=temp->next;
	}
}

void insert(char a,struct Node* head_ref)
{
	int charnum,i;
	charnum=(int)a;
	struct Node* temp;

	if((a>=65)&&(a<=90))// upper case letters
	{
		charnum=charnum-65;
		// printf("Upper Char %c number %d\n",a,charnum);
		temp=head;
		for(i=0;i<charnum;i++)
		{
			temp=temp->next;
		}

		temp->key=temp->key+1;

	}
	else if ((a>=97)&&(a<=122))
	{
		
		charnum=charnum-97;
		// printf("Lower Char %c number %d\n",a,charnum);
		temp=head;
		for(i=0;i<charnum;i++)
		{
			temp=temp->next;
		}

		temp->key=temp->key+1;
	}
}