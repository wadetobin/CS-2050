//Wade Tobin
//wmtb75
//Lab 6
//Section E
#include <stdio.h>
#include <stdlib.h>

typedef struct list_node{
	int num;
	struct list_node *next;
} node;

node* add_node(node *head, int *number);
node* delete_node(node *head);
int sum_list(node *head);
void free_list(node *head);

int main()
{

	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	//Initialize to NULL, since we have an empty list.
	
	node *head = NULL;
	int i = 0;
	
	//add 10 nodes to list
	for(i = 0; i < 10; i++)
	{
		head = add_node(head, (array + i));
	}
	//print sum
	printf("\n The sum of the list is %d", sum_list(head));

	//loop, delete each node, tries to delete 10 nodes
	for(i = 0; i < 10; i++)
	{
		head = delete_node(head);
		printf("\n The sum of the list is %d", sum_list(head));
	}

	free_list(head);

	head = add_node(head, (array + 9));

	printf("\n The sum of the list is %d", sum_list(head));

	free_list(head);

	head = NULL;

	printf("\n The sum of the list is %d", sum_list(head));

return 0;
}

node* add_node(node *head, int *number)
{
	node* current;

	current = head;

	if(head == NULL)
	{
		head = malloc(sizeof(node));
		head -> num = *number;

	return head;
	}
	else
	{
		while(current -> next != NULL)
		{
			current = current -> next;
		}

		current -> next = malloc(sizeof(node));
		current -> next -> num = *number;
	}
	return head;
}

node* delete_node(node *head)
{
	node* current;
	current = head;
	node* previous = NULL;

	if(current == NULL)
	{
		return NULL;
	}
	else if(current -> next == NULL)
	{
		free(head);
		head = NULL;
		return head;
	}
	else
	{
		while(current -> next != NULL)
		{
			previous = current;
			current = current -> next;
		}
		free(current);
		previous -> next = NULL;
	}

	return head;
}

int sum_list(node *head)
{

        node* current;

        current = head;

        int sum = 0;

        while(current != NULL)
        {  
            	sum += (current -> num);
	    	current = current -> next;
        }


return sum;
}

void free_list(node *head)
{
        node* current;

        current = head;

	if(current != NULL)
	{
        	if(current -> next != NULL)
        	{
                	free_list(current -> next);
       		}

        	free(current);
	}
}
