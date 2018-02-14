#include <stdio.h>
#include <stdlib.h>


void min_max(double*, int , FILE*);
double* read_file(FILE* , int);


int main (void)
{
	FILE *ptr2;
	FILE *ptr;
	int  i= 0;	
	double* array;


	if((ptr = fopen("input.txt", "r")) == NULL)
	{
	printf("File could not be opened\n");
	}
	
	if((ptr2 = fopen("output.txt", "w")) == NULL)
	{
	printf("Error\n");
	}


	array = read_file(ptr,10);
	//printf("%lf\n",*array);

	min_max(array, 10, ptr2);

	fclose(ptr);
	fclose(ptr2);
}

void min_max(double* array, int length, FILE* outputfile)
{
	double max = *array, min = *array;
	int i;


	for(i=1; i < length; i++)
	{
		if(max < *(array + i))
		{
		max = *(array + i);
		}

		if(min > *(array +i))
		{
		min = *(array +i);
		}
	}
	
	fprintf(outputfile, "Max is %lf\n", max);
	fprintf(outputfile, "Min is %lf", min);

}

double* read_file(FILE* file, int length)
{
	double* array = malloc(length * sizeof(double));
	int i = 0;

	for(i=0; i < length; i++)
	{

	fscanf(file, "%lf", array + i);
	//printf("%lf\n",*(array+i));
	}

	return array;
}

