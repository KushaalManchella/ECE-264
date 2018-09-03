#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
	if(argc != 5)     
	{
		return EXIT_FAILURE;
	}

	long int ascii_count[256] = {0};

	int ch = 0;

	FILE *fp = fopen(argv[1], "r");
	FILE *fe = fopen(argv[2], "w");
	FILE *ff = fopen(argv[3], "w");
	FILE *fg = fopen(argv[4], "w");


	// Section to print occurences of character in output_file1
	while(ch != EOF)  
	{
		ch = fgetc(fp);
		if(ch != EOF)
		{
				ascii_count[ch]++;
		}
	}

	
	Node * head = NULL; // initializing Node
		
	for(int i = 0; i < 256; i++) {
		if( ascii_count[i]!= 0)
		{
			TreeNode* t_curr = malloc(sizeof(*t_curr));
			t_curr -> freq = ascii_count[i];
			t_curr -> ASCII = i;
			t_curr -> left = NULL;
			t_curr -> right = NULL;

			pq_enqueue(&head, t_curr, _cmp_fn);
		
		}
	}
	
	Node* temp = NULL;
	temp = head;

	while(temp -> next != NULL) // change back to temp if doesn't work
	{
	    temp = temp -> next;
	}

	// Building the tree
	
	int count_branch = 0;
	

	while(head -> next != NULL)
	{
		// dequeue two smallest nodes 
		Node* left_most = pq_dequeue(&head); // left most 
		Node* next_lm = pq_dequeue(&head); // left most after left most 
	

		TreeNode* parent = malloc(sizeof(*parent));  //Create tree node that is parent node of two smallest nodes
		parent -> freq = left_most -> ptr -> freq + next_lm -> ptr -> freq;
		parent -> left = left_most -> ptr; 
		parent -> right = next_lm -> ptr ;
	
		free(left_most);
		free(next_lm);

		pq_enqueue(&head, parent, _cmp_fn2); // enqueue new node into the linked list. // I just changed this to temp  
		count_branch++;
	}
		
	// recursion (output 1)	
	TreeNode* huffman = head -> ptr;

	int* path = malloc(sizeof(path) * 9);
	for(int i =0; i < 9; i++)
	{
		path[i] = -1;		
	}

	int count = 0;	
	
	_recurse(huffman, fe, path, count);
	

	// recursion (output 2)
	
	char* header = malloc(sizeof(char) * 512);
	for(int i = 0; i < 512; i++)
	{
		header[i] = -1;
	}

	_huffman_header(huffman,  ff);
	fprintf(ff,"0");
	
	fclose(ff);
	
	// put contents of output file in array 
	
	fopen(argv[3], "r");
	
	ch = 0;

	count = 0;
	while(!feof(ff))
	{
		ch = fgetc(ff);
		header[count] = ch;
		count += 1;
	}
	
	bit_convert(fg, header);
	
	

// time to free stuff 

	Node* temp2 = head;
	while(temp2 != NULL)
	{
		_destroy_tree(temp2 -> ptr);
		temp2 = temp2 -> next;
	}
	_destroy_node(head);

	free(path);

	fclose(fp);
	fclose(fe);
	fclose(ff);
	fclose(fg);
	

	return EXIT_SUCCESS;
}
