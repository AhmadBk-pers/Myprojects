/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Recursion test modules
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stdio.h>  /* printf           */
#include <stdlib.h> /* calloc, free     */
#include <assert.h> /* assert           */
#include "node_utils.h" /* node utils API */
#include "stack_int.h"      /* stack API */
#include "recursion.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define PINK    "\033[1;35m"
#define TEAL    "\033[1;36m"
#define RESET   "\033[1;0m"

#define PRINT_SUCCESS(s) printf(GREEN "%s succeeded in line %d.\n" RESET, (s), __LINE__)
#define PRINT_FAILED(s, val, expec) printf(RED "%s failed in line %d. " YELLOW \
    "expected %s for %s \n" RESET, (s), __LINE__, #expec, #val)
#define COMPARE_AND_ALERT(val, expec, name) (((val) != (expec)) ? \
            PRINT_FAILED(#name, val, expec) : PRINT_SUCCESS(#name))
#define HANDLE_ALLOC(x, name) if (!x)                            \
            {                                                       \
                printf("Couldn't allocate memory in "#name", line %d.\n", __LINE__); \
                return;                                             \
            }

#define SIZE 11

static void StackPrintRecursive(stack_t *stack)
{
	int element = 0;
	
	if (!StackIsEmpty(stack))
	{
		element = StackPeek(stack);
		printf("%d \t", element);
		StackPop(stack);
		StackPrintRecursive(stack);
		StackPush(stack, element);
	}
}

void TestBreakFibonacci(void)
{
    printf("Fibonacci %d = %d\n", 100, FibRecursive(100));
    /*for (i = 0; i < LIMIT; i++)
    {
        printf("Fibonacci %lu = %d\n", i, FibRecursive(i));
    }*/
}

void TestFibonacci(void)
{
    int expected[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377,
        610, 987, 1597, 2584, 4181, 6765};
    size_t i = 0;

    for (i = 1; i < sizeof(expected) / sizeof(*expected); i++)
    {
        COMPARE_AND_ALERT(FibIterative(i), expected[i], "Fibonacci Iterative");
    }

    for (i = 1; i < sizeof(expected) / sizeof(*expected); i++)
    {
        COMPARE_AND_ALERT(FibRecursive(i), expected[i], "Fibonacci Recursive");
    }
}



void TestFlip(void)
{
    node_t *head = NodeUtilCreate();
    if (!head)
    {
        printf("Couldn't allocate memory to test Flip.\n");
        return;
    }

    while (NULL != head)
    {
        printf("Before:\n");
        NodeUtilPrintSList(head);
        head = FlipList(head);

        printf("Flipped:\n");
        NodeUtilPrintSList(head);
        printf("\n");
        head = NodeUtilRemove(head);
    }

    NodeUtilDestroy(head);
}

void TestStrLen(void)
{
    COMPARE_AND_ALERT(StrLen("654682"), 6, "strlen");
    COMPARE_AND_ALERT(StrLen("654\0682"), 6, "strlen");
    COMPARE_AND_ALERT(StrLen(""), 0, "strlen");
    COMPARE_AND_ALERT(StrLen("hfnn jkh \n yykg\t hg"), 19, "strlen");
    COMPARE_AND_ALERT(StrLen("1"), 1, "strlen");
}

void TestStrCmp(void)
{
    COMPARE_AND_ALERT(StrCmp("", ""), 0, "strcmp");
    COMPARE_AND_ALERT(StrCmp("ugh", "ugh"), 0, "strcmp");
    COMPARE_AND_ALERT(StrCmp("hjhst", "jmdfh"), 'h' - 'j', "strcmp");
    COMPARE_AND_ALERT(StrCmp("\0", "gdfg"), -(int)'g', "strcmp");
    COMPARE_AND_ALERT(StrCmp("XYZ", "abc"), 'X' - 'a', "strcmp");
    COMPARE_AND_ALERT(StrCmp("london", "londona"), -'a', "strcmp");
    COMPARE_AND_ALERT(StrCmp("mexicoo", "mexico"), 'o', "strcmp");
    COMPARE_AND_ALERT(StrCmp("kaukaz", "kawkaz"), 'u' - 'w', "strcmp");

}

void TestStrCpy(void)
{
	char dest[20]; /* Initializing space in buffer, to copy to */
	char *result; /* A pointer, that would point to the initial memory
					 location of the buffer = of the copied string */
	char *src = "hello"; 				/* Test case 1 */

	result = StrCpy(dest, src);
    COMPARE_AND_ALERT(StrCmp(result, src), 0, "strcpy");

	src = "g\0";		 				/* Test case 2 */
	result = StrCpy(dest, src);
    COMPARE_AND_ALERT(StrCmp(result, src), 0, "strcpy");

	src = "any\nthing";					/* Test case 3 */
	result = StrCpy(dest, src);
    COMPARE_AND_ALERT(StrCmp(result, src), 0, "strcpy");

	src = "before_copy";				/* Test case 4 */
	result = StrCpy(dest, src);
    COMPARE_AND_ALERT(StrCmp(result, src), 0, "strcpy");

}

void TestStrCat(void)
{
	char *src = " Home!";
	char dest1[30] = "Welcome"; /*(char *) malloc(sizeof(char) * 20);*/
	char dest2[30] = "Welcome";
	char dest4[30] = "check it";

	char *result = StrCat(dest1, src);
	char *expected = "Welcome Home!";
    COMPARE_AND_ALERT(StrCmp(result, expected), 0, "strcat");

	src = "";
    result = StrCat(dest2, src);
    expected = "Welcome";
    COMPARE_AND_ALERT(StrCmp(result, expected), 0, "strcat");

	src = " o ";
    result = StrCat(dest4, src);
    expected = "check it o ";
    COMPARE_AND_ALERT(StrCmp(result, expected), 0, "strcat");

}

void TestStrStr(void)
{
	char *needle = "you";
	char *haystack = "are you ready?";
	char *result = StrStr(haystack, needle);
	char *expected = haystack + 4;
    COMPARE_AND_ALERT((result == expected), 1, "strstr");

	needle = "k";
    haystack = "Welcome";
    result = StrStr(haystack, needle);
    expected = NULL;
    COMPARE_AND_ALERT(result, expected, "strstr");

	needle = "nahman";
    haystack = "n na nah nahm nahma nahman meuman";
/*				012345678901234567890		*/
    result = StrStr(haystack, needle);
    expected = haystack + 20;
    COMPARE_AND_ALERT((result == expected), 1, "strstr");

	needle = "a";
    haystack = "abra kadabra";
    result = StrStr(haystack, needle);
    expected = haystack;
    COMPARE_AND_ALERT((result == expected), 1, "strstr");

    needle = "end";
    haystack = "abra kadabraend";
/*				0123456789012			*/
    result = StrStr(haystack, needle);
    expected = haystack + 12;
    COMPARE_AND_ALERT(StrCmp(result, expected), 0, "strstr");

    needle = "";
    haystack = "abra kadabraend";
/*              012345678901234           */
    result = StrStr(haystack, needle);
    expected = haystack;
    /*printf("%s\n", result);*/
    COMPARE_AND_ALERT((result == expected), 1, "strstr");

}

void TestSortStack(void)
{
    int sorted[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int insert_order[SIZE] = {5, 3, 9, 1, 8, 2, 0, 7, 6, 10, 4};
    size_t i = 0;

    stack_t *stack = StackCreate(SIZE);
    if (!stack)
    {
        return;
    }
    for (i = 0; i < SIZE; ++i)
    {
        StackPush(stack, insert_order[i]);

    }

    printf("before:\n");
    StackPrintRecursive(stack);
    printf("\n");
    StackSort(stack);
    printf("sorted:\n");
    StackPrintRecursive(stack);
    printf("\n");

    StackDestroy(stack);
}

int main(void)
{
/*    printf(PINK"\nbreak Fibonacci\n"RESET);*/
/*    TestBreakFibonacci();*/

    printf(PINK"\nFibonacci\n"RESET);
    TestFibonacci();
    printf(PINK"\nLIST FLIP\n"RESET);
    TestFlip();

    printf(PINK"\nSorting Stack Test\n" RESET);
    TestSortStack();

    printf(PINK"\nSTR LEN\n"RESET);
    TestStrLen();
    printf(PINK"\nSTR CMP\n"RESET);
    TestStrCmp();
    printf(PINK"\nSTR CPY\n"RESET);
    TestStrCpy();
    printf(PINK"\nSTR CAT\n"RESET);
    TestStrCat();
    printf(PINK"\nSTR STR\n"RESET);
    TestStrStr();

    return 0;
}

