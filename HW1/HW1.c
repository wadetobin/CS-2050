//Wade Tobin
//HW 1
//wmtb75
//Section E
#include <stdio.h>
#include <stdlib.h>

typedef struct player{
	char Fname[25];
	char Lname[25];
	int Singles;
	int Doubles;
	int Triples;
	int Homeruns;
	int At_Bats;
	float Slugging_Percentage;
}Player;

// prototype fuctions
void read_from_file(char* filename, Player* players, int index, int size);
void calculate_slugging(Player* players, int size);
void sort_array(Player* players, int size);
void write_to_file(char* filename, Player* players, int size);


int main( int argc, char** argv)
{
	char* filename;
	int index = 0;
	int size = 0;
	
	
	if(argc != 6) 
	{ 
		printf("Error, insufficent argument.\n");	
		
	return 0;
	}	
	
	size = atoi(argv[1]);
	

	Player* players = malloc(sizeof(Player)* size);

	filename = argv[2];
	read_from_file(filename, players, index, size);//calls read to file
	index += size/3;
	
	filename = argv[3];
	read_from_file(filename, players, index, size);//calls read to file
	index += size/3;
	
	filename = argv[4];
	read_from_file(filename, players, index, size);//calls read to file

	calculate_slugging(players, size);//calls calculate_slugging

	sort_array(players, size);//calls sort_array

	filename = argv[5]; 
	write_to_file(filename, players, size);//calls write_to_file



return 0;

}

void read_from_file(char* filename, Player* players, int index, int size) //reading whats in the files
{
	int i = 0;
	FILE *ptr;
	
	if((ptr = fopen(filename, "r")) == NULL)
	{
		printf("File could not be opened\n");// prints an error if file couldn't be opened
	}

	for(i=0; i < size/3; i++)
	{
		fscanf(ptr,"%s %s %d %d %d %d %d", (players + index + i) -> Fname, (players + index + i) -> Lname, &(players + index + i) -> Singles, &(players + index + i) -> Doubles, &(players + index + i) -> Triples, &(players + index + i) -> Homeruns, &(players + index + i) -> At_Bats); //scans the names and numbers of each of the input files 
	}


	fclose(ptr);
}

void calculate_slugging(Player* players, int size) //calculates the slugging percentage
{
	int i;	

	for(i = 0; i < size; i++)
	{
		(players + i) -> Slugging_Percentage = (float)((players + i) -> Singles + ((players + i) -> Doubles)*2 + ((players + i) -> Triples)*3 + ((players + i) -> Homeruns)*4) /(float) ((players + i) -> At_Bats); //takes all the stats of input files, put them into a formula to get the slugging percentage
	} 

}

void sort_array(Player* players, int size)// sorts all of the players in decreasing order by their slugging percentage
{

	int i, j;
	Player temp;	

	for(i = 0; i < size-1; i++)// bubble sort
	{
		for(j = 0; j < size - i - 1; j++)
		{
			if((players + j) -> Slugging_Percentage < (players + j + 1) -> Slugging_Percentage)
			{
				temp = *(players + j);
				*(players + j) = *(players + j + 1);
				*(players + j + 1) = temp;
			}
		}
	}
	
}

void write_to_file(char* filename, Player* players, int size)// opens filename and writes to it
{
	int i = 0;
        FILE *ptr;

        if((ptr = fopen(filename, "w")) == NULL)
        {
                printf("File could not be opened\n");// sends error if file couldn't be opened
        }else{

        	for(i=0; i < size; i++)
        	{
                fprintf(ptr,"%s %s %d %d %d %d %d %f\n", (players + i) -> Fname, (players + i) -> Lname, (players + i) -> Singles, (players + i) -> Doubles, (players + i) -> Triples, (players + i) -> Homeruns, (players + i) -> At_Bats, (players + i) -> Slugging_Percentage);//prints out the data from the input files by their order
        	}	
	}

        fclose(ptr);
}



