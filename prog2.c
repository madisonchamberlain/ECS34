# include <stdio.h>

void sum3(int a, int b, int c, int *sum)
{
	if (sum)
	{
		int total = a+b+c;
		*sum = total;
	}
}

void replaceIfHigher(long* arr, unsigned len)
{
	long user_input;
	for (int i=0; i<len; ++i)
	{
		scanf("%ld", &user_input);
		if (arr[i] < user_input)
		{
			arr[i] = user_input;
		}
	}
}

int performShiftCipher(char* text, int k)
{
	if (k > 500 || k < -500 || text == NULL)
	{
		return 0;
	}
	else
	{
		for (int i=0; text[i] != '\0'; i++)
		{
			if (text[i] >= 'a' && text[i] <= 'z')
			{
				if (k >= 0)
				{	
					int to_a = ((text[i] - 'a')+k)%26;
					char new_ascii = to_a + 'a';
					text[i] = new_ascii;
				}	
				else
				{
					
					
					int to_a = ((text[i] - 'a')+k)%26;
					if (to_a < 0)
					{
						to_a = to_a + 26;
					}
					char new_ascii = to_a + 'a';
					text[i] = new_ascii;
				}
			}
			else if (text[i] >= 'A' && text[i]<= 'Z')
			{
				if (k >= 0)
				{	
					int to_A = ((text[i] - 'A')+k)%26;
					char new_ascii = to_A + 'A';
					text[i] = new_ascii;
				}
				else
				{
					
					int to_A = ((text[i] - 'A')+k)%26;
					if (to_A < 0)
					{
						to_A = to_A + 26;
					}
					char new_ascii = to_A + 'A';
					text[i] = new_ascii;
				}
			}
			else if (text[i] >= '0' && text[i] <= '9')
			{
				if (k >= 0)
				{	
					int to_0 = ((text[i] - '0')+k)%10;
					char new_ascii = to_0 + '0';
					text[i] = new_ascii;
				}
				else
				{
					
					int to_0 = ((text[i] - '0')+k)%10;
					if (to_0 < 0)
					{
						to_0 = to_0 + 10;
					}
					char new_ascii = to_0 + '0';
					text[i] = new_ascii;
				}
			}
		}
		return 1;
	}
}

int getLen (char* string)
{
	int length;
	for (length = 0; string[length] != '\0'; length++);
	return length;
}

char* strrstr(char* haystack, char* needle)
{
	char* return_loc = NULL;
	int hay_index = getLen(haystack) -1;
	int ned_index = getLen(needle) - 1;
	while (hay_index >= 0)
	{
		if (needle[ned_index] == haystack[hay_index])
		{
			ned_index = ned_index - 1;
			hay_index = hay_index - 1;
			if (ned_index < 0)
			{
				
				int answer = hay_index + 1;
				return_loc = haystack + answer;
				return return_loc;
			}
		}
		else
			hay_index = hay_index - 1;
	}
	printf("s is NULL\n");
	return NULL;
}

int charInString(char* string, char target)
{
	int charInString = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
	char character = string[i];
		if (character == target)
		{
			charInString = 1;
		}
	}
	return charInString;
}

int eachContains(char** strings, char target, unsigned numStrings, char** firstOffending)
{
	for (int i = 0; i<numStrings; i++)
	{
		char* string = strings[i];
		int targetPresent = charInString(string, target);
		if (targetPresent == 0)
		{
			*firstOffending = string;
			return 0;
		}
	}
	return 1;
}






















