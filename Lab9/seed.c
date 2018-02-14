#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main(int argc, char* argv[]){

	srand(time(NULL));
	int max=0;
	int size=0;
	int i=0;

	if(argc != 4)
	{
		printf("argument count is wrong!\n");
        return 0;
	}
	
	FILE* fp = fopen(argv[1], "w");

	max = atoi(argv[3]);
	size = atoi(argv[2]);
    
	for (i=0; i<size; i++)
	{
		fprintf(fp,"%d\n",(rand()%(max+1)));
	}
    
    fclose(fp);
	

    return 0;
}
