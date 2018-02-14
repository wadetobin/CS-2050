//Wade Tobin
//Homework 2
//wmtb75
//Section E
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Book{
	int bookID;
	char* title;
	bool checkedOut;
	struct Book* next;
}book;

typedef struct BookIds{
	int id;
	struct BookIds* next;
}bookIds;

typedef struct Student{
	char* firstName;
	char* lastName;
	int priority;
	int readingLevel;
	bookIds* wishlist; 
	struct Student* next;
}student;

student* buildStudentList(char* studentsFile, student* head);
void printStudents(student* head);
void createPriorityQueue(student* head);
void addWishlist(student* head,char* wishListfile);
book* createBookList(char* bookFile,book* bookHead);
void printBookList(book* bookHead);
void checkOutBooks(student* studentHead, book* bookHead);
book* findBook(book* bookhead, int book_id);
void freeList(student* studenthead);
void freebook(book* bookhead);
void freewishlist(bookIds* head);

#define NAME 25
#define TITLE 50
int main(int argc, char* argv[])
{
	char* file1;
	char* file2;
	char* file3;
	student* head = NULL;
	book* bookHead = NULL;

	if(argc != 4)
	{
		printf("Insufficent Arguments");
		return 0;
	}
	
	file1 = argv[1];
	file2 = argv[2];
	file3 = argv[3];

	head = buildStudentList(file1, head);

	printStudents(head);

	createPriorityQueue(head);

	addWishlist(head, file2);

	printf("%d ", head->wishlist->next->next->next->id);
	printStudents(head);

	bookHead = createBookList(file3, bookHead);

	printBookList(bookHead);
	
	checkOutBooks(head, bookHead);
	
	freeList(head);
	freebook(bookHead);

	return 0;
}




student* buildStudentList(char* studentsFile, student* head) 
{
	FILE* fp;
	char* last = malloc(sizeof(char)* NAME); 
	char* first = malloc(sizeof(char) * NAME);
	int prior = 0;
	int read = 0;

	fp = fopen(studentsFile, "r");
	head = malloc(sizeof(student));
	student* current = head;
	student* pre =NULL;
	if(fp == NULL)
	{
		printf("Error, cannot open file.\n");
		return NULL;
	}
	
	while(fscanf(fp, "%s %s %d %d", first, last, &prior, &read) == 4)
	{
		if(current != head)
		{
			current = malloc(sizeof(student));
			pre->next = current;
		}
		
		current -> firstName = malloc(sizeof(char)* NAME);
                memcpy(current -> firstName, first, sizeof(char)* NAME);
                current -> lastName = malloc(sizeof(char) * NAME);
		memcpy(current -> lastName, last, sizeof(char) * NAME);

		current -> priority = prior;
		current -> readingLevel = read;
                pre = current;
		current = current -> next;
	}

	fclose(fp);
	free(last);
	free(first);


	return head;
}
void printStudents(student* head) 
{
        student* current = head;
        bookIds* temp = NULL;
        while(current != NULL)
        {
                printf("First Name: %s \n", current -> firstName);
		printf("Last Name: %s \n", current -> lastName);
		printf("Priority: %d \n", current -> priority);
		printf("Reading Level: %d \n", current -> readingLevel); 
		
		if(current -> wishlist != NULL)
		{
			
			temp = current -> wishlist;
			printf("Wishlist:");	
			int i;
			for(i=0;i<4;i++)
			{ 
			printf("%d ->", temp -> id);
			temp = temp -> next;
			}
		}
                current = current -> next;
		printf("\n");
        }
        printf("\n");
}

void createPriorityQueue(student* head) 
{
	student* current;
	student* current1;
	student* counter; 
	current1 = head;
	char* first = malloc(sizeof(char)* NAME);	
	char* last = malloc(sizeof(char) * NAME);
	int prior = 0;
	int read = 0;

	while(current1 -> next != NULL)
	{
		current = head;
		counter = current1;
		while(counter -> next!= NULL)
		{
			if(current -> priority > current -> next -> priority)
			{
				memcpy(first, current -> firstName, sizeof(char) * NAME);
				memcpy(last, current -> lastName, sizeof(char) * NAME);
				prior = current -> priority;
				read = current -> readingLevel;
				memcpy(current -> firstName,current -> next -> firstName,sizeof(char)*NAME);
				memcpy(current -> lastName, current -> next -> lastName, sizeof(char) *NAME);
				current -> priority = current -> next -> priority;
				current -> readingLevel = current -> next -> readingLevel;
				memcpy(current -> next -> firstName, first, sizeof(char) * NAME);
				memcpy(current -> next -> lastName, last, sizeof(char) * NAME);
				current -> next -> priority = prior;
				current -> next -> readingLevel = read;
			}
		 current = current -> next;
		counter = counter -> next;
		}
	 current1 = current1 -> next;
	}

free(first);
free(last);

}

void addWishlist(student* head,char* wishListfile) 
{
	FILE* fp;
	int* arr = malloc(sizeof(int) * 4);

	fp = fopen(wishListfile, "r");

	student* current = head;
        //bookIds* pre = NULL;
	while(fscanf(fp, "%d %d %d %d", arr, (arr + 1), (arr + 2), (arr + 3)) == 4)
	{
		current -> wishlist = malloc(sizeof(bookIds));
		int i=0;
		bookIds * temp = current->wishlist;
		//pre = NULL;
		for(i=0;i<4;i++)
		{
			temp->id = *(arr+i);
			if(i!=3){	
				temp->next = malloc(sizeof(bookIds));
				temp = temp->next;		
			}else{
			temp -> next = NULL;
			}
		}
		current = current->next;
	}

	free(arr);
	fclose(fp);
			
}

book* createBookList(char* bookFile,book* bookHead) 
{
	FILE* fp;
	char* tempc = malloc(sizeof(char)*TITLE);
        int tempi = 0;
	book* pre=NULL;
	fp = fopen(bookFile, "r");
	bookHead = malloc(sizeof(book));
	book* current = bookHead;
	
	if(fp == NULL)
	{
		printf("Error, cannot open the file.\n");
		return NULL;
	}

	while(fscanf(fp,"%d %s", &tempi, tempc) == 2)	
	{	
		if(current != bookHead)
		{
	        current = malloc(sizeof(book));
		pre ->next = current;
		}
		current -> title = malloc(sizeof(char)*TITLE);
		memcpy(current -> title, tempc, sizeof(char)*TITLE);
		current -> bookID = tempi;
		pre = current;
		current = current -> next;
	}

	fclose(fp);
	free (tempc);

	return bookHead;
}

void printBookList(book* bookHead) 
{
        book* current = bookHead;
	

	printf("Book List:\n");


        while(current != NULL)
        {

                printf("Id: %d Title: %s \n", current -> bookID, current -> title);
                current = current -> next;
        }
        printf("\n");
}

void checkOutBooks(student* studentHead, book* bookHead) 
{
	student* current = studentHead;
	
	while(current != NULL)
	{
		bookIds* temp = current -> wishlist;
		printf("\nStudent: %s is checking out:\n", current -> firstName);
		int i = 0 ;
		while(i != 4)
		{
			book* tempi = findBook(bookHead, temp -> id);
			
			if(tempi -> checkedOut == false)
			{
			//printf("%p\n",tempi->next);
			tempi -> checkedOut = true;			
			printf("Book %s\n", tempi -> title);
			}
			else
			{
			//printf("%p\n",tempi->next);
			printf("Book %s is checked out already!!\n", tempi -> title);
			}	
			temp = temp -> next;
			i++;
		}
		current = current -> next;
	}		
}	
	
book* findBook(book* bookhead, int book_id) 
{
	book* current = bookhead;
	
	while(current != NULL && current -> bookID != book_id)
	{
		current = current -> next;
	}
	return current;
}

void freeList(student* studenthead)
{
        student* current = studenthead;
	
	if(current == NULL)
	{
		return;
	}
	
	if(current -> next != NULL)
	{
		freeList(current -> next);
	}
	free(current -> firstName);
	free(current -> lastName);
	freewishlist(current -> wishlist); 
	free(current);
}
void freebook(book* bookhead)
{
	book* current = bookhead;

	if(current == NULL)
	{
		return;
	}
	
	if(current -> next != NULL)
	{
		freebook(current -> next);
	}
	free(bookhead -> title);
	free(bookhead);
}

void freewishlist(bookIds* head)
{
	bookIds* current = head;
	if(current == NULL)
	{
		return;
	}
	if(current -> next != NULL)
	{
		freewishlist(current -> next);
	}
	
	free(current);
}
