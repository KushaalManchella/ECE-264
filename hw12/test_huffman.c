#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


void _print_fn(const void* ptr) {
	   printf("%d", *(const int*)ptr);
	   return ;
	}

int _cmp_fn(const void* p1, const void* p2) {
	return *(const int*)p1 - *(const int*)p2;
	}

void _destroy_fn(void* ptr){
	return;
}

int main(int argc, char* argv[])
{
	int val1 = 5;
	// create list
	Node * head = malloc(sizeof(*head));
	head -> ptr = &val1;
	Node* enqueue;

	// data to add to list	int data [] = {2,3};
	int val3 = 3;
    int data[]={1,2,3,4};
	printf("Node at beginning :");
//	print_node(head, _print_fn);  
	printf("\n");

	// iterate through list and test enqueue (adding to list)
for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++) {
		 enqueue = pq_enqueue(&head, &(data[i]), _cmp_fn);
	}

	


	print_node(head, _print_fn);

	// testing dequeue
	
	Node* dequeue = pq_dequeue(&head);
	printf("Deqeueu:");
	print_node(head, _print_fn);
	printf("\n");

	// testing stack_push
	

	Node* push = stack_push(&head, &val3);
	printf("stack_push:");
	print_node(head, _print_fn);
	printf("\n");

	// testing stack_pop
	
	stack_pop(&head);
	printf("stack_pop:");
	print_node(head, _print_fn);
	printf("\n");
	
	// testing remove last node; 
	
	remove_last_node(&head);
	printf("remove_last_node:");
	print_node(head, _print_fn);
	printf("\n");

	// destroying node 
	
	destroy_node(head, _destroy_fn);

	destroy_node(dequeue, _destroy_fn);

	destroy_node(push, _destroy_fn);
    destroy_node(enqueue,_destroy_fn);
}
	
