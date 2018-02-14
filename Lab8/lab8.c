#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROLL 6

typedef struct Node {
        int spaceID;
        int backValue;
        struct Node* next;
        struct Node* prev;
}node;

node* add_node(node* head, int spaceID, int backValue);
void play_game(node* head);
node* player_turn(node* user, int playerID);
void free_list(node* head);
void link_back_to_front(node* head);

int main(int argc, char** argv) 
{
	srand(time(NULL));	

	if(argc != 2)
	{
		printf("Insufficent Argument");
		return 0;
	}

	FILE* fp;
	fp = fopen(argv[1], "r");
	int num1 =0;
	int num2 = 0;

	node* head = NULL;
	
	if(fp == NULL)
	{
		printf("Cannont open file\n");
		return 0;
	}

	while(fscanf(fp, "%d %d", &num1, &num2) == 2)
	{
		head = add_node(head, num1, num2);
	}

	node* current = head;
	
	while(current != NULL)
	{
		printf("%d -- %d", current -> spaceID, current -> backValue);
		current = current -> next;
	}
	
	printf("NULL\n");
	link_back_to_front(head);

	play_game(head);
	
	head -> prev -> next = NULL;
	
	free_list(head);



        return 0;
}

node* add_node(node* head, int spaceID, int backValue) 
{
	if(head == NULL)
	{
		head = malloc(sizeof(node));
		head -> spaceID = spaceID;
		head -> backValue = backValue;
		return head;
	}

	node* current = head;

	while(current -> next != NULL)
	{
		current = current -> next;
	}

	current -> next = malloc(sizeof(node));
	//current -> next -> spaceId = spaceID;
	current -> next -> backValue = backValue;
 	current -> next -> prev = current;
	current -> next -> next = NULL;

        return head;
}

void link_back_to_front(node* head) 
{
	node* tail = head;
	
	while(tail -> next != NULL)
	{
 		tail = tail -> next;
	}
	
	tail -> next = head;
	head -> prev = tail;	
}

void play_game(node* head) 
{
	node* player1 = head;
	node* player2 = head;

	int option = 0;
	int round = 1;

	while(player1 -> next -> spaceID != 0 || player2 -> next -> spaceID != 0)
	{
		printf("Enter 1 to play the next turn:");
		scanf("%d", &option);

		printf("===============================\n");
		printf("Starting turn %d\n", round);
		printf("===============================\n");

		player1 = player_turn(player1, 1);
		
		if(player1 -> next -> spaceID != 0)
		{
			player2 = player_turn(player2, 2);

		}
		printf("After turn %d, player 1 is on space %d and player2 is on space %d", round, player1 -> spaceID, player2 -> spaceID);
}
return;		
}

node* player_turn(node* user, int playerID) 
{
	int roll = rand()%MAX_ROLL +1;
	int i = 0;

	printf("player %d rolled a %d\n", playerID, roll);
	for(i = 0; i < roll; i++)
	{
		user = user -> next;
	}

	if(user -> backValue > 0)
	{
		printf("user %d has moved forward %d spaces!\n", playerID, user -> backValue);
		
		if(user -> next -> spaceID != 0)
		{
			int k = user -> backValue;
			for(i = 0; i < k; i++)
			{
				user = user -> next;
			}
		}
	}
	else
	{
		printf("user %d has moved back %d spaces!\n", playerID, user -> backValue);
		
		if(user -> next ->spaceID != 0)
		{
			int k = user -> backValue;
			for(i = 0; i < k; i++)
			{
				user = user -> prev;
			}
		}
	}
	
        return user;
}

void free_list(node* head) 
{
	node* current = head;

	if(current -> next != NULL)
	{
		free_list(current -> next);
	}
	free(current);
}

