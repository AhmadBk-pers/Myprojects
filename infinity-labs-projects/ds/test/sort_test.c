/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Sorting module tests
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdio.h>  /* printf           */
#include <assert.h> /* assert           */
#include <stdlib.h> /* rand             */
#include <time.h>   /* clock            */

#include "sort.h"

#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define PINK    "\x1B[35m"
#define TEAL    "\x1B[36m"
#define RESET   "\x1B[0m"

#define PRINT_SUCCESS(s) printf(GREEN "%s succeeded in line %d.\n" RESET, (s), __LINE__)
#define PRINT_FAILED(s) printf(RED "%s failed in line %d.\n" RESET, (s), __LINE__)
#define COMPARE_AND_ALERT(val, expec, name) (((val) != (expec)) ? \
            PRINT_FAILED(#name) : PRINT_SUCCESS(#name))
#define PRINT_TIMESPAN(c_tics, str) printf(YELLOW "%s took %lu tics to run.\n" \
                                RESET, (str), (c_tics))

#define ARR_SIZE 5000

static int Compare(const void *num1, const void *num2)
{
	return *(int *)num1 - *(int *)num2;
}


static void CompareClock(clock_t time1, clock_t time2, clock_t timeqs2, clock_t timeqs1)
{
	if((time2 - time1) > (timeqs2 - timeqs1))
	{
		printf("qsort is faster\n");
	}
	else if ((time2 - time1) < (timeqs2 - timeqs1))
	{
		printf("My sort is faster\n");
	}
	else
	{
		printf("sqrt is equal to bubble\n");
	}
}



static void PutRandArr(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);

    for (i = 0; i < size; i++)
    {
        arr[i] = rand()%1000;
    }
}

static void PutOrderedArr(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);

    for (i = 0; i < size; i++)
    {
        arr[i] = i * 3 / 2;
    }
}

static void PutReverseOrderedArr(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);

    for (i = 0; i < size; i++)
    {
        arr[i] = (size - i - 1) * 3 / 2;
    }
}

static int IsOrdered(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);

    for (i = 1; i < size; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            return 0;
        }
    }

    return 1;
}

/*static void PrintIntArr(int *arr, size_t size)*/
/*{*/
/*    size_t i = 0;*/

/*    assert(arr);*/

/*    for (i = 0; i < size; i++)*/
/*    {*/
/*        printf("%d\n", arr[i]);*/
/*    }*/
/*}*/

static void TestBubbleSort(int *arr, size_t size)
{
    clock_t c_before = {0};
    clock_t c_after = {0};
	clock_t qsort_before = {0}, qsort_after = {0};

    PutRandArr(arr, size);
    /*printf("Random array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    BubbleSort(arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "\n\nRandom array Bubble Sort");
    /*printf("Random array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Random array Bubble Sort");

    PutRandArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);


    PutOrderedArr(arr, size);
    /*printf("Ordered array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    BubbleSort(arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Ordered array Bubble Sort");
    /*printf("Ordered array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Ordered array Bubble Sort");

    PutOrderedArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);



    PutReverseOrderedArr(arr, size);
    /*printf("Reverse Ordered array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    BubbleSort(arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Reverse Ordered array Bubble Sort");
    /*printf("Reverse Ordered array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Reverse Ordered array Bubble Sort");

    PutReverseOrderedArr(arr, size);    
    qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);
}

static void TestSelectionSort(int *arr, size_t size)
{
    clock_t c_before = {0};
    clock_t c_after = {0};
	clock_t qsort_before = {0}, qsort_after = {0};

    PutRandArr(arr, size);
    /*printf("Random array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    SelectionSort(arr, size);
    c_after = clock();
    
    printf(BLUE "\nTesting Selection Sort\n");
    
    PRINT_TIMESPAN(c_after - c_before, "\n\nRandom array Selection Sort");
    /*printf("Random array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Random array Selection Sort");

    PutRandArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);


    PutOrderedArr(arr, size);
    /*printf("Ordered array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    SelectionSort(arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Ordered array Selection Sort");
    /*printf("Ordered array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Ordered array Selection Sort");

    PutOrderedArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);


    PutReverseOrderedArr(arr, size);
    /*printf("Reverse Ordered array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    SelectionSort(arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Reverse Ordered array Selection Sort");
    /*printf("Reverse Ordered array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Reverse Ordered array Selection Sort");

    PutReverseOrderedArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);
}

static void TestInsertionSort(int *arr, size_t size)
{
    clock_t c_before = {0};
    clock_t c_after = {0};
	clock_t qsort_before = {0}, qsort_after = {0};

    PutRandArr(arr, size);
    /*printf("Random array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    InsertionSort(arr, size);
    c_after = clock();
    
    printf(BLUE "\nTesting Insertion Sort\n");
    
    PRINT_TIMESPAN(c_after - c_before, "\n\nRandom array Insertion Sort");
    /*printf("Random array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Random array Insertion Sort");

    PutRandArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);


    PutOrderedArr(arr, size);
    /*printf("Ordered array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    InsertionSort(arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Ordered array Insertion Sort");
    /*printf("Ordered array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Ordered array Insertion Sort");

    PutOrderedArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);


    PutReverseOrderedArr(arr, size);
    /*printf("Reverse Ordered array before Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    InsertionSort(arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Reverse Ordered array Insertion Sort");
    /*printf("Reverse Ordered array after Bubble Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Reverse Ordered array Insertion Sort");

    PutReverseOrderedArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);
}

static void TestCountingSort(int *arr, size_t size)
{
    clock_t c_before = {0};
    clock_t c_after = {0};
	clock_t qsort_before = {0}, qsort_after = {0};
	int dest_arr[ARR_SIZE] = {0};

    PutRandArr(arr, size);
    /*printf("Random array before Counting Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    
    if (CountingSort(dest_arr, arr, size))
    {
    	PRINT_FAILED("Counting Sort");
    }
    
    printf(BLUE "\nTesting Counting Sort\n");
    
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "\n\nRandom array Counting Sort");
    /*printf("Random array after Counting Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(dest_arr, size), 1, "Random array Counting Sort");
	
	PutRandArr(arr, size);
	
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);


    PutOrderedArr(arr, size);
    /*printf("Ordered array before Counting Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    CountingSort(dest_arr, arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Ordered array Counting Sort");
    /*printf("Ordered array after Counting Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(arr, size), 1, "Ordered array Counting Sort");
	
	PutOrderedArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);



    PutReverseOrderedArr(arr, size);
    /*printf("Reverse Ordered array before Counting Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    CountingSort(dest_arr, arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Reverse Ordered array Counting Sort");
    /*printf("Reverse Ordered array after Counting Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(dest_arr, size), 1, "Reverse Ordered array Counting Sort");
    
    PutReverseOrderedArr(arr, size);
    qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);
}

static void TestRadixSort(int *arr, size_t size)
{
    clock_t c_before = {0};
    clock_t c_after = {0};
	clock_t qsort_before = {0}, qsort_after = {0};
	int dest_arr[ARR_SIZE] = {0};
	
	printf(BLUE "\nTesting Radix Sort\n");
    PutRandArr(arr, size);
    printf("Random array before Radix Sort:\n");
    
/*    PrintIntArr(arr, size);*/
    c_before = clock();
    
    if (RadixSort(dest_arr, arr, size))
    {
    	PRINT_FAILED("Radix Sort");
    }
    
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "\n\nRandom array Radix Sort");
    printf("Random array after Radix Sort:\n");
/*    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(dest_arr, size), 1, "Random array Radix Sort");

	PutRandArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);


    PutOrderedArr(arr, size);
    /*printf("Ordered array before Radix Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    RadixSort(dest_arr, arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Ordered array Radix Sort");
    /*printf("Ordered array after Radix Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(dest_arr, size), 1, "Ordered array Radix Sort");

    PutOrderedArr(arr, size);
	qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);



    PutReverseOrderedArr(arr, size);
    /*printf("Reverse Ordered array before Radix Sort:\n");
    PrintIntArr(arr, size);*/
    c_before = clock();
    RadixSort(dest_arr, arr, size);
    c_after = clock();
    PRINT_TIMESPAN(c_after - c_before, "Reverse Ordered array Radix Sort");
    /*printf("Reverse Ordered array after Radix Sort:\n");
    PrintIntArr(arr, size);*/
    COMPARE_AND_ALERT(IsOrdered(dest_arr, size), 1, "Reverse Ordered array Counting Sort");

    PutReverseOrderedArr(arr, size);    
    qsort_before = clock();
	qsort(arr, size, sizeof(int), Compare);
	qsort_after = clock();
	
	CompareClock(c_before, c_after, qsort_after, qsort_before);
}

int main(void)
{
    int arr[ARR_SIZE] = {0};

    TestBubbleSort(arr, ARR_SIZE);
    TestSelectionSort(arr, ARR_SIZE);
    TestInsertionSort(arr, ARR_SIZE);
    TestCountingSort(arr, ARR_SIZE);
    TestRadixSort(arr, ARR_SIZE);

    return 0;
}
