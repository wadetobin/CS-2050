//Wade Tobin
//Lab 4
//wmtb75
//Section E
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int* readfile(char* filename, int size);
void bubble_sort(int* array, int size);
void selection_sort(int* array, int size);
void insertion_sort(int* array, int size);
double calculate_time(clock_t begin, clock_t end);


int main(int argc, char* argv[])
{
        char* filename;
        int* ptr;
	float time;
	clock_t begin, end;


        if(argc != 3)
        {
                printf("Error, insufficent argument.\n");
        
	return 0;
        }

        int size = atoi(argv[1]);
        filename = argv[2];

      	ptr = readfile(filename, size);

	int* arr = malloc(sizeof(int)*size);
	int* arr2 = malloc(sizeof(int)*size);
	int* arr3 = malloc(sizeof(int)*size);
	
	memcpy(arr, ptr, sizeof(int)*size);
	memcpy(arr2, ptr, sizeof(int)*size);
	memcpy(arr3, ptr, sizeof(int)*size);

	int i;	
	int choice;
	do{
		printf("Enter '1' for a bubble sort\n");
		printf("Enter '2' for a selection sort\n");
		printf("Enter '3' for an insertion sort\n");
		printf("Enter -1 to exit program\n");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: begin = clock();
				bubble_sort(arr, size);
				for(i = 0; i < 10; i++)
			        {
               				 printf("%d\n", *(arr + i));
       				}
				end = clock();
				time = calculate_time(begin, end);
					printf("Bubble sort on %d numbers took %f seconds\n", size, time);
				break;
			case 2: begin = clock();
				selection_sort(arr2, size);
				for(i = 0; i < 10; i++)
			        {
                			printf("%d\n", *(arr2 + i));
        			}
				end = clock();
				time = calculate_time(begin, end);
					 printf("Selection sort on %d numbers took %f seconds\n", size, time);
				break;
			case 3: begin = clock();
				insertion_sort(arr3, size);
				for(i = 0; i < 10; i++)
			        {
                			printf("%d\n", *(arr3 + i));
        			}
				end = clock();
				time = calculate_time(begin, end);
					 printf("Insertion sort on %d numbers took %f seconds\n", size, time);
				break;
			case -1: printf("Program quitting.\n");
				break;
			default: printf("Invalid choice.\n");
				break;
		}
	} while(choice != -1);

free(ptr);
free(arr);
free(arr2);
free(arr3);
return 0;
}


int* readfile(char* filename, int size)
{
        FILE *ptr2;
        int* ptr3;

        ptr3 = malloc(sizeof(int)*size);

        ptr2 =fopen(filename, "r");

        if(ptr2 == NULL)
        {
                printf("Error, oould not open.\n");

                return 0;
        }
                else
                {
			int i;
			for(i=0;i<size;i++)
                               fscanf(ptr2,"%d",(ptr3+i));
		}

	fclose(ptr2);

return ptr3;
}

void selection_sort(int* array, int size)
{
        int i, j;
        int temp;

        for(j=0;j < size - 1; j++)
        {
                int Min = j;

                        for(i = j + 1; i < size; i++)
                        {
                                if(*(array + i) < *(array + Min))
                                        {
                                                Min = i;
                                        }
                        }
        	if(Min != j)
        	{
                	temp = *(array + j);
                	*(array + j) = *(array + Min);
                	*(array + Min) = temp;
        	}
        }
}


void bubble_sort(int* array, int size)
{

        int i, j;
        int temp;

        for(i = 0; i < size - 1; i++)// bubble sort
        {
                for(j = 0; j < size - i - 1; j++)
                {
                        if(*(array + j) > *(array + j + 1))
                        {
                                temp = *(array + j);
                                *(array + j) = *(array + j + 1);
                                *(array + j + 1) = temp;
                        }
                }
        }
}

void insertion_sort(int* array, int size)
{
	int i, key, j;

	for(i = 1; i < size; i++)
	{
		key = array[i];
		j = i - 1;
	
		while(j >= 0 && array[j] > key)
		{
			(array[j + 1]) = array[j];
			j = j - 1;
		}

		array[j + 1] = key;
	}
}

double calculate_time(clock_t begin, clock_t end)
{
	double total = (double)(end - begin) /(CLOCKS_PER_SEC);

return total;
}












