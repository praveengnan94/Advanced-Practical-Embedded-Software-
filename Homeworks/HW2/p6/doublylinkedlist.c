/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 02/03/2018
* DESCRIPTION	: This program implements a doublylinkedlist and performs various
					operations on the linked list
		  
* HEADER FILES	: doublylinkedlist.h
****************************************************************/

#include "doublylinkedlist.h"

node_t* head=NULL;

node_t* insert_at_beginning(node_t* head, uint32_t data)
{

	//if no head exists, init this node as head
	if(head == NULL)
	{
		//allocate memory
		info_t* new_node = (info_t*)malloc(sizeof(info_t));
		
		new_node->data = data;
				
		new_node->mylist.prev = NULL;
		new_node->mylist.next = NULL;

		head = &(new_node->mylist);
	}

	else
	{
		info_t* new_node = (info_t*)malloc(sizeof(info_t));

		new_node->data = data;

		new_node->mylist.prev = NULL;
		new_node->mylist.next = head;

		
		
		head->prev = &(new_node->mylist); 

		head = &(new_node->mylist);
	}

	return head;
}

node_t* insert_at_end(node_t* head, uint32_t data)
{

	//if no head exists, init this node as head
	if(head == NULL)
	{
		//allocate memory
		info_t* new_node = (info_t*)malloc(sizeof(info_t));
		
		new_node->data = data;
				
		new_node->mylist.prev = NULL;
		new_node->mylist.next = NULL;

		head = &(new_node->mylist);
	}
	else
	{
		node_t* temp=head;
		//go to end of list
		while(temp->next != NULL)
		{
			temp = temp->next;
		}

		info_t* new_node = (info_t*)malloc(sizeof(info_t));
		
		temp->next=&(new_node->mylist);
		new_node->mylist.prev=temp;
		new_node->mylist.next=NULL;
		new_node->data=data;
	}

	return head;
}


node_t* insert_at_position(node_t* head, uint32_t data , uint32_t position)
{
	if(head == NULL)
	{
		if(position == 0)
		{
			head=insert_at_beginning(head,data);
		}
		else
		{
			printf("Cannot insert at position %d. HEAD is NULL\n",position);
			head=NULL;
		}

	}
	else
	{
		size_t sze=size(head);

		if(position > (sze+1))
		{
			printf("Position is greater than size- Node not inserted\n");
			return NULL;
		}
		else if(position < 0)
		{
			printf("Position is negative\n");
			return NULL;
		}
		else if(position ==0)
		{
			head=insert_at_beginning(head,data);
		}
		else if (position == (sze+1))
		{
			insert_at_end(head,data);
		}
		else
		{
			node_t* temp=head;
			node_t* tempstore;
			size_t cntt=0;

			while(cntt < position-1)
			{
				temp = temp->next;
				cntt++;	
			}

			info_t* new_node = (info_t*)malloc(sizeof(info_t));
		
			new_node->data = data;
					
			tempstore=temp->next;

			temp->next=&(new_node->mylist);

			new_node->mylist.prev = temp;
			new_node->mylist.next=tempstore;
			tempstore->prev=&(new_node->mylist);

		}

	}

	return head;
}

node_t* delete_from_beginning(node_t* head)
{
	if(head==NULL)
	{
		printf("Head node is NULL \n");
	}
	else
	{
		info_t* temp;

		temp=GET_LIST_CONTAINER(head,info_t,mylist);

		head=head->next;

		free(temp);
	}

	return head;
}

node_t* delete_from_end(node_t* head)
{
	if(head==NULL)
	{
		printf("Head node is NULL \n");
	}
	else
	{
		info_t* temp;
		node_t* tempseclast;
		node_t* temptraverse=head;

		while(temptraverse->next != NULL)
		{
			temptraverse = temptraverse->next;
		}

		temp=GET_LIST_CONTAINER(temptraverse,info_t,mylist);

		tempseclast=temptraverse->prev;
		tempseclast->next=NULL;
		temptraverse->prev=NULL;

		free(temp);
	}

	return head;
}

node_t* delete_from_position(node_t* head,size_t position)
{
	if(head==NULL)
	{
		printf("Head is NULL.Cannot delete\n");
	}
	else
	{
		size_t sze=size(head);

		if(position >= (sze))
		{
			printf("Position is greater than size- Node not deleted\n");
			return NULL;
		}
		else if(position < 0)
		{
			printf("Position is negative\n");
			return NULL;
		}
		else if(position == 0)
		{
			head=delete_from_beginning(head);
		}
		else if (position == (sze-1))
		{
			delete_from_end(head);
		}
		else
		{
			node_t* temp=head;
			node_t* prevtemp;
			node_t* nexttemp;
			info_t* node;
			size_t cntt=0;

			while(cntt < (position-1))
			{
				temp = temp->next;
				cntt++;	
			}

			prevtemp=temp->prev;
			nexttemp=temp->next;
		    
		    prevtemp->next=nexttemp;
		    nexttemp->prev=prevtemp;

		    node=GET_LIST_CONTAINER(temp,info_t,mylist);
		    free(node);
		}

	}
	return head;

}


size_t size(node_t* head)
{
	node_t* temp=head;
	size_t sze=0;

	if(temp == NULL)
	{
		printf("Doubly Linked list is empty\n");
		sze=0;
	}
	else
	{
		//go to end of list
		while(temp != NULL)
		{
			sze++;	
			temp = temp->next;
		}
	}
	return sze;	
}

//DO NOT IMPLEMENT
void print_list(node_t* head)
{
	node_t* temp=head;
	int cnt = 0;

	if(temp == NULL)
	{
		printf("Doubly Linked list is empty\n");
	}
	else
	{
		//go to end of list
		while(temp != NULL)
		{
			info_t* node_addr = GET_LIST_CONTAINER(temp, info_t, mylist);
			printf("Link %d has %d\n", cnt, node_addr->data);	
			cnt++;	
			temp = temp->next;
		}
	}	
}

// int main(void)
// {

// 	head = insert_at_beginning(head, 16);	

// 	head = insert_at_beginning(head, 24);	

// 	head = insert_at_beginning(head, 32);	

// 	head = insert_at_end(head, 64);

// 	head = insert_at_end(head, 72);

// 	head = insert_at_end(head, 84);

// 	head = insert_at_position(head, 80, 3);

// 	print_list(head);
// 	head = insert_at_position(head, 500, 3);
// 	head = insert_at_position(head, 10, 0);	
// 	print_list(head);

// 	printf("Size of list is %ld\n",size(head));

// 	head = delete_from_beginning(head);	

// 	print_list(head);
// 	head = delete_from_end(head);	
// 	print_list(head);

// 	printf("Size of list is %ld\n",size(head));
// 	head = delete_from_position(head, 2);

// 	print_list(head);

// 	return 0;	
// }














