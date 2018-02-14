#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define NUM 30

int isPhone(char* phone);
int isEmail(char* email);
int isName(char* name);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Not enough Arguments");
		return 1;
	}
	
	FILE* fp = fopen(argv[1], "r");
	char** array = malloc(sizeof(char*)* MAX);
	char* temp = malloc(sizeof(char)* NUM);
	int i = 0;


	while(fscanf(fp, "%s", temp) == 1)
	{
		*(array + i) = malloc(sizeof(char) * NUM);
		memcpy(*(array + i), temp, sizeof(char) * NUM);	
		i++;
	}

	fclose(fp);

	int j = 0;

	for(j = 0; j < i; j++)
	{
		if(isPhone(*(array + j)))
		{
			printf("Phone Number: %s\n", (*(array + j)));
		}
		else if(isEmail(*(array + j)))
		{
			printf("Email Address: %s\n", (*(array + j)));
		}
		else if(isName(*(array + j)))
		{
			if(j + 2 < i)
			{
				if(isName(*(array + j + 1)))
				{
					printf("Name: %s %s\n", (*(array + j)), (*(array + j + 1)));
					j++;
				}
			}
		}
	}

	for(j = 0; j < i; j++)
	{
		free(*(array + j));
	}
	free(array);
	free(temp);

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
