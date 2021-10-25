/****************************************************************************/
/*******************************File Handling********************************/
/****************************Author: Ahmad Bakri*****************************/
/*****************************Reviewer:Amatsia"******************************/
/****************************************************************************/

#include <stdio.h>	/*printf(), getchar()*/
#include <stdlib.h> /*exit()*/
#include <string.h>	/*strlen strncmp*/


#define SIZE 10
#define MAX_LIMIT 100
#define FLAGSNUM 5

enum _status_codes{
	E_SUCCESS = 0,
	E_FILE_COULDNT_OPEN = 1,
	E_FILE_COULDNT_CLOSE = 2,
	E_BUFFER_NOT_SAVED = 3,
	E_COULDNT_SEEK_CORSUR = 4,
	E_COULDNT_GET_DATA = 5,
	E_UNABLE_TO_DELETE = 6
};

const char *GetErrorStr(int _status)
{
	
	const char *ret;
	
	switch (_status)
	{
		case E_SUCCESS:
	   		ret = "Success";
			break;
			
		case E_COULDNT_GET_DATA:
		    ret = "Error: Could not get data.";
			break;
			
		case E_FILE_COULDNT_CLOSE:
			ret = "Error: Could not close file.";
			break;
			
		case E_BUFFER_NOT_SAVED:
			ret = "Error: Could not save buffer.";
			break;
			
		case E_FILE_COULDNT_OPEN:
			ret = "Error: Could not open the file.";
			break;
			
		case E_COULDNT_SEEK_CORSUR:
			ret = "Error: Could not set the cursor to the rigth place.";
			break;
			
		case E_UNABLE_TO_DELETE:
	   		ret = "Error: Unable to delete the file.";
			break;
			
	}
	
	return ret;
}

/*making the prints red */
void red() 
{
	printf("\033[1;31m");
}

/*making the prints green */
void green() 
{
	printf("\033[0;32m");
}

/*making the prints reseted */
void reset() 
{
 	printf("\033[0m");
}


void StatusHandler(const char *error_str)
{
	if (!strcmp(error_str, "Success"))
	{
		green();
	}
	else 
	{
		red();
	}
	
	printf("%s\n", error_str);
	
	reset();
}


/************************************EX1************************************/


struct print_me
{
	int x;
	void (*print_ptr)(int);
};


void Print(int x)
{
	printf("%d\n",x);
}

void TestPrint_me()
{
	int i = 0;
	struct print_me struct_arr[SIZE];
	
	for (i = 0; i < SIZE; i++)
	{
		struct_arr[i].x = i;
		struct_arr[i].print_ptr = Print;
	}
	
	for (i = 0; i < SIZE; i++)
	{
		struct_arr[i].print_ptr(struct_arr[i].x);
	}
}

/************************************EX2************************************/

struct operation
{
	const char *op;
	int (*comparision_ptr)(const char *, const char *);
	int (*operation_ptr)(const char *, const char *);
};

int Compare(const char *op, const char *str)
{
	return !strncmp(op,str,strlen(op));
}

int Count(const char *str, const char *file_name)
{
	
	char ch;
	int lines_count = 0;
	FILE *file = NULL;
	
	(void) str;
	
	file = fopen(file_name, "a+");
	
	if (file == NULL)
	{
		return E_FILE_COULDNT_OPEN;
	}	
	
	while ((ch = fgetc(file)) != EOF) 
	{
    	if (ch == '\n')
    	{
    		lines_count++;
    	}	
	}
	
	printf("The number of lines is: %d\n", lines_count);
	
	if (fclose(file) == EOF)
	{
		return E_FILE_COULDNT_CLOSE;
	}
	
	return E_SUCCESS;
}

int Remove(const char *str, const char *file_name)
{
	(void) str;
	
	if (remove(file_name))
	{
		return E_UNABLE_TO_DELETE;
	}
   	
   	return E_SUCCESS;
}

int Exit(const char *str, const char *file_name)
{
	(void) str;
	(void) file_name;
	
	exit(0);
}

void CopyFile(FILE *dest, FILE *src)
{
	char c = 0;
	
	c = fgetc(src);
	
    while (c != EOF)
    {
        fputc(c, dest);
        c = fgetc(src);
    }
}

int FirstLineAppend(const char *str, const char *file_name)
{
	char *temp_file_name = "temp.file";
	FILE *file = NULL, *temp_file = NULL;
	file = fopen(file_name, "r+");
	temp_file = fopen(temp_file_name, "a+");
	
	str++;										/*to remove <*/
	
	if (file == NULL) 
	{
		return E_FILE_COULDNT_OPEN;
	}
	
	if (temp_file == NULL) 
	{
		return E_FILE_COULDNT_OPEN;
	}
	
	CopyFile(temp_file, file);
	
	if (fseek(file, 0, SEEK_SET))
	{
		return E_COULDNT_SEEK_CORSUR;
	}
	
	if (fseek(temp_file, 0, SEEK_SET))
	{
		return E_COULDNT_SEEK_CORSUR;
	}

	if (fputs(str, file) == EOF)
	{
		return E_BUFFER_NOT_SAVED;
	}
	
	if (fseek(file, strlen(str), SEEK_SET))
	{
		return E_COULDNT_SEEK_CORSUR;
	}

	CopyFile(file, temp_file);
	
	if (fclose(file) == EOF)
	{
		return E_FILE_COULDNT_CLOSE;
	}
	
	if (remove(temp_file_name))
	{
		return E_UNABLE_TO_DELETE;
	}
	
	return E_SUCCESS;
}

int AppendString(const char *str, const char *file_name)
{
	FILE *file = NULL;
	
	file = fopen(file_name, "a+");
	
	if (file == NULL)
	{
		return E_FILE_COULDNT_OPEN;
	}
	
	if (fputs(str, file) == EOF)
	{
		return E_BUFFER_NOT_SAVED;
	}
		
	if (fclose(file) == EOF)
	{
		return E_FILE_COULDNT_CLOSE;
	}
	
	return E_SUCCESS;
}

int StringInput(int argc, char **argv)
{
	int i = 0;
	const char *file_name = argv[1];
	char str[MAX_LIMIT];
	const char *op;
	
	struct operation operation_array [FLAGSNUM] = {
	{"-count", Compare, Count},
	{"-remove", Compare, Remove},
	{"-exit", Compare, Exit},
	{"<", Compare, FirstLineAppend},
	{"", Compare, AppendString}
	};
	
	(void) argc;
	if (file_name == NULL)
	{
		return E_FILE_COULDNT_OPEN;
	}
	
	while (1)
	{
		if (fgets(str, MAX_LIMIT, stdin) == NULL)
		{
			return E_COULDNT_GET_DATA;
		}
		
		for (i = 0; i < FLAGSNUM ; i++)
		{
			int _status = E_SUCCESS;
			
			op = operation_array[i].op;
			
			if (operation_array[i].comparision_ptr(op, str))
			{
				_status = operation_array[i].operation_ptr(str, file_name);
				
				if (E_SUCCESS != _status)			return _status;
				
				break;
			}	
		}
	}
	
	return E_SUCCESS;
}


int main(int argc, char **argv)
{
	int _status = E_SUCCESS;
/*	TestPrint_me();*/
	
	_status = StringInput(argc, argv);
	
	StatusHandler(GetErrorStr(_status));
	
	return E_SUCCESS;
}
