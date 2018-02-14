#include <stdlib.h>
#include <stdio.h>


typedef struct Player{
        char Player_Name[50];
        int Homeruns;
        int Triples;
	int Doubles;
}player;

player* read_binary_file(char* input_file);

int main(int argc, char* argv[])
{

        char* filename;
	player* ptr3;

        if(argc != 2)
        {
                printf("Error, not enough sufficent argument.\n");

        return 0;
        }

	filename = argv[1];	

	ptr3 =  read_binary_file(filename);

	printf("Player Name = %s\n", (ptr3) -> Player_Name);
	printf("Homeruns = %d\n", (ptr3 ) -> Homeruns);
	printf("Doubles = %d\n", (ptr3) -> Doubles);
        printf("Triples = %d", (ptr3) -> Triples);

return 0;
}

player* read_binary_file(char* input_file)
{
	FILE *ptr;
	player* ptr2;
	int i;	
	
	ptr2 = malloc(sizeof(player)); 

	ptr = fopen(input_file,  "rb"); 


	if(ptr == NULL)
	{
		printf("Error, could not open.\n");
		
		return NULL;
	}
		else
		{
			(fread(ptr2, sizeof(player), 1, ptr));
		}
	fclose(ptr);

return ptr2;
} 

