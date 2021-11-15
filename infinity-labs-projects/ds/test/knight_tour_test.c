/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ------
* Description   Knight tour module tests
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <time.h>   /* time   */

#include "knight_tour.h"


#define _RED_    "\033[1;31m"
#define _GREEN_  "\033[1;32m"
#define _YELLOW_ "\033[1;33m"
#define _BLUE_   "\033[1;34m"
#define _PURPLE_ "\033[1;35m"
#define _CYAN_   "\033[1;36m"
#define _WHITE_  "\033[0m"


int TestKnight(void);

int InitArray(size_t **arr, size_t rows, size_t cols);
void DestroyArray(size_t **arr, size_t rows);
void PrintArray(size_t **arr, size_t rows, size_t cols);

void PrintResultsInt(int, int);
void PrintResultsLong(char*, size_t, size_t);
static void TestTime(clock_t, clock_t);


int main()
{
	int status = 0;
	
	status = TestKnight();
	
	printf("\n");
	return status;
}



int TestKnight()
{
	const size_t rows = 8;
	const size_t cols = 8;
	size_t **result = (size_t **)malloc(rows * sizeof(size_t*));
	size_t x = 0, y = 0;
	clock_t before = 0, after = 0;
	int status = 0, overall_status = 0;
	
	printf("\nTest - Knight Tour\n\n");
	
	srand(time(NULL));
	x = rand() % cols;
	y = rand() % rows;
	status = InitArray(result, rows, cols);

    for (x = 0; x < rows; x++)
    {
        for (y = 0; y < cols; y++)
        {
            
            if (0 != status)
            {
                return -1;
            }
            
            printf(_BLUE_"size: %ld x %ld\n", rows, cols);
            printf("start at: (%ld , %ld)\n"_WHITE_, x, y);
            
            before = clock();
            status = KnightTour(result, rows, cols, x, y);
            after = clock();
            
            overall_status += status;
            PrintResultsLong("success", status, 0);
            PrintArray(result, rows, cols);
            TestTime(before, after);
        }
    }	
	
    PrintResultsLong("Overall status", overall_status, 0);
	
	DestroyArray(result, rows); result = NULL;
	
	return 0;
}






int InitArray(size_t **arr, size_t rows, size_t cols)
{
	size_t i = 0;
	
	for (i = 0; i < rows; i++)
	{
		arr[i] = (size_t *)calloc(cols, sizeof(size_t));
	}
	
	return 0;
}


void DestroyArray(size_t **arr, size_t rows)
{
	size_t i = 0;
	
	for (i = 0; i < rows; i++)
	{
		free(arr[i]); arr[i] = NULL;
	}
	
	free(arr); arr = NULL;
}


void PrintArray(size_t **arr, size_t rows, size_t cols)
{
	size_t i = 0, j = 0;
	
	printf("\n");
	
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			(0 == (i + j) % 2) ? printf(_YELLOW_) : printf(_CYAN_);
			printf("%3ld ", arr[i][j]);
		}
		printf("\n");
	}
	
	printf(_WHITE_"\n");
}


void PrintResultsInt(int res, int expect)
{
	(res == expect) ? printf(_GREEN_) : printf(_RED_);
	printf ("result: %d , expect: %d\n", res, expect);
	printf(_WHITE_);
}


void PrintResultsLong(char *title, size_t res, size_t expect)
{
	(res == expect) ? printf(_GREEN_) : printf(_RED_);
	printf ("%s: %ld , expect: %ld\n", title, res, expect);
	printf(_WHITE_);
}


static void TestTime(clock_t before, clock_t after)
{
	printf(_PURPLE_"time: %-9ld "_WHITE_, after - before);
}