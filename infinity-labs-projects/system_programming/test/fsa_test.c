/******************************************************************************
* Author        Ahmad Bakri
* Reviewer      tzvi
* Description   Fixed Size Allocator module - Test file
* Version:      1.0.0
* Updated:      Sept 2021
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdio.h>  /* printf           */
#include <stdlib.h> /* calloc, free     */
#include "fsa.h"

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
#define HANDLE_ALLOC(x, name) if (!x)                            \
            {                                                       \
                printf("Couldn't allocate memory in "#name"\n"); \
                return;                                             \
            }



void TestSuggestSize()
{
    size_t num_of_blocks = 0;
    size_t size_of_blocks = 17;
    size_t suggested = FSASuggestSize(num_of_blocks, size_of_blocks);
    size_t expected = (24) * num_of_blocks + 16;
    COMPARE_AND_ALERT(suggested, expected, "Undefined Behavior FSASuggestSize");

    num_of_blocks = 1;
    size_of_blocks = 8;
    suggested = FSASuggestSize(num_of_blocks, size_of_blocks);
    expected = (8) * num_of_blocks + 16;
    COMPARE_AND_ALERT(suggested, expected, "FSASuggestSize");

    num_of_blocks = 1;
    size_of_blocks = 5;
    suggested = FSASuggestSize(num_of_blocks, size_of_blocks);
    expected = (8) * num_of_blocks + 16;
    COMPARE_AND_ALERT(suggested, expected, "FSASuggestSize");

    num_of_blocks = 1;
    size_of_blocks = 10;
    suggested = FSASuggestSize(num_of_blocks, size_of_blocks);
    expected = (16) * num_of_blocks + 16;
    COMPARE_AND_ALERT(suggested, expected, "FSASuggestSize");

    num_of_blocks = 3;
    size_of_blocks = 10;
    suggested = FSASuggestSize(num_of_blocks, size_of_blocks);
    expected = (16) * num_of_blocks + 16;
    COMPARE_AND_ALERT(suggested, expected, "FSASuggestSize");

    num_of_blocks = 5;
    size_of_blocks = 24;
    suggested = FSASuggestSize(num_of_blocks, size_of_blocks);
    expected = (24) * num_of_blocks + 16;
    COMPARE_AND_ALERT(suggested, expected, "FSASuggestSize");
}



void PrintFSAValues(fsa_t fsa, size_t allocation_size)
{
    size_t i = 0;
    /*printf("%lu\n", (size_t)&fsa);*/
    for (; i < allocation_size / sizeof(size_t); ++i)
    {
        printf("TEST %lu = %lu\n", (size_t)&(*(size_t *)fsa), *(size_t *)fsa);
        fsa = (size_t *)fsa + 1;
    }
}
void TestFSA(void)
{
    size_t num_of_blocks = 8;
    size_t size_of_blocks = 17;
    size_t *blocks[8] = {0};
    size_t i = 0;
    size_t allocation_size = FSASuggestSize(num_of_blocks, size_of_blocks);
    size_t expec_alloc_size = (24) * num_of_blocks + 16;
    void *mem_pool = (void *)calloc(1, allocation_size);
    
    fsa_t fsa = FSAInit(mem_pool, allocation_size, size_of_blocks);

    printf("TEST mem_pool = %lu\n", (size_t)&(*(size_t *)mem_pool));
    printf("TEST fsa = %lu\n", (size_t)&(*(size_t *)fsa));

    PrintFSAValues(fsa, allocation_size);


    /* check suggest size for the instance, and emptiness*/
    COMPARE_AND_ALERT(allocation_size, expec_alloc_size, "FSASuggestSize");
    COMPARE_AND_ALERT(FSACountFree(fsa), num_of_blocks, "FSACountFree");

    /* alllocate all the blocks and check the count free as it decreases*/
    for (i = 0; i < num_of_blocks; ++i)
    {
        blocks[i] = FSAAlloc(fsa);
        COMPARE_AND_ALERT(FSACountFree(fsa), num_of_blocks - i - 1, "FSACountFree");
        PrintFSAValues(fsa, allocation_size);
    }
     /* check that alloc returns NULL when it is all allocated */
    COMPARE_AND_ALERT(FSAAlloc(fsa), NULL, "FSAAlloc");
    COMPARE_AND_ALERT(FSACountFree(fsa), 0, "FSACountFree");

    /* free one by one and assure count free */
    for (i = 0; i < num_of_blocks; ++i)
    {
        FSAFree(fsa, blocks[i]);
        COMPARE_AND_ALERT(FSACountFree(fsa), i + 1, "FSACountFree");
        PrintFSAValues(fsa, allocation_size);
    }

    /* alllocate all again and check the count free as it decreases*/
    for (i = 0; i < num_of_blocks; ++i)
    {
        blocks[i] = FSAAlloc(fsa);
        COMPARE_AND_ALERT(FSACountFree(fsa), num_of_blocks - i - 1, "FSACountFree");
        PrintFSAValues(fsa, allocation_size);
    }

    /*free selected one, not in order */
    FSAFree(fsa, blocks[2]);
    COMPARE_AND_ALERT(FSACountFree(fsa), 1, "FSACountFree");
    FSAFree(fsa, blocks[5]);
    COMPARE_AND_ALERT(FSACountFree(fsa), 2, "FSACountFree");
    FSAFree(fsa, blocks[7]);
    COMPARE_AND_ALERT(FSACountFree(fsa), 3, "FSACountFree");

    PrintFSAValues(fsa, allocation_size);

    blocks[7] = FSAAlloc(fsa);
    COMPARE_AND_ALERT(FSACountFree(fsa), 2, "FSACountFree");
    blocks[5] = FSAAlloc(fsa);
    COMPARE_AND_ALERT(FSACountFree(fsa), 1, "FSACountFree");
    blocks[2] = FSAAlloc(fsa);
    COMPARE_AND_ALERT(FSACountFree(fsa), 0, "FSACountFree");

    PrintFSAValues(fsa, allocation_size);

    free(mem_pool);
}

int main(void)
{
    TestSuggestSize();
    TestFSA();
    return 0;
}
