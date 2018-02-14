//Wade Tobin
//Lab 5
//wmtb75
//Section E
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_NAME_LENGTH 25
#define BOOK_SIZE 5
#define EMAIL_LENGTH 50

typedef struct info{
	long int phone;
	char* email;
}Info;

typedef struct person{
	char* firstName;
	char* lastName;
	Info* contact;
}Person;

int check_email(char* email);
int check_phone(long int phone);
Person* allocate_memory();
void add_contact(Person* list);
void free_list(Person* list);
void print_list(Person* list);

int main(void){

	Person* list = allocate_memory();
	
	add_contact(list);

	print_list(list);

	free_list(list);

return 0;
}

int check_email(char* email)
{
	int i;
	int q = strlen(email);	
	
	for(i = 0; i < 	q; i++)
	{	
	if (email[i]  == '@'){
		return 1;
	}
	}
return 0;
}
int check_phone(long int phone)
{
	if((phone < 999999999) || (phone > (9999999999)))
	{
		return 0;
	}
	else
	{
	return 1;
	}
}

Person* allocate_memory()
{
	Person* list = malloc(sizeof(Person) * BOOK_SIZE);
	//Info* con = malloc(sizeof(Info) * BOOK_SIZE);

	int i;

	for(i = 0; i < BOOK_SIZE; i++)
	{
		(list + i) -> firstName = malloc(sizeof(char)* MAX_NAME_LENGTH);
		(list + i) -> lastName = malloc(sizeof(char)* MAX_NAME_LENGTH);
		(list + i) -> contact = malloc(sizeof(Info));
		(list + i) -> contact -> email = malloc(sizeof(char)* EMAIL_LENGTH);
	}
return list;
}
void add_contact(Person* list)
{
	int i;

	for(i = 0; i < BOOK_SIZE; i++)
	{
	printf("==================================\n");
        printf("CONTACT %d \n", i + 1);
        printf("==================================\n");
	
	printf("Enter your First Name:");
	scanf("%s", (list+i) -> firstName);

	printf("Enter your Last Name:");
	scanf("%s", (list + i) -> lastName);

	printf("Enter your email:");
	scanf("%s", (list + i) -> contact -> email);
	
	while(check_email((list+i) -> contact -> email) == 0)
	{
		printf("Error, incorrect input:");
		printf("Enter your email:");
		scanf("%s", (list + i) -> contact -> email);
	}	



	printf("Enter your phone Number(10 digits):");
	scanf("%ld", &(list + i) -> contact -> phone);
	
	while(check_phone((list+i) -> contact -> phone) == 0)
        {
                printf("Error, incorrect input:");
                printf("Enter your phone Number:");
                scanf("%ld", &(list + i) -> contact -> phone);
        }



	}

	




}

void free_list(Person* list)
{
	int i;

	for(i = 0; i < BOOK_SIZE; i++)
	{
		free((list + i) -> firstName);
		free((list + i) -> lastName);
		free((list + i) -> contact -> email);
		free((list + i) -> contact);
	}

	free(list);
}	

void print_list(Person* list)
{
	int i;

	for(i = 0; i < BOOK_SIZE; i++)
	{
	printf("==================================\n");
	printf("CONTACT %d \n", i + 1);
	printf("==================================\n");
	
	printf("First Name is:%s \n", (list + i) -> firstName);

	printf("Last Name is:%s \n", (list + i) -> lastName);

	printf("Email: %s \n", (list + i) -> contact -> email);

	printf("Phone Number: %ld \n", (list + i) -> contact -> phone);
	}
	
}

