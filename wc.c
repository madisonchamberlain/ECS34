#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Fileinfo
{
	char* filename;
	int num_lines;
	int num_words;
	int num_chars;
	int broken_file;
};

struct Fileinfo* loadTotal(int num_lines, int num_words, int num_chars)
{
	struct Fileinfo* file_info;
	file_info = malloc(sizeof(struct Fileinfo));
	char* total = malloc(6*sizeof(char));
	strcpy(total, "total");
	file_info->filename = total;
	file_info->broken_file = 0;
	file_info->num_lines = num_lines;
	file_info->num_words = num_words;
	file_info->num_chars = num_chars;
	return file_info;
}


struct Fileinfo* loadFile(FILE* fp, const char* filename, int broken_file)
{
	struct Fileinfo* file_info;
	file_info = malloc(sizeof(struct Fileinfo));
	if (broken_file == 1)
	{
		int len_error = strlen(filename)+1;
		char* error = malloc(len_error+1*(sizeof(char)));
		strcpy(error, filename);
		file_info->filename = error;
		file_info->num_lines = 0;
		file_info->num_words = 0;
		file_info->num_chars = 0;
		file_info->broken_file = broken_file;
		return file_info;
	}
	char character;
	char last_character = '\n';
	int num_lines = 0;
	int num_words = 0;
	int num_chars = 0;
	while ((character = fgetc(fp)) != EOF)
	{
		num_chars = num_chars + 1;
		if (character == '\n' || character == '\0')
		{
			num_lines = num_lines + 1;
		}
		if ((character == ' '&& last_character != ' '&&last_character!='\n')|| (character == '\n'&& last_character!= '\n'&&last_character != ' ')|| (character == '\0'&& last_character!= '\0')|| character == '\t')
		{
			num_words = num_words + 1;
		}
		last_character = character;
	}
	int len_name = strlen(filename);
	char* name = malloc(len_name+1*(sizeof(char)));
	strcpy(name, filename);
	file_info->filename = name;
	file_info->num_lines = num_lines;
	file_info->num_words = num_words;
	file_info->num_chars = num_chars;
	file_info->broken_file = broken_file;
	return file_info;
}

char* flag_type(char* arg, char* flags)
{
	if ((strcmp(arg, "--lines") == 0) || (strstr(arg, "l")!=NULL))
	{
		flags[0] = 'l';
	}
	if ((strcmp(arg, "--words") == 0) || (strstr(arg, "w")!=NULL))
	{
		flags[1] = 'w';
	}
	if ((strcmp(arg, "--chars") == 0) || (strstr(arg, "m")!=NULL))
	{
		flags[2] = 'm';
	}
	return flags;
}

void do_print(char* flags, struct Fileinfo* file_info)
{
	if (file_info->broken_file == 1)
	{
		printf("fopen: %s\n", file_info->filename);
	}
	else
	{
		if (strcmp(flags,"ooo") == 0)
		{
			printf("%s: %d %d %d\n", file_info->filename, file_info->num_lines, file_info->num_words, file_info->num_chars);
		}	
		else if (strcmp(flags,"loo")==0)
		{
			printf("%s: %d\n", file_info->filename, file_info->num_lines);
		}
		else if (strcmp(flags,"owo")==0)
		{
			printf("%s: %d\n", file_info->filename, file_info->num_words);
		}
		else if (strcmp(flags,"oom")==0)
		{
			printf("%s: %d\n", file_info->filename, file_info->num_chars);
		}
		else if (strcmp(flags,"lwo")==0)
		{
			printf("%s: %d %d\n", file_info->filename, file_info->num_lines, file_info->num_words);
		}
		else if (strcmp(flags,"lom")==0)
		{
			printf("%s: %d %d\n", file_info->filename, file_info->num_lines, file_info->num_chars);
		}
		else if (strcmp(flags,"owm")==0)
		{
			printf("%s: %d %d\n", file_info->filename, file_info->num_words, file_info->num_chars);
		}	
		else if (strcmp(flags,"lwm")==0)
		{
			printf("%s: %d %d %d\n", file_info->filename, file_info->num_lines, file_info->num_words, file_info->num_chars);
		}
	}	
}


int main(int argc, char* argv[])
{
	struct Fileinfo** files;
	files = malloc(50*sizeof(struct Fileinfo));  // initilize a list of file structs 
	char* flags = malloc(4*sizeof(char));//change to 4
	strcpy(flags, "ooo");
	//static int* lines_words_chars[3];
	//static char* filename;
	int lines = 0;
	int words = 0;
	int chars = 0;
	int num_files = 0;
	int return_value = 0;
	for (int i=1; i<argc; i++)
	{
		if (strstr(argv[i],"-") != NULL)
		{
			char* flag_types = flag_type(argv[i], flags);
			if (flag_types[0] == 'l')
			{
				flags[0] = 'l';
			}
			if (flag_types[1] == 'w')
			{
				flags[1] = 'w';
			}
			if (flag_types[2] == 'm')
			{
				flags[2] = 'm';
			}
		}
		else
		{
			char* filename = argv[i];
			FILE* fp = fopen(filename, "r");
			if (fp==NULL)
			{
				const char* error = strerror(errno);
				struct Fileinfo* file_info = loadFile(NULL, error, 1);
				return_value = 1; 
				files[num_files] = file_info;
				num_files = num_files + 1;
				//fclose(fp);
			}
			else
			{
				// loading the file to the struct
				struct Fileinfo* file_info = loadFile(fp, filename, 0);
				// add struct to a list of file info
				lines = lines + file_info->num_lines;
				words = words + file_info->num_words;
				chars = chars + file_info->num_chars;
				files[num_files] = file_info;
				num_files = num_files + 1;
				fclose(fp);
			}	
		}
	}
	if (num_files == 0)
	{
		fprintf(stderr, "No file provided.\n");
		return 2;
	}
	if (num_files == 1)
	{
		struct Fileinfo* file = files[0];
		do_print(flags, file);
	}
	else
	{
		for (int i = 0; i<num_files; i++)
		{
			struct Fileinfo* file = files[i];
			do_print(flags, file);
			free(file->filename);
			free(file);
		}
		struct Fileinfo* total = loadTotal(lines, words, chars);
		do_print(flags, total);
		free(total->filename);
		free(total);
	}
	free(files);
	free(flags);
	return return_value;
}

