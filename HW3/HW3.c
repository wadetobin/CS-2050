#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 200
#define MAXCARPRICE 1000000

typedef struct node{
	char make[25];
	char model[25];
	int price;
	int year;
	char color[25];
	char type[25];
	int mileage;
	struct node* left;
	struct node* right;
} Node;

Node* get_cars(char* filename);
Node* add_to_tree(Node* head, Node* new);
void search_tree(Node* root, int year, int price, int* count);
int helper(Node* root, int year, int price);
int filter(char* ptr, char** ptr2, int size);
int bonus(Node* root, char* color, char* make, int price);
void freetree(Node* root);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Not enough arguments.");
	}

	Node* head = NULL;

	head = get_cars(argv[1]);

	int option = 0;
	int year = 0;
	int price = 0;
	int* count = malloc(sizeof(int));
	*count = 0;
	char* color = malloc(sizeof(char)* 25);
	char* make = malloc(sizeof(char)* 25);

	while(option != -1)
	{
		printf("To search for a vehicle newer than a specific year enter '1'\n");
		printf("To search for a vehicle that costs less than a certain price enter '2'\n");
		printf("To search for a vehicle with both of the above parameters enter '3'\n");
		printf("To search for a vehicle with color, make, price enter '4'\n");
		printf("To exit enter '-1'\n");
		scanf("%d", &option);

		switch(option)
		{
			case 1:
			{
				printf("Enter the year you would like the vehicles to be newer than: \n");
				scanf("%d", &year);
				search_tree(head, year, 0, count);
				break;
			}
			case 2:
			{
				printf("Enter the price you would like the vehicles to be less than: \n");
                                scanf("%d", &price);
                                search_tree(head, 0, price, count);
                                break;
			}
			case 3:
			{
				printf("Enter the year you would like the vehicles to be newer than: \n");
                                scanf("%d", &year);
			
				printf("Enter the price you would like the vehicles to be less than: \n");
                                scanf("%d", &price);
                                search_tree(head, year, price, count);
                                break;
			}
			case 4:
			{
				printf("Enter the price you would like the vehicle to be less than: \n");
				scanf("%d", &price);
				
				printf("Enter the color you would like the vehicle to be: \n");
				scanf("%s", color);
		
				printf("Enter the make you would like the vehicle to be: \n");
				scanf("%s", make);
				printf("%d Cars found\n", bonus(head, color, make, price));
			} 
			case -1:
			{
				break;
			}
			default:
			{
				printf("Invalid input, try again.");
			}
		}
	
	}
free(color);
free(make);
free(count);
freetree(head);

return 0;

}

Node* get_cars(char* filename)
{
	FILE* fp;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;

	fp = fopen(filename, "r");
	fp2 = fopen("makes.txt", "r");
	fp3 = fopen("types.txt", "r");
	fp4 = fopen("colors.txt", "r");

	Node* head = NULL;	

	if(fp == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL)
	{
		printf("Cannot open file.\n");
		return NULL;
	}
	
	char* temp = malloc(sizeof(char)* MAXLINELENGTH);
	char* a;
	char** makes = malloc(sizeof(char*)* 18);
	char** types = malloc(sizeof(char*)* 4);
	char** colors = malloc(sizeof(char*)* 8);
	

	int i;

	for(i = 0; i < 18; i++)
	{
		*(makes + i) = malloc(sizeof(char)* 25);
		fscanf(fp2, "%s", *(makes + i));
	}

        for(i = 0; i < 4; i++)
        {
                *(types + i) = malloc(sizeof(char)* 25);
                fscanf(fp3, "%s", *(types + i));
        }

        for(i = 0; i < 8; i++)
        {
                *(colors + i) = malloc(sizeof(char)* 25);
                fscanf(fp4, "%s", *(colors + i));
        }

	while(fscanf(fp, "%s", temp) == 1)
	{
		a = strtok(temp, "|");
		Node* new = malloc(sizeof(Node));

		while(a != NULL)
		{
			if(strcmp(a, "mileage") == 0)
			{
				a = strtok(NULL, "|");
				(new -> mileage = atoi(a));
			}
			if(strcmp(a, "color") == 0)
                        {
                                a = strtok(NULL, "|");
                                strcpy(new -> color, a);
                        }
			if(strcmp(a, "price") == 0)
                        {
                                a = strtok(NULL, "|");
                                (new -> price = atoi(a));
                        }
                        if(strcmp(a, "type") == 0)
                        {
                                a = strtok(NULL, "|");
                                strcpy(new -> type, a);
                        }
                        if(strcmp(a, "year") == 0)
                        {
                                a = strtok(NULL, "|");
                                (new -> year = atoi(a));
                        }
                        if(strcmp(a, "make") == 0)
                        {
                                a = strtok(NULL, "|");
                                strcpy(new -> make, a);
                        }
                        if(strcmp(a, "model") == 0)
                        {
                                a = strtok(NULL, "|");
                                strcpy(new -> model, a);
                        }
			a=strtok(NULL,"|");
		}
	if((new -> mileage >= 0) && filter(new -> make, makes, 18) && filter(new -> color, colors, 8) && filter(new -> type, types, 4) && (new-> price < MAXCARPRICE) && (new -> year != 0) && (new -> price != 0))
	{
		head = add_to_tree(head, new); 
	}
	else
	{
		free(new);
	}
	}	
        for(i = 0; i < 18; i++)
        {
                free(*(makes + i));
        }
	free(makes);

        for(i = 0; i < 4; i++)
        {
                free(*(types + i));
        }
	free(types);

        for(i = 0; i < 8; i++)
        {
                free(*(colors + i));
        }
	free(colors);

free(temp);
fclose(fp);
fclose(fp2);
fclose(fp3);
fclose(fp4);

return head;
}

Node* add_to_tree(Node* head, Node* new)
{
        if(head == NULL)
        {
                head = new;
        }
        else if(new -> price < head -> price)
        {
                head -> left = add_to_tree(head -> left, new);
        }
        else
        {
                head -> right = add_to_tree(head -> right, new);
        }
return head;

}

void search_tree(Node* root, int year, int price, int* count)
{
	if(root != NULL)
	{
		*count = helper(root, year, price);
		printf("There were %d cars found\n", *count);
	}		
}

int helper(Node* root, int year, int price)
{
	int count = 0;

	if(root != NULL)
	{
		if(year != 0 && price != 0)
		{
			if(root -> year > year && root -> price < price)
			{
				printf("%d %s %s that cost $%d\n", root -> year, root -> make, root -> model, root-> price);
				count++;
			}
		}
		else if(year != 0 && price == 0)
		{
			if(root -> year > year)
                        {
                                printf("%d %s %s that cost $%d\n", root -> year, root -> make, root -> model, root-> price);
                        	count++;
			}
		}
		else if(year == 0 && price != 0)
		{
			if(root -> price < price)
                        {
                                printf("%d %s %s that cost $%d\n", root -> year, root -> make, root -> model, root-> price);
                        	count++;
			}
		}
		
		count += helper(root -> left, year, price);
		count += helper(root -> right, year, price);
	}
	return count;
}

int filter(char* ptr, char** ptr2, int size)
{
	int i;	
	
	for(i = 0; i < size; i++)
	{
		if(strcmp(ptr, *(ptr2 + i)) == 0)
		return 1;	
	}
	
return 0;
}

int bonus(Node* root, char* color, char* make, int price)
{
        int count = 0;

        if(root != NULL)
        {
		if(root -> price < price && (strcmp(color, root -> color) == 0) && (strcmp(make, root -> make) == 0))
                        {
                                printf("%d %s %s %s that cost $%d\n", root -> year, root -> make, root -> model, root -> color, root-> price);
                                count++;
                        }
		
                count += bonus(root -> left, color, make, price);
                count += bonus(root -> right, color, make, price);
        }
        return count;
}

void freetree(Node* root)
{
	if(root != NULL)
	{
		freetree(root -> left);
		freetree(root -> right);
		free(root);
	}
}
