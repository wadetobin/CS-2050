#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
	struct Node* next;
	struct Node* prev;
	int data;
}node;

node* add_node(node* head, int num);
void print_list_forward(node* head);
void print_list_backward(node* head);
node* delete_from_list(node* head, int num);
void free_list(node* head);

int main()
{

	
	int number = 0;
	node* head = NULL;
	int option = 0;
	int number2 = 0;

	while(option != -1)
	{
		printf("To add a number the list enter '1': \n");
		printf("To print the list enter '2': \n");
		printf("To print the list backwards enter '3': \n");
		printf("To delete a number enter '4' (assume there are no duplicates): \n");
		printf("Enter your choice(1-3): to exit enter '-1': \n");
		scanf("%d", &option);
		
		while((option < 1 || option > 4) && option != -1)
		{
			printf("Wrong entry\n");
			scanf("%d", &option);
		}
		
		switch(option)
		{
			case 1:
			printf("Enter the number you would like to add to the list: ");
			scanf("%d", &number2);
			head = add_node(head, number2);
			break;		
	
			case 2:
			print_list_forward(head);
			break;
		
			case 3:
			print_list_backward(head);
			break;

			case 4:
			printf("Enter a number to delete from list: \n");
			scanf("%d", &number);
			delete_from_list(head, number);
			break;
			
			default:
			printf("Exited\n");
		}

	}

	free_list(head);

return 0;
}

node* add_node(node* head, int num)
{
	if(head == NULL)
	{
		head = malloc(sizeof(node));
		head -> data = num;
		return head;

	}

	node* current = head;	

	while(current -> next != NULL)
	{
		current = current -> next;
	}

	current -> next = malloc(sizeof(node));

	current -> next -> data = num;

	current -> next -> prev = current;
	
	return head;
}

void print_list_forward(node* head)
{
	node* current = head;

	printf("printing list forward\n");

	while(current != NULL)
	{
		if(current -> next != NULL)
		{
			printf("%d-->", current -> data);
			current = current -> next;
		}
		else
		{
			printf("%d", current -> data);
			current = current -> next;
		}
	}
	printf("\n");
}

void print_list_backward(node* head)
{
	node* current = head;

	printf("printing list backward\n");

	while(current -> next != NULL)
	{
		current = current -> next;
	}
	while(current != NULL)
	{
		if(current -> prev != NULL)
		{	
			printf("%d-->", current -> data);
			current = current -> prev;
		}
		else
		{
			printf("%d", current -> data);
			current = current -> prev;
		}
	}
	printf("\n");
}

node* delete_from_list(node* head, int num)
{
	node* current = head;
	
	while(current != NULL)
	{
		if(current -> data == num)
		{
			if(current -> prev == NULL)
			{
				node* temp = current -> next;
				if(current->next->next != NULL){
					current ->next ->next ->prev =  current;
				}
				current -> data = current ->next ->data;
				current -> next = current ->next ->next;
				free(temp);
				current = current->next;
			}
			else if(current -> next == NULL)
			{
				current -> prev -> next = NULL;
				free(current);
				current = NULL;
			}
			else
			{
			current -> prev -> next = current -> next;
			current -> next -> prev = current -> prev;
			node* tempi = current -> next;
			free(current);
			current = tempi;
			}
		}
		else
		{
			current = current -> next;
		}
	}
	return head;
}

void free_list(node* head)
{
	node* current = head;

	if(current != NULL)
	{
		free_list(current -> next);
		free(current);
	}
}	
