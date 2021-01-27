#ifndef LIBRARY_H
#define LIBRARY_H
#define MAX_LINE_LEN 300
#define BUF_LEN 302

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{
	char* title;
	char* author;
	int year;
};

struct Library
{
	struct Book* books;
	int numBooks;
};


struct Library* loadLibrary(const char* filename)
{
	struct Library* lib;
	lib = malloc(sizeof(struct Library));
	if (filename == NULL)
	{
		return NULL;
	}
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return NULL;
	}
	char buf[BUF_LEN];
	int i = 0;
	int lineCounter = 0;
	int numBooks;
	struct Book* books;
	while (fgets(buf, BUF_LEN, fp)!=NULL)
	{
		// if at first line; set the number of books 
		if (lineCounter == 0)
		{
			numBooks = atoi(buf);
			lib->numBooks = numBooks;
			lineCounter = lineCounter + 1;
		}
		// if its the second line, initialize books and make first book
		else if (lineCounter == 1)
		{
			// initialize books to number of books times space needed per book
			books = malloc(numBooks*sizeof(struct Book));
			// make first book:
			struct Book book;
			char* line = malloc((BUF_LEN+1)*sizeof(char));
			char* title = malloc((BUF_LEN+1)*sizeof(char));
			char* author = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(line, buf);
			char* copytitle = strtok(line, ",");
			strcpy(title, copytitle);
			char* copyauthor = strtok(NULL, ",");
			strcpy(author, copyauthor);
			int year = atoi(strtok(NULL, ","));
			book.title = title;
			book.author = author;
			book.year = year;
			free(line);
			// append book to books
			books[i] = book;
			//increase i and lineCounter 
			lineCounter = lineCounter + 1;
			i = i + 1;
		}	
		// if at the last line, set last book and set books pointer of books
		else if (lineCounter == numBooks)
		{
			// create a struct of book
			struct Book book;	
			char* line = malloc((BUF_LEN+1)*sizeof(char));
			char* title = malloc((BUF_LEN+1)*sizeof(char));
			char* author = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(line, buf);
			char* copytitle = strtok(line, ",");
			strcpy(title, copytitle);
			char* copyauthor = strtok(NULL, ",");
			strcpy(author, copyauthor);
			int year = atoi(strtok(NULL, ","));
			book.title = title;
			book.author = author;
			book.year = year;
			free(line);
			// append book to books
			books[i] = book;
			//increase i and lineCounter 
			lineCounter = lineCounter + 1;
			i = i + 1;
			// set books to books in library 
			lib->books = books;
		}
		// if it is any other line, create a book and increase line counter by one
		else
		{
			struct Book book;	
			char* line = malloc((BUF_LEN+1)*sizeof(char));
			char* title = malloc((BUF_LEN+1)*sizeof(char));
			char* author = malloc((BUF_LEN+1)*sizeof(char));
			strcpy(line, buf);
			char* copytitle = strtok(line, ",");
			strcpy(title, copytitle);
			char* copyauthor = strtok(NULL, ",");
			strcpy(author, copyauthor);
			int year = atoi(strtok(NULL, ","));
			book.title = title;
			book.author = author;
			book.year = year;
			free(line);
			books[i] = book;
			//increase i and lineCounter 
			lineCounter = lineCounter + 1;
			i = i + 1;
		}

	}
	fclose(fp);
	return lib;
}

int printLibrary(const struct Library* library)
{
	if (library == NULL)
	{
		return 0;
	}
	for(int i=0; i<(library->numBooks); i++)
	{
		struct Book book = (library->books)[i];
		printf("%s by %s (%d)\n", book.title, book.author, book.year);
	}
	return 1;
}

int countCommonTitles(const struct Library* lib1, const struct Library* lib2)
{
	int common_titles = 0;
	for(int i=0; i<(lib1->numBooks); i++)
	{
		struct Book booki = (lib1->books)[i];
		char* lib1_title_i = booki.title;
		for(int j=0; j<(lib2->numBooks); j++)
		{
			struct Book bookj = (lib2->books)[j];
			char* lib2_title_j = bookj.title;
			if (strcmp(lib1_title_i, lib2_title_j) == 0)
			{
				common_titles = common_titles + 1;
			}
		}
	}
	return common_titles;
}
int freeLibrary(struct Library* library)
{
	if (library == NULL)
	{
		return 0;
	}
	for (int i=0; i<(library->numBooks); i++)
	{
		struct Book book = (library->books)[i];
		free(book.title);//allocate
		free(book.author);//allocate
	}
	free(library->books);
	free(library);
	return 1;
}

#endif //LIBRARY_H
