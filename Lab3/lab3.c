//Wade Tobin
//Lab 3
//Section E
//wmtb75
#include <stdio.h>
#include <stdlib.h>

typedef struct Player{
	char Player_Name[50];
	int singles;
	int doubles;
	int triples;
	int Homeruns;
}player;

//prototype fuctions
player* read_binary_file(char* input_file, int num_players);
int Check_User_Search(int number);
void Search_Players(player* players, int num_players, int number);


int main(int argc, char* argv[])
{
	char* filename;
	player* ptr;
	int num;

	if(argc != 3)
	{
		printf("Error, insufficent argument.\n");
	return 0;
	}

	int num_players = atoi(argv[1]);
	filename = argv[2];

	ptr = read_binary_file(filename, num_players);

//	printf("Player Name = %s\n", (ptr) -> Player_Name);
//	printf("Singles = %d\n", (ptr) -> singles);
//	printf("Doubles = %d\n", (ptr) -> doubles);
//	printf("Triples = %d\n", (ptr) -> triples);
//	printf("Homeruns = %d", (ptr) -> Homeruns);

	num = -1;

	while(Check_User_Search(num)== -1)
	{
	printf("Enter a Number.\n");
	scanf("%d", &num);
	}

	Search_Players(ptr, num_players, num);

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
return ptr3;
}

void Search_Players(player* players, int num_players, int number)
{
	int i;
	int j;

	if(players == NULL || num_players <= 0 )
	{
		printf("Error.");
	}
		else
		printf("#### Search Results ####\n");
		{
			for(i = 0; i < num_players; i++)
			{
				if((players + i) -> singles == number) 
				{	
					printf("%s has %d Singles!\n", (players + i) -> Player_Name, (players + i) -> singles);
						j++;
				}
				if((players + i) -> doubles == number)
				{
					printf("%s has %d Doubles!\n", (players + i) -> Player_Name, (players + i) -> doubles);
						j++;
				}
				if((players + i) -> triples == number)
				{
					printf("%s has %d Triples!\n", (players + i) -> Player_Name, (players + i) -> triples);
						j++;
				}
				if((players + i) -> Homeruns == number)
				{
					printf("%s has %d Homeruns!\n", (players + i) -> Player_Name, (players + i) -> Homeruns);
						j++;
				} 
			}
		}
	printf("This search has a total of %d matching criteria!\n", j);
}
int Check_User_Search(int number)
{

	if( (number >= 0)&&(number <=50)){
		return number;
	}
	else
	{
		return -1;
	}

}
