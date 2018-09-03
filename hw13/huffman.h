#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _TreeNode{
	int freq;
	char ASCII;
	struct	_TreeNode * left;
	struct	_TreeNode * right;
} TreeNode;

typedef struct _Node {
   TreeNode  *ptr;
   struct _Node *next;
} Node;


void _destroy_node(Node *head);

void _destroy_tree(TreeNode* tree);

int _cmp_fn(TreeNode* p1, TreeNode* p2);

Node *pq_enqueue(Node **pq, TreeNode *new_object, 
                  int (*cmp_fn)(TreeNode *, TreeNode *));

TreeNode* _create_node(int freq,char ASCII);

void _print_fn(const void* ptr);

Node *pq_dequeue(Node **pq);

void print_node(const Node *list, void (*print_fn)(const void *));

int _cmp_fn2(TreeNode* p1, TreeNode* p2);

void _recurse(TreeNode* curr, FILE* fd,int* path, int count);

// Node* _ordered_ll(long int array[], Node* head)


