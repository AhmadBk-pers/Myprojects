/******************************************************************************
* Author        Shahar Refael Shoshany
* Reviewer      ---
* Description   Tests of Priority_Queue module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stdio.h>  /* printf() */
#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */

#include "priority_q.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

#define FAIL() (printf( RED "\nTest-Failed: at line %d\n" RESET, __LINE__))
#define SUCCESS() printf( GREEN "\nTest-success: at line %d\n" RESET, __LINE__)
#define TEST(test) do{if (!(test)) {FAIL();}} while(0)

/* Utility funcs */
/******************************************************************/
int PrioritizeLongInt(const void *d1, const void *d2);
int IsDivideByCriteria(const void *data, const void *criteria);

/* Test Functions */
/******************************************************************/
void PriorityQueueTests();
void TestInsertInMixedOrder();



int main()
{
    PriorityQueueTests();

    return 0;
}


void PriorityQueueTests()
{
    TestInsertInMixedOrder();

    /* Visual check for leakage - valgrind report */
}


/* Insert_In_Mixed_Order */
/******************************************************************/
void TestInsertInMixedOrder()
{
    size_t i = 0, j = 0;
    void *data_ptr = NULL;
    size_t int_arr[100];
    pq_t *prior_q = PQCreate(PrioritizeLongInt);

    TEST(PQSize(prior_q) == 0);
    TEST(PQIsEmpty(prior_q));

    for (i = 0, j = 0; i < 50; ++i, j += 2)
    {
        int_arr[j] = i;
        int_arr[j + 1] = 99 - i;

        TEST(0 == PQEnqueue(prior_q, (int_arr + j)));
        TEST(0 == PQEnqueue(prior_q, (int_arr + j + 1)));
        TEST(99 == *((size_t *)PQPeek(prior_q)));

        TEST(PQSize(prior_q) == (j + 2));
        TEST(!PQIsEmpty(prior_q));
    }

    TEST(PQSize(prior_q) == 100);
    TEST(!PQIsEmpty(prior_q));

    for (i = 0; i < 50; ++i)
    {
        TEST((99 - i) == *((size_t *)PQPeek(prior_q)));
        TEST((99 - i) == *((size_t *)PQDequeue(prior_q)));
        TEST((99 - i - 1) == *((size_t *)PQPeek(prior_q)));
        TEST(PQSize(prior_q) == (99 - i));
        TEST(!PQIsEmpty(prior_q));
    }

    TEST(PQSize(prior_q) == 50);
    TEST(!PQIsEmpty(prior_q));
    TEST(49 == *((size_t *)PQPeek(prior_q)));

    i = 42;
    data_ptr = PQErase(prior_q, &i);
    i = 0;
    TEST(data_ptr == int_arr + 84);
    TEST(42 == *((size_t *)data_ptr));

    TEST(PQSize(prior_q) == 49);
    TEST(49 == *((size_t *)PQPeek(prior_q)));

    i = 50;
    data_ptr = PQErase(prior_q, &i);
    i = 0;
    TEST(data_ptr == NULL);

    TEST(PQSize(prior_q) == 49);
    TEST(49 == *((size_t *)PQPeek(prior_q)));

    i = 49;
    data_ptr = PQErase(prior_q, &i);
    i = 0;
    TEST(data_ptr == int_arr + 98);
    TEST(49 == *((size_t *)data_ptr));

    TEST(PQSize(prior_q) == 48);
    TEST(48 == *((size_t *)PQPeek(prior_q)));

    i = 12;
    data_ptr = PQErase(prior_q, &i);
    i = 0;
    TEST(data_ptr == int_arr + 24);
    TEST(12 == *((size_t *)data_ptr));

    TEST(PQSize(prior_q) == 47);
    TEST(48 == *((size_t *)PQPeek(prior_q)));

    i = 222;
    data_ptr = PQErase(prior_q, &i);
    i = 0;
    TEST(data_ptr == NULL);

    TEST(PQSize(prior_q) == 47);
    TEST(48 == *((size_t *)PQPeek(prior_q)));

    i = 33;
    data_ptr = PQEraseIf(prior_q, &i, IsDivideByCriteria);
    i = 0;
    TEST(data_ptr == int_arr + 0);
    TEST(0 == *((size_t *)data_ptr));

    TEST(PQSize(prior_q) == 46);
    TEST(48 == *((size_t *)PQPeek(prior_q)));

    i = 33;
    data_ptr = PQEraseIf(prior_q, &i, IsDivideByCriteria);
    i = 0;
    TEST(data_ptr == int_arr + 66);
    TEST(33 == *((size_t *)data_ptr));

    TEST(PQSize(prior_q) == 45);
    TEST(48 == *((size_t *)PQPeek(prior_q)));

    i = 33;
    data_ptr = PQEraseIf(prior_q, &i, IsDivideByCriteria);
    i = 0;
    TEST(data_ptr == NULL);

    TEST(PQSize(prior_q) == 45);
    TEST(48 == *((size_t *)PQPeek(prior_q)));

    i = 48;
    data_ptr = PQEraseIf(prior_q, &i, IsDivideByCriteria);
    i = 0;
    TEST(data_ptr == int_arr + 96);
    TEST(48 == *((size_t *)data_ptr));

    TEST(PQSize(prior_q) == 44);
    TEST(47 == *((size_t *)PQPeek(prior_q)));

    i = 48;
    data_ptr = PQEraseIf(prior_q, &i, IsDivideByCriteria);
    i = 0;
    TEST(data_ptr == NULL);

    TEST(PQSize(prior_q) == 44);
    TEST(47 == *((size_t *)PQPeek(prior_q)));

    PQClear(prior_q);

    TEST(PQSize(prior_q) == 0);
    TEST(PQIsEmpty(prior_q));

    for (i = 0; i < 10; ++i)
    {
        TEST(0 == PQEnqueue(prior_q, (int_arr + i)));
    }

    TEST(PQSize(prior_q) == 10);
    TEST(!PQIsEmpty(prior_q));

    for (i = 0; i < 5; ++i)
    {
        TEST((99 - i) == *((size_t *)PQPeek(prior_q)));
        TEST((99 - i) == *((size_t *)PQDequeue(prior_q)));
    }

    for (i = 0; i < 5; ++i)
    {
        TEST((4 - i) == *((size_t *)PQPeek(prior_q)));
        TEST((4 - i) == *((size_t *)PQDequeue(prior_q)));
    }

    TEST(PQSize(prior_q) == 0);
    TEST(PQIsEmpty(prior_q));

    PQDestroy(prior_q);
    prior_q = NULL;
}


/* Utility funcs */
/******************************************************************/
int PrioritizeLongInt(const void *d1, const void *d2)
{
    assert(d1);
    assert(d2);

    return *((size_t *)d1) - *((size_t *)d2);
}


int IsDivideByCriteria(const void *data, const void *criteria)
{
    assert(data);
    assert(criteria);

    return !(*((size_t *)criteria) % *((size_t *)data));
}




/* space */
