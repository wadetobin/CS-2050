//Wade Tobin
//Section E
//Lab 10
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person{
	char first[25];
	char last[25];
	char email[25];
	char phone[25];
	struct Person* left;
	struct Person* right;
}person;

#define MAX 100
#define NUM 30

int isPhone(char* phone);
int isEmail(char* email);
int isName(char* name);
void print_address_book(person* head);
person* add_person(person* head, char* first, char* last, char* phone, char* email);
void free_address_book(person* head);

int main(int argc, char* argv[])
{
        if(argc != 6)
        {
                printf("Not enough Arguments");
                return 1;
        }

        FILE* fp;
	person* head = NULL;
	
	int k = 1;

	fp = fopen(argv[k], "r");
        char** array = malloc(sizeof(char*)* MAX);
        char* temp = malloc(sizeof(char)* NUM);
	char* first, *last, *email, *phone;
        int i = 0;


        while(fscanf(fp, "%s", temp) == 1)
        {
                *(array + i) = malloc(sizeof(char) * NUM);
                memcpy(*(array + i), temp, sizeof(char) * NUM);
                i++;
        }
       
	int j =0; 
	for(j = 0; j < i; j++)
            {
                if(isPhone(*(array + j)))
                {
                       phone= *(array+j);
                }
                else if(isEmail(*(array + j)))
                {
                        email= *(array + j);
                }
                else if(isName(*(array + j)))
                {
                        if(j + 2 < i)
                        {
                                if(isName(*(array + j + 1)))
                                {
                                    first = *(array + j);
                                    last = *(array + j + 1);
                                        j++;
                                }
                        }
                }
		}
            head =add_person(head, first, last, phone, email);



	fclose(fp);
return 0;
}

int isPhone(char* phone)
{
        char* array = malloc(sizeof(char) * 4);


        if(strlen(phone) == 12)
        {
                memcpy(array, phone, sizeof(char)* 3);

                if(atoi(array) >= 100 && atoi(array) <= 999)
                {
                        if(*(phone + 3) == '-')
                        {
                                memcpy(array, (phone + 4), sizeof(char)* 3);

                                if(atoi(array) >= 0 && atoi(array) <= 999)
                                {
                                        if(*(phone + 7) == '-')
                                        {
                                                memcpy(array, (phone + 8), sizeof(char)* 4);

                                                if(atoi(array) >= 0 && atoi(array) <= 9999)
                                                {
                                                        free(array);
                                                        return 1;
                                                }
                                                else
                                                {
                                                        free(array);
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                free(array);
                                                return 0;
                                        }
                                }
                                else
                                {
                                        free(array);
                                        return 0;
                                }
                        }
                        else
                        {
                                free(array);
                                return 0;
                        }
                }
                else
                {
                        free(array);
                        return 0;
                }
        }
        else
        {
                free(array);
                return 0;
        }
}

int isEmail(char* email)
{
        int i;
        int j = 0;
        char* string1 = ".com";
        char* string2 = ".edu";
        char* array = malloc(sizeof(char)* 4);


        for(i = 0; i <(int)strlen(email); i++)
        {
                if(*(email + i) == '@')
                {
                        j = 1;
                }
        }

        if(strlen(email) >= 4)
        {
                memcpy(array, email + strlen(email) - 4, sizeof(char)* 4);

                if(strcmp(array, string1) == 0 && j == 1)
                {
                        free(array);
                        return 1;
                }
                else if(strcmp(array, string2) == 0 && j == 1)
                {
                        free(array);
                        return 1;
                }
                else
                {
                        free(array);
                        return 0;
                }
        }
        else
        {
                free(array);
                return 0;
        }
}

int isName(char* name)
{
        if(*name >= 'A' && *name <= 'Z')
        {
                return 1;
        }
        else
        {
                return 0;
	}
} 
void print_address_book(person* head)
{
	if(head != NULL)
	{
		print_address_book(head -> left);
		printf("============================\n");
		printf("NAME: %s %s\n", head -> first, head -> last);
		printf("PHONE: %s\n", head -> phone);
		printf("EMAIL: %s\n", head -> email);
		printf("============================\n\n");
		print_address_book(head -> right);
        }
}

person* add_person(person* head, char* first, char* last, char* phone, char* email)
{
	if(head !=NULL)
	{
		if(head -> last[0] > *last)
		{
			add_person(head -> left, first, last, phone, email);
		}
		else
		{
			add_person(head -> right, first, last, phone, email);
		}
	}
	else
	{
		person* temp = malloc(sizeof(person));
		
		strcpy(temp -> email, email);
		strcpy(temp -> phone, phone);
		strcpy(temp -> first, first);
		strcpy(temp -> last, last);
		temp -> left = temp -> right = NULL;
		head = temp;
	}

return head;
}

void free_address_book(person* head)
{
	if(head != NULL)
	{
		free(head -> left);
		free(head -> right);
		free(head);
	}
}
