#include <stdio.h>
#include <string.h>

unsigned foo(char* str, char target, char* output)
{
	int n = strlen(str);
	counter = 0;
	output_index = 0;
	for (int i=0; i<n; i++)
	{
		char character = str[i];
		if (character == target)
		{
			counter = counter + 1;
		}
		else
		{
			output[output_index] = str[i];
			output_index = output_index + 1;
		}
	}
}
