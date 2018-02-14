#include <stdio.h>
#include <stdlib.h>

typedef struct node{
        int num;
        struct node *next;
} Node;

Node* push(int number, Node* head);
void print(Node* head);
void menu();
Node* pop(Node* head);
void freeList(Node* head);

int main()
{
	int option = 0;
	Node* head = NULL;
	int number;

	while(option != -1)
	{

	print(head);

	menu();

	scanf("%d", &option);

	if(option == 1)
	{
		printf("Enter a number to push onto the stack:\n");
		scanf("%d", &number);
		head = push(number, head);
	}
	else if(option == 2)
	{
		head = pop(head);
	}
	else if(option != -1)
	{
		printf("Invalid input\n");
	}
	else{}
	}
	print(head);

	freeList(head);
return 0;
}

Node* push(int number, Node* head)
{
	Node* current;

	current = malloc(sizeof(Node));
	current -> num = number;
	current -> next = head;

return current;
}

void print(Node* head)
{
	Node* current;
	current = head;

	if(current != NULL)
	{
		while(current != NULL)
		{
			printf("%d -->", current -> num);
			current = current -> next;
		}
		printf("NULL\n");
	}
	else
	{
		printf("The stack is empty.\n");
	}


}

void menu()
{

	printf("Enter '1' to push a node onto the list.\n");
	printf("Enter '2' to pop a node off of the list.\n");

	printf("Enter '-1' to exit:\n");


}

Node* pop(Node* pop)
{
	Node* current;
	
	if(pop == NULL)
	{
		return NULL;
	}
	else if(pop -> next == NULL)
	{
		free(pop);
		return NULL;
	}
	else
	{
		current = pop -> next;
		free(pop);
		return current;
	}
}

void freeList(Node* head)
{
        Node* current;

        current = head;

        if(current -> next != NULL)
        {
                freeList(current -> next);
        }

        free(current);
}


