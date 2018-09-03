#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


Node *pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *))
{

	if( new_object == NULL)
	{
		return NULL;
	}
	Node* head = malloc(sizeof(*head));

	if(head == NULL)
	{
		return NULL;
	}

	head -> ptr = (void*)new_object;
	head -> next = NULL;

	Node* temp = *pq;

	Node* curr = NULL;
//	Node* start = malloc(sizeof(*start));
//	Node* start_curr = *pq;

	while(temp != NULL && cmp_fn(temp -> ptr, new_object) <  0)
	{
		curr = temp;
		temp = temp -> next;
//		start -> ptr = start_curr -> ptr;
//		start_curr = start_curr -> next;
		

	}

	if(temp == *pq)  // add new_object to the beginning of the list 
	{
		head -> next = *pq;
		*pq = head;
		return head;
	}
	curr -> next = head;
	head -> next = temp;
//	start_curr -> next = curr;
	return head;
}

// aniyaz@purdue.edu
                       
Node *pq_dequeue(Node **pq)
{
	if(*pq == NULL)
	{
		return NULL;
	}
	Node* head = *pq;

	Node* curr = head -> next;
	head -> next = NULL;
	*pq = curr;

   return head;
}


Node *stack_push(Node **stack, const void *new_object)
{
	if(new_object == NULL)
	{
		return NULL;
	}
	Node* head = malloc(sizeof(*head));
	if(head == NULL)
	{
		return NULL;
	}
	head -> ptr = (void*)new_object;
	head -> next = *stack;
	*stack = head;

   return head;
}

                       
Node *stack_pop(Node **stack)
{
	Node* head  = pq_dequeue(stack);
	return head;
}


Node *remove_last_node(Node **list)
{
	if(*list == NULL)
	{
		return NULL;
	}
	
	

	Node* last = *list;
	Node* curr;
	while((last -> next) != NULL)
	{	
		curr = last;
		last = last -> next;
	}
	curr = last;
	last -> next = NULL;

	if(last == *list)
	{
		*list = NULL;
	}



	return curr;
}


void destroy_node(Node *list, void (*destroy_fn)(void *))
{
	Node* curr = list;
	Node* next;

	while(curr != NULL)
	{
		next = curr -> next;
		destroy_fn(curr->ptr);
		free(curr);
		curr = next;
	}

   return;
}




/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void print_node(const Node *list, void (*print_fn)(const void *))
{
   while (list != NULL) {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   } 
   // print NULL and a newline after that 
   fprintf(stdout, "NULL\n");
}

