/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ------
* Description   Hash Table module tests
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include <string.h> /* strcmp, strcpy, strlen */

#include "hash_t.h"

#define ESC 27

void HeaderColor(char *string);
void Yellow();
void Red(void);
void Green(void);
void ResetColor(void);
void TestExpectedINTS(int actual, int expected, const char *func_name);

int CompareInts(const void *d1, const void *d2);
void InitIntArr(int *arr, size_t size);
size_t HashInts(const void *data);
int PrintEntries(void *data, void *param);


void TestUnit1();
void TestUnit2And3();

void DictionaryInteractive();
void Dictionary();
size_t DictionaryHash(const void *data);
void LoadDictionary(h_table_t *table);
int WrapStrcmp(const void *d1, const void *d2);
int DestroyData(void *data, void *param);


int main()
{
    TestUnit1();
    TestUnit2And3(); 
    Dictionary();

    return 0;
}

/*************************** DICTIONARY ***************************************/
void Dictionary()
{
    h_table_t *table = HTCreate(256, DictionaryHash, WrapStrcmp);
    if (!table)
    {
        printf("Table Create Fail\n");
        return;
    }

    LoadDictionary(table);
    DictionaryInteractive(table);
    HTForEach(table, DestroyData, NULL);
    HTDestroy(table);
}

int DestroyData(void *data, void *param)
{
    (void)param;
    free(data);
    data = NULL;
    
    return 0;
}

size_t DictionaryHash(const void *data)
{
    return (size_t)(*(unsigned char *)data);
}

void DictionaryInteractive(h_table_t *table)
{
    char buffer[30] = {0};

    printf("Enter String and press Enter.\nTo Quit Press Esc and Enter\n");
    while (buffer[0] != ESC)
    {
        printf("Enter String:");
        scanf("%s", buffer);
        
        if (HTFind(table, (void *)buffer))
        {
            Green();
            printf("Word: %s is Found!\n", buffer);
            ResetColor();
        }
        else
        {
            Red();
            printf("Word: %s is NOT Found!\n", buffer);
            ResetColor();
        }
    }
}

void LoadDictionary(h_table_t *table)
{
    char buffer[30] = {0};
    char *buffer_ptr = buffer;
    FILE *dictionary = fopen("/usr/share/dict/words", "r");
    if (!dictionary)
    {
        printf("File Could'nt open\n");
        return;
    }

    while (fgets(buffer, 30, dictionary))
    {
        char *malloc_buffer = (char *)malloc(sizeof(char) * strlen(buffer));
        if (!malloc_buffer)
        {
            printf("Failed Malloc\n");
            return;
        }

        while(*buffer_ptr)
        {
            buffer_ptr++;
        }
        *(buffer_ptr - 1) = '\0';
        
        buffer_ptr = buffer;

        strcpy(malloc_buffer, buffer);

        if (HTInsert(table, (void *)malloc_buffer))
        {
            printf("Insertion Failed\n");
            return;
        }
    }

    fclose(dictionary);
}

int WrapStrcmp(const void *d1, const void *d2)
{
    return strcmp((const char *)d1, (const char *)d2);
}

/***************************** TEST *******************************************/
void TestUnit1()
{
    h_table_t *table = HTCreate(10, HashInts, CompareInts);
    if (!table)
    {
        Red();   printf("Create Failed!\n");   ResetColor();
    }

    HeaderColor("Unit 1");

    TestExpectedINTS(HTIsEmpty(table), 1, "IsEmpty");

    HTDestroy(table);
}

void TestUnit2And3()
{
    size_t i = 0;
    int arr[20];
    int not_found = 20;
    h_table_t *table = HTCreate(10, HashInts, CompareInts);
    if (!table)
    {
        Red();   printf("Create Failed!\n");   ResetColor();
    }

    InitIntArr(arr, 20);

    HeaderColor("Unit 2 + 3");

    for (; i < 20; i++)
    {
        if (HTInsert(table, (void *)&arr[i]))
        {
            Red();
            printf("Insert Fail! %lu\n", i);
            ResetColor();
        }
    }
    
    TestExpectedINTS(HTIsEmpty(table), 0, "IsEmpty");
    TestExpectedINTS(HTSize(table), 20, "Size");

    TestExpectedINTS(*(int *)HTFind(table, &arr[10]), 10, "Find");
    TestExpectedINTS(*(int *)HTFind(table, &arr[0]), 0, "Find");
    TestExpectedINTS(*(int *)HTFind(table, &arr[5]), 5, "Find");
    TestExpectedINTS(*(int *)HTFind(table, &arr[19]), 19, "Find");
    TestExpectedINTS((size_t)HTFind(table, &not_found), 0, "Find- Not Found");

    HeaderColor("For Each");
    HTForEach(table, PrintEntries, NULL);
    printf("\n");

    for (i = 0; i < 20; i++)
    {
        HTRemove(table, (void *)&arr[i]);
    }
    
    TestExpectedINTS(HTIsEmpty(table), 1, "IsEmpty");
    TestExpectedINTS(HTSize(table), 0, "Size");

    TestExpectedINTS((size_t)HTFind(table, &arr[5]), 0, "Remove + Not Found");
    TestExpectedINTS((size_t)HTFind(table, &arr[10]), 0, "Remove + Not Found");


    HTDestroy(table); 
}

size_t HashInts(const void *data)
{
    return *(int *)data % 10;
}

int PrintEntries(void *data, void *param)
{
	(void)param;
	printf("%d -> ", *(int *)data);

	return 0;
}

void InitIntArr(int *arr, size_t size)
{
	size_t i = 0;

	for (; i < size; i++)
	{
		arr[i] = i;
	}
}

int CompareInts(const void *d1, const void *d2)
{
	return *(int *)d1 - *(int *)d2;
}


void TestExpectedINTS(int actual, int expected, const char *func_name)
{
	if (actual != expected)
	{
		Red();
		printf("Result: %d \n", actual);
	}
	else
	{
		Green();
	}
	
	printf("%s\n", func_name);
	ResetColor();
}

void HeaderColor(char *string)
{
	Yellow();
	printf("\n%s \n", string);
	ResetColor();
}

void Yellow()
{
	printf("\033[0;33m");
}

void Red() 
{
	printf("\033[1;31m");
}

void Green() 
{
	printf("\033[0;32m");
}

void ResetColor()
{
	printf("\033[0m");
}
