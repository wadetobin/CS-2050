//Wade Tobin
//Lab 7
//Section E
//wmtb75
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 25


typedef struct node{
        char* word;
        struct node *next;
} Node;

Node* add_to_front(char* word, Node* head);
void print(Node* head);
void menu();
Node* remove_from_front(Node* head);
Node* add_to_back(Node* head, char* word);
Node* remove_from_back(Node* head);

int main(void)
{
	int choice = 0;
	char* word = malloc(sizeof(char)*SIZE);
	Node* head = NULL;
	Node* undo = NULL;

	while(choice != -1)
	{
		menu();

		scanf("%d", &choice);
     
		switch (choice)
		{
			case 1: 
			{
				printf("Enter a word to add to the document:");
				scanf("%s", word);
				head = add_to_back(head, word);
				print(head);
				break;
			}
			case 2:
			{
				Node* current = head;
				if(current == NULL)
				{
					printf("There is nothing to undo at the moment\n");
				}
				else
				{
					while(current -> next != NULL)
					{
						current = current -> next;
					}
				
					undo = add_to_front(current -> word, undo);
					head = remove_from_back(head);
				}
				print(head);
				break;
			}
			case 3:
			{
				if(undo== NULL)
				{
					 printf("There is nother to redo at the moment!\n");
				}
				else
				{
					head = add_to_back(head, undo -> word);
					undo = remove_from_front(undo);
				}
				print(head);
				break;
			}
			case -1:
			{
			break;
			}

			default:
			{
				printf("Invalid input!\n");
			}

		}
	}

	printf("Bye\n");

return 0;
}

Node* add_to_front(char* word, Node* head)
{
	Node* new = malloc(sizeof(Node));
	new -> word = malloc(sizeof(char)*SIZE);
	memcpy(new -> word, word, SIZE);
	new -> next = head;

	return new;
}

void print(Node* head)
{
	Node* current = head;

	while(current != NULL)
	{
		printf("%s ",current -> word);
		current = current -> next;
	}
	printf("\n");
}

void menu()
{
	printf("Enter '1' to add a word to the sentence\n");
	printf("Enter '2' to undo\n");
	printf("Enter '3' to redo\n");
	printf("Enter '-1' to exit:\n");
}

Node* remove_from_front(Node* head)
{
	if(head == NULL)
	{
		return NULL;
	}
	
	else if(head->next == NULL)
	{
		free(head -> word);
		free(head);
		return NULL;
	}
	else
	{
		Node* current = head;
		current = head -> next;
		free(head -> word);
		free(head);
		return current;
	}
}


Node* add_to_back(Node* head, char* word)
{
	if(head == NULL)
	{
	head = malloc(sizeof(Node));
	head -> word = malloc(sizeof(char)*SIZE);
	memcpy(head -> word, word, SIZE);
	
	return head;
        }

	Node* current = head;

	while(current -> next != NULL)
	{
		current = current ->next;
	}

	current -> next = malloc(sizeof(Node));
	current = current -> next;
	current -> word = malloc(sizeof(char)*SIZE);
	
	memcpy(current -> word, word, SIZE);

	return head;
}

Node* remove_from_back(Node* head)
{
        if(head == NULL)
	{
		return NULL;
	}
	else if(head -> next == NULL)
	{
		free(head -> word);
		free(head);
		
		return NULL;
	}
	else
	{
		Node* current = head;
		Node* previous = NULL;
		
		while(current -> next != NULL)
		{
			previous = current;
			current = current -> next;
                }

		previous -> next = NULL;
		free(current -> word);
		free(current);

	return head;
        }
}


