#ifndef PROG3_H
#define PROG3_H

#define MAX_LINE_LEN 40

#define BUF_LEN (MAX_LINE_LEN + 2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int parseForHighest(const char* filename, int* highest)
{
	if ( !filename || !highest)
	{
		return -1;
	}
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return -2;
	}
	char buf[MAX_LINE_LEN];     
	int highest_int = -1000;     // may need to make this lower
	while(fgets(buf, MAX_LINE_LEN, fp))
	{
		int current_int = atoi(buf);
		if (current_int > highest_int)
		{
			highest_int = current_int;
		}
	}
	*highest = highest_int;
	fclose(fp);
	return 0;
}

int* getAllHigherThan(const int* arr, unsigned arrlen, int threshold, unsigned* newArrlen)
{
	if (!arr || !arrlen || !threshold || !newArrlen)
	{
		return NULL;
	}
	unsigned len_list = 0;
	for (int i=0; i<arrlen; i++)
	{
		if (arr[i] > threshold)
		{
			len_list = len_list + 1;
		}
	}
	int list[len_list];
	unsigned list_index = 0;
	for (int i=0; i<arrlen; i++)
	{
		int item = arr[i];
		if (item > threshold)
		{
			list[list_index] = item;
			list_index = list_index + 1;
		}
	}
	unsigned max_index = len_list;
	int* returnList = malloc((len_list-1)*sizeof(int));
	for (int j=0; j<len_list; j++)
	{
		returnList[j] = list[max_index-1];
		max_index = max_index - 1;
	}
	*newArrlen = len_list;
	return returnList;
}


char* getFirstToken(char* str, const char* delim)
{
	char* pointer_to_first = strpbrk(str, delim);
	if (pointer_to_first == NULL)
	{

		int n = strlen(str);
		char* copy_of_string = malloc((n+1)*sizeof(char));
		for (int i=0; i<n; i++)
		{
			copy_of_string[i] = str[i];
		}
		copy_of_string[n] = '\0';
		return copy_of_string;
	}
	int len_first_tok = strlen(str) - strlen(pointer_to_first);
	char* return_string = malloc((len_first_tok + 1)*sizeof(char));
	for (int i=0; i<len_first_tok; i++)
	{
		return_string[i] = str[i];
	}
	return_string[len_first_tok] = '\0';
	return return_string;
}

int is_next_char_delim(char next_char, const char* delim)
{
	int next_char_is_delim = 0;
	for (int i=0; i<strlen(delim); i++)
	{
		if (delim[i] == next_char)
		{
			next_char_is_delim = 1;
		}
	}
	return next_char_is_delim;
}


char* strtok_c(const char* str, const char* delim)
{
	static char* current_string = NULL;
	static int pointer = 0;
	if (str != NULL)
	{
		pointer = 0;
		// copy string to a mutable copy
		int n = strlen(str);
		char* copy_of_string = malloc((n+1)*sizeof(char));
		for (int i=0; i<n; i++)
		{
			copy_of_string[i] = str[i];
		}
		copy_of_string[n] = '\0';

		// set static current string to copy of string
		current_string = copy_of_string;
	}
	else
	{
		// if str is not null make sure current string is also not null
		if (current_string == NULL)
		{
			return NULL;
			free(current_string);
		}
	}
	// then check to see if its the end of the string
	if (current_string[pointer] == '\0')
	{
		return NULL;
		free(current_string);
	}
	// get the token     make sure to return token if token exists and rest of string if not 	
	while (is_next_char_delim(current_string[pointer], delim) == 1)
	{
		pointer = pointer + 1;
		if (current_string[pointer] == '\0')
		{
			return NULL;
			free(current_string);
		}
	}
	char* return_tok = getFirstToken(current_string+pointer, delim);
	if (strlen(return_tok) == strlen(current_string+pointer))
	{
		pointer = 0;
		current_string = NULL;
		free(current_string);
		return return_tok;
	}
	// set pointer to rest of string
	char* rest_of_string = strpbrk(current_string+pointer, delim);
	rest_of_string = rest_of_string + 1;
	pointer = ((rest_of_string-current_string)/sizeof(char));
	return return_tok;
}

struct Student
{
	char* name;
	int numCurrCourses;
	char** currCourses;
	int numPrevCourses;
	char** prevCourses;
};

struct Student* loadStudent(const char* studentFilename)
{
	struct Student *s;
        s=malloc(sizeof(struct Student));
	if (studentFilename == NULL)
	{
		return NULL;
	}
	FILE* fp = fopen(studentFilename, "r");
	if (fp == NULL)
	{
		return NULL;
	}
	int numCurrCourses;
	int numPrevCourses;
	char buf[BUF_LEN];
	int lineCounter = 0;
	int i =0;
	int j =0;
	char** prevCourses;
	char** currCourses;
	while (fgets(buf, BUF_LEN, fp)!=NULL)
	{
		if (lineCounter == 0)
		{
			int name_len = strlen(buf);
			char* name = malloc(name_len*sizeof(char));
			strcpy(name, buf);
			name = strtok(name, "\n");
			s->name = name;
			lineCounter = lineCounter + 1;
		}
		else if (lineCounter == 1)
		{
			numCurrCourses = atoi(buf);
			s->numCurrCourses = numCurrCourses;
			lineCounter = lineCounter + 1;
		}
		else if(lineCounter == 2)
		{
			currCourses = malloc(numCurrCourses*(BUF_LEN+1)*sizeof(char));
			char* course = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(course, buf);
			currCourses[i] = course;
			i = i+1;
			lineCounter = lineCounter + 1;
		}
		else if (lineCounter >2 && lineCounter<=numCurrCourses)
		{
			char* course = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(course, buf);
			currCourses[i] = course;
			i = i+1;
			lineCounter = lineCounter + 1;
		}
		else if (lineCounter == 1+numCurrCourses)
		{
			char* course = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(course, buf);
			currCourses[i] = course;
			i = i+1;
			lineCounter = lineCounter + 1;
			i = i+1;
			s->currCourses = currCourses;
		}
		else if(lineCounter == 2+numCurrCourses)
		{
			lineCounter = lineCounter + 1;
		}
		else if (lineCounter == 3+numCurrCourses)
		{
			numPrevCourses = atoi(buf);
			s->numPrevCourses = numPrevCourses;
			lineCounter = lineCounter + 1;
		}
		else if (lineCounter == 4+numCurrCourses)
		{
			prevCourses = malloc(numPrevCourses*(BUF_LEN+1)*sizeof(char));
			char* course = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(course, buf);
			prevCourses[j] = course;
			j = j+1;
			lineCounter = lineCounter + 1;
		}
		else if (lineCounter == 2+numCurrCourses+numPrevCourses)
		{
			char* course = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(course, buf);
			prevCourses[j] = course;
			j = j+1;
			lineCounter = lineCounter + 1;
			s->prevCourses = prevCourses;
		}
		else 
		{
			char* course = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(course, buf);
			prevCourses[j] = course;
			j = j+1;
			lineCounter = lineCounter + 1;
		}
	}
	return s;
	fclose(fp);
}

void printStudent(const struct Student* s)
{
	if (s==NULL)
	{
		return;
	}
	printf("Name: %s\n", s->name);
	printf("Current courses:\n"); 
	for (int i=0; i<(s->numCurrCourses); i++)
	{
		printf("%s", s->currCourses[i]);
	}
	printf("Previous courses:\n");
	for (int i=0; i<(s->numPrevCourses); i++)
	{
		printf("%s", s->prevCourses[i]);
	}
}


void freeStudent(struct Student** s)
{
	free((*s)->name);
	for (int i=0; i<((*s)->numCurrCourses); i++)
	{
		free(((*s)->currCourses)[i]);
	}
	for (int j=0; j<((*s)->numPrevCourses); j++)
	{
		free(((*s)->prevCourses)[j]);
	}
	free((*s)->currCourses);
	free((*s)->prevCourses);
	free(*s);	
}

int areClassmates(const struct Student* s1, const struct Student* s2)
{
	int classes_together = 0;
	for (int i=0; i<(s1->numCurrCourses); i++)
	{
		for (int j=0; j<(s2->numCurrCourses); j++)
		{
			if (strcmp(s1->currCourses[i],s2->currCourses[j]) == 0)
			{
				classes_together = 1;
			}
		}
	}
	return classes_together;
}


#endif // PROG3_H
