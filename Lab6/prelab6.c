#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
int data;
struct Node * nextPtr;
}node;

node* readFile(FILE* fp, node* head);
void printList(node* head);
void freeList(node* head);

int main(int argc, char*  argv[])
{

	char* filename;
	FILE* fp;


	if(argc != 2)
        {
                printf("Error, insufficent argument.\n");

        return 0;
        }

        filename = argv[1];

	fp = fopen(filename, "r");
	
	node* head = NULL;
	
	head = readFile(fp, head);
      

	printList(head);

	freeList(head);

fclose(fp);

return 0;
}
node* readFile(FILE* fp, node* head)
{
        node* current;

        head = malloc(sizeof(node));

	current = head;

        if(fp == NULL)
        {
                printf("Error, oould not open.\n");

                return 0;
        }
                else
                {

                        fscanf(fp, "%d", &(current -> data));
			while(feof(fp)!=1)
                        {
			current -> nextPtr = malloc(sizeof(node));
			current = current -> nextPtr;
			fscanf(fp, "%d", &(current -> data));
			}
                }

return head;
}

void printList(node* head)
{
	node* current;

	current = head;

	int i = 1;

        while(current -> nextPtr != NULL)
        {
                printf("Node %d: %d\n", i, current -> data);
		i++;
		current = current -> nextPtr;
        }
}
void freeList(node* head)
{
	node* current;

	current = head;

	if(current -> nextPtr != NULL)
	{
		freeList(current -> nextPtr);
	}	
	
	free(current);
}

