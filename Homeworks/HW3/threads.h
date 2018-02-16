#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <string.h>
#include <sys/syscall.h>

#define NUM_THREADS (3)
#define NUM_CPUS (1)

#define NSEC_PER_SEC (1000000000)
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)
#define DELAY_TICKS (1)
#define ERROR (-1)
#define OK (0)

pid_t getpid(void);
pid_t gettid(void);
pthread_t threads[NUM_THREADS];
pthread_attr_t rt_sched_attr[NUM_THREADS];
int rt_max_prio, rt_min_prio;
struct sched_param rt_param[NUM_THREADS];
struct sched_param main_param;
pthread_attr_t main_attr;
pid_t mainpid;
int rc;

/*Struct for threadinfo*/
typedef struct threadinfo
{
	char logfilename[20];	
	pthread_t pid;
	pid_t tid;
}threadinf;


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