#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 25

typedef struct numbers{
	int* array;
	int* sortedAscending;
	int* sortedDescending;
}Numbers;

void displayMenu();
Numbers* readBinaryFile(FILE* fp);
void sortAscending(int* array);
void sortDescending(int* array);
void freeArrays(Numbers* numbers);
void printArray(int* array);
void merge(int arr[], int i, int mid, int j);
void mergesort(int arr[], int i, int j);
void quicksort(int x[], int first, int last);

int main(int argc,char * argv[])
{
	char* filename;
	int option = 1;
	FILE* fp;
	Numbers* numbers;

        if(argc != 2)
        {
                printf("Error, insufficent argument.\n");

        return 0;
        }

        filename = argv[1];

	fp = fopen(filename, "rb");

	numbers = readBinaryFile(fp);

	sortAscending(numbers -> sortedAscending);
	sortDescending(numbers -> sortedDescending);


	while(option != 4)
	{
		displayMenu();
		printf("\n\nSelect an option:\n");
		scanf("%d", &option);
	
		switch (option){ 
		
		case 1: 
			printf("-- Printing unsorted array --\n");
			printArray(numbers -> array);
			break;
		case 2:
			printf("-- Printing Ascending array --\n");
                        printArray(numbers -> sortedAscending);
                        break;
		case 3:
                        printf("-- Printing Descending array --\n");
                        printArray(numbers -> sortedDescending);
                        break;
		case 4:
			printf("-- Exiting and freeing all memory --\n");
			freeArrays(numbers);
			exit(0);
		default:
			printf("Error, enter number between 1-4\n");
		}
	}
return 0;
}
void displayMenu()
{
	printf("\n\tMenu:\n");	

	printf("1.) Print unsorted array.\n");

	printf("2.) Print ascending array.\n");

	printf("3.) Print descending array.\n");

	printf("4.) Exit.\n");
}

Numbers* readBinaryFile(FILE* fp)
{
        int* ptr;
	int* ptr2;
	int* ptr3;
	Numbers* num;

	ptr = malloc(sizeof(int)* SIZE);
        ptr2 = malloc(sizeof(int)* SIZE);
	ptr3 = malloc(sizeof(int)* SIZE);
	num = malloc(sizeof(Numbers));


        if(fp == NULL)
        {
                printf("Error, could not open.\n");
		free(ptr);
		free(ptr2);
		free(ptr3);
		free(num);
		fclose(fp);
                return NULL;
        }
                else
                {
                        fread(ptr, sizeof(int), SIZE, fp);
			memcpy(ptr2, ptr, (sizeof(int)* SIZE));
			memcpy(ptr3, ptr, (sizeof(int)* SIZE));
                }
	num -> array = ptr;
	num -> sortedAscending = ptr2;
	num -> sortedDescending = ptr3;
 
fclose(fp);

return num;
}

void mergesort(int arr[], int i, int j)
{
	int mid = 0;
	
	if(i < j) 
	{
		mid = (i + j) / 2;
		mergesort(arr, i, mid);
		mergesort(arr, mid + 1, j);
		merge(arr, i , mid, j);
	}
}
void merge(int arr[], int i, int mid, int j)
{
	int temp[SIZE];
	int l = i;
	int r = j;
	int m = mid + 1;
	int k = l;
	int i1;

	while(l <= mid && m <=r)
	{
		if(arr[l] <= arr[m])
		{
			temp[k++] = arr[l++];
		}
		else
		{
			temp[k++] = arr[m++];
		}
	}

	while(l <= mid)
		temp[k++] = arr[l++];

	while(m <= r)
		temp[k++] = arr[m++];
	
	for(i1 = i; i1 <= j; i1++)
	{
		arr[i1] = temp[i1];
	} 
}

void sortAscending(int* array)
{
	mergesort(array, 0, SIZE - 1);
}
void quicksort(int x[], int first, int last)
{
	int pivot, j, temp, i;

	if(first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while(i < j)
		{
			while(x[i] >= x[pivot] && i < last)
				i++;
			while(x[j] < x[pivot])
				j--;
			if(i < j)
			{
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
		}
	temp = x[pivot];
	x[pivot] = x[j];
	x[j] = temp;
	quicksort(x, first, j - 1);
	quicksort(x, j + 1, last);
	}
}

void sortDescending(int* array)
{
	quicksort(array, 0, SIZE -1);
}

void freeArrays(Numbers* numbers)
{
	free(numbers -> array);
	free(numbers -> sortedAscending);
	free(numbers -> sortedDescending);
	free(numbers);
}

void printArray(int* array)
{
	int i;

	for(i = 0; i < SIZE; i++)
	{
		printf("%d ", *(array + i));
	}
}
	

















