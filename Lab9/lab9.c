//Wade Tobin
//Lab 9
//Section E
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int num;
	int count;
	struct Node* left;
	struct Node* right;
}node;

node* add_to_tree(node* head, int number);
int print_totals(node* head, int count);
void free_tree(node* head);

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Wrong Argument count");
		return 0;
	}

	int option = 0;
	int temp = 0;
	int total = 0;
	int max = atoi(argv[2]);

	FILE* fp = fopen(argv[1], "r");
	node* head = NULL;

	while(fscanf(fp, "%d", &temp) == 1)
	{
		head = add_to_tree(head, temp);
	}

	while(option != -1)
	{

        printf("Enter '1' to add a number to the tree\n");
        printf("Enter '2' to print the totals for each number\n");
        printf("Enter '-1' to terminate the program\n");

	printf("Enter your choice:");
	scanf("%d", &option);

	if(option == 1)
	{
		printf("Enter a number(0-%d) to add to the tree:", max);
		scanf("%d", &temp);

		while(temp < 0 || temp > max)
		{

			printf("Wrong input\n");
			printf("Enter a number(0-10) to add to the tree:");
			scanf("%d", &temp);
		}
		
		add_to_tree(head, temp);
	}
	else if(option == 2)
	{
		total = print_totals(head, 0);
		printf("Total = %d\n", total);
	}
        else if(option == -1)
	{
		printf("Program terminated\n");
	}
	else
	{
		printf("Wrong input\n");
	}
	}
return 0;
}
node* add_to_tree(node* head, int number)
{
        if(head == NULL)
        {
                head = malloc(sizeof(node));
                head -> num = number;
		head -> count = 1;
                head -> left = NULL;
                head -> right = NULL;
        }
        else if(number < head -> num)
        {
                head -> left = add_to_tree(head -> left, number);
        }
        else if(number > head -> num)
        {
                head -> right = add_to_tree(head -> right, number);
        }
	else
	{
		head -> count ++;
	}

return head;
}


int print_totals(node* head, int count)
{
        if(head != NULL)
        {
        count = print_totals(head -> left, count);
        printf("There are %d occurances of the number %d\n", head -> count, head -> num);
	count = print_totals(head -> right, count) + head -> count; 
        }

return count;
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




