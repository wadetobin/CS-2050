#include <stdio.h>
#include <stdlib.h>

typedef struct Player{
	char Player_Name[50];
	int singles;
	int doubles;
	int triples;
	int Homeruns;
}player;

player* read_binary_file(char* , int );
void selection_sort(player* array, int size);
void print_Array(player* array, int size);

int main(int argc, char* argv[])
{
	char* filename;
	player* ptr;
	

	if(argc != 3)
	{ 
		printf("Error.\n");
	return 0;
	}

	filename = argv[2];
	int num_players = atoi(argv[1]);
	
	ptr = read_binary_file(filename, num_players);

	selection_sort(ptr, num_players);

	print_Array(ptr, num_players);
return 0;
}



player* read_binary_file(char* input_file, int num_players)
{
        FILE *ptr2;
        player* ptr3;

        ptr3 = malloc(sizeof(player)*num_players);

        ptr2 =fopen(input_file, "rb");

        if(ptr2 == NULL)
        {
                printf("Error, oould not open.\n");

                return 0;
        }
                else
                {
                        
                                (fread(ptr3, sizeof(player), num_players, ptr2));
                        
                }
fclose(ptr2);

return (ptr3);
}
void selection_sort(player* array, int size)
{
	int i, j;
	int n = size;
	player temp;

	for(j=0;j < n-1; j++)
	{
		int iMin = j;
	
			for(i = j + 1; i < n; i++)
			{
				if(((array + i) -> Homeruns) > ((array + iMin) -> Homeruns))
					{ 
						iMin = i;
					}
			}
	if(iMin != j)
	{
		temp = *(array + j);
		*(array + j) = *(array + iMin);
		*(array + iMin) = temp;
	}
	}
	printf("Successfully sorted %d players.\n", size);

}
void print_Array(player* array, int size)
{

	int i;

	for(i = 0; i < size; i++)
	{
		printf("%-25s   Homeruns = %d\n", (array + i) -> Player_Name, (array + i) -> Homeruns); 
	}
}

