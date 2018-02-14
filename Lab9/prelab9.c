#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int num;
	struct Node* left;
	struct Node* right;
}node;

node* add_to_tree(node* head, int number);
void print_in_order(node* head);
void print_in_reverse(node* head);
void free_tree(node* head);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Insufficient Arguments");
		return 1;
	}
	
	FILE* fp = fopen(argv[1], "r");

	int temp;
	node* head = NULL;

	while(fscanf(fp, "%d", &temp) == 1)
	{
		head = add_to_tree(head, temp);
	}

	printf("printing the list in order\n");
	print_in_order(head);

	printf("printing the list in reverse order\n");
	print_in_reverse(head);

	free_tree(head);

return 0;
}

node* add_to_tree(node* head, int number)
{
	if(head == NULL)
	{
		head = malloc(sizeof(node));
		head -> num = number;
		head -> left = NULL;
		head -> right = NULL;
	}
	else if(number < head-> num)
	{
		head -> left = add_to_tree(head -> left, number);
	}
	else
	{
		head -> right = add_to_tree(head -> right, number);
	}

return head;
}

void print_in_order(node* head)
{
	if(head != NULL)
	{
	print_in_order(head -> left);
	printf("%d\n", head -> num);

	print_in_order(head -> right);
	}
}

void print_in_reverse(node* head)
{
	if(head != NULL)
	{
	print_in_reverse(head -> right);
	printf("%d\n", head ->num);

	print_in_reverse(head -> left);
	}
}

void free_tree(node* head)
{
	if(head != NULL)
	{
		free_tree(head -> left);
		free_tree(head -> right);
		free(head);
	}
}
