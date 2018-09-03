#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>






void _destroy_node(Node *head){

	if(head == NULL)
	{
		return;
	}

	Node* curr = head;
	
	while(head != NULL)
	{
		curr = head -> next;
		free(head);
		head = curr;
	}
}

void _destroy_tree(TreeNode* tree){
	if(tree == NULL)
	{
		return;
	}
	_destroy_tree(tree -> left);
	_destroy_tree(tree -> right);
	free(tree);
}


int _cmp_fn(TreeNode* p1, TreeNode* p2) {
	if((p1 -> freq) < (p2 -> freq))
	{
		return -1;
	}
	else if((p1 -> freq) > (p2 -> freq))
	{
		return 1;
	}
	else
	{
		return (p1 -> ASCII) - (p2 -> ASCII);
	}

}


int _cmp_fn2(TreeNode* p1, TreeNode* p2) {
	if((p1 -> freq) < (p2 -> freq))
	{
		return -1;
	}
	else if((p1 -> freq) > (p2 -> freq))
	{
		return 1;
	}
	else if (p1 -> freq == p2 -> freq)
	{
		if(p1 -> left == NULL && p2 -> right != NULL)
		{
			return -1;
		}
		else if(p1 -> left != NULL && p2 -> right == NULL)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}


	
Node *pq_enqueue(Node **pq, TreeNode *new_object, 
                  int (*cmp_fn)(TreeNode *, TreeNode *))
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
	head -> ptr = (TreeNode*)new_object;
	head -> next = NULL;

	Node* temp = *pq;
	Node* curr = NULL;

	while(temp != NULL && cmp_fn(temp -> ptr, new_object) <  0)
	{
		curr = temp;
		temp = temp -> next;
		
	}

	if(temp == *pq)  // add new_object to the beginning of the list 
	{
		head -> next = *pq;
		*pq = head;
		return head;
	}
	curr -> next = head;
	head -> next = temp;
	
	return head;
}


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

	
TreeNode* _create_node(int freq,char ASCII){
	TreeNode tree = {
		.freq = freq,
		.ASCII = ASCII,
		.left = NULL,
		.right = NULL
	};
	TreeNode* node = malloc(sizeof(*node));
	*node = tree;

	return node;

}


void _print_fn(const void* ptr) {
	   printf("%d", *(const int*)ptr);
	   return ;
	}


void print_node(const Node *list, void (*print_fn)(const void *)){
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

void _recurse(TreeNode* curr, FILE* fe,int* path, int count)
{
	if(curr -> right == NULL) // if you hit a leaf, print ASCII and PATH 
	{
		fprintf(fe, "%c:", (char)curr -> ASCII);
		for(int i = 0; i < count; i++)
		{
			fprintf(fe,"%d", path[i]);
		}
		fprintf(fe, "\n");
		
	}
	else
	{
		path[count]= 0;
		_recurse(curr -> left, fe, path, count+1);
		path[count]= 1;
		_recurse(curr -> right, fe, path, count+1);
	}
	
}








