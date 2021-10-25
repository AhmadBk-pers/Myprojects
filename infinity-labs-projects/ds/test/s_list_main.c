#include <stdio.h>
#include <assert.h>
#include "s_list.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SUCCESS 0
#define FAILURE 1
#define PRINT_MALLOC_ERROR(func) (printf("Couldn't allocate memory for " #func "."))
#define HANDLE_ALLOC(obj) if (!obj) { printf("Couldn't allocate memory"\
                            "in line %d.", __LINE__); return 1; }

int ComputeSum(void *data, void *param)
{
    int *param_to_intptr = (int *)param;
    *param_to_intptr = *(int *)param + *(int *)data;
    param = param_to_intptr;

    return SUCCESS;
}

int Add(void *add_to, void *value)
{
    int *temp = (int *)add_to;
    *temp = *temp + *(int *)value;
    add_to = temp;

    return SUCCESS;
}

int InitList(slist_t *list)
{
	sl_iter_t iter;
    char values[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    size_t i = 0;

    assert(list && SLIterIsEqual(SLBegin(list), SLEnd(list)));

    iter = SLBegin(list);
    iter = SLAddBefore(SLBegin(list), &values[0]);

    for (i = 1; i < sizeof(values)/sizeof(*values); ++i)
    {
        iter = SLAddAfter(SLBegin(list), &values[i]);
        HANDLE_ALLOC(iter)
    }/* The order in list:a->f->e->d->c->b->end */

	return 0;
}

int TestForEach()
{
    int result = 0;
    slist_t *list = SLCreate();
    sl_iter_t iter = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t i = 0;
    int sum = 0;
    int addition = 8;

    if (!list)
    {
        PRINT_MALLOC_ERROR("TestForEach");
        return 0;
    }

    iter = SLBegin(list);

    for (i = sizeof(values)/sizeof(values[0]) - 1;
                i < sizeof(values)/sizeof(values[0]); --i)
    {
        iter = SLAddBefore(iter, &values[i]);
    }/* The order in list:1->2->3->4->5->6->7->8->9->end */

    result += (9 != SLCount(list));
    result += SLIsEmpty(list);
    result += (!SLIterIsEqual(SLBegin(list), iter));

    SLForEach(SLBegin(list), SLEnd(list), &ComputeSum, &sum);
    result += !(45 == sum);
    SLForEach(iter ,SLNext(SLNext(iter)), &Add, &addition);
    /* nodes 1->2  will become 9->10*/
    sum = 0;
    SLForEach(iter, SLEnd(list), &ComputeSum, &sum);
    result += !(61 == sum);

    SLDestroy(list);
    return result;
}

int ChCmp(const void *c1, const void *c2)
{
    return ((char *)MAX(c1, c2) - (char *)MIN(c1, c2));
    /*return (MAX(char(c1), char(c2)) - MIN(char(c1), char(c2)));*/
}

int TestFind()
{
    int result = 0;
    slist_t *list = SLCreate();
    sl_iter_t iter = NULL;
    char values[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    size_t i = 0;

    HANDLE_ALLOC(list)

    iter = SLBegin(list);
    iter = SLAddBefore(SLBegin(list), &values[0]);

    for (i = 1; i < sizeof(values)/sizeof(*values); ++i)
    {
        iter = SLAddAfter(SLBegin(list), &values[i]);
        HANDLE_ALLOC(iter)
    }/* The order in list:a->f->e->d->c->b->end */

    /* find value in the middle */
    iter = SLFind(list, &values[2], &ChCmp);
    result += (&values[2] != SLGetValue(iter));
    printf("The result in line %d is %d.\n", __LINE__, result);
    iter = SLRemove(iter);
    /* find non-existant value */
    iter = SLFind(list, &values[2], &ChCmp);
    result += (!SLIterIsEqual(SLEnd(list), iter));
/*    result += (SLGetValue(SLEnd(list)) == SLGetValue(iter));*/
    printf("The result in line %d is %d.\n", __LINE__, result);
    iter = SLBegin(list);
    /* find value in the fisrt node */
    iter = SLFind(list, &values[0], &ChCmp);
    result += (&values[0] != SLGetValue(iter));
    printf("The result in line %d is %d.\n", __LINE__, result);

    SLDestroy(list);
    return result;
}

int TestAddRemove()
{
    slist_t *list = SLCreate();
    sl_iter_t iter = NULL;
    int result = 0;

    if (!list)
    {
        printf("Couldn't allocate memory for TestAddRemove.");
        return 0;
    }

    iter = SLAddBefore(SLBegin(list), (void *)1);
    iter = SLAddBefore(SLBegin(list), (void *)2);
    iter = SLAddBefore(SLBegin(list), (void *)3);
    iter = SLAddBefore(SLBegin(list), (void *)4);
    iter = SLAddBefore(SLBegin(list), (void *)5);
    iter = SLAddBefore(SLBegin(list), (void *)6);
    /* The order in list:6->5->4->3->2->1->end */
    

    result += (6 != SLCount(list));
    result += ((void *)6 != SLGetValue(iter));
    result += ((void *)5 != SLGetValue(SLNext(iter)));
    SLRemoveAfter(iter);
    result += ((void *)4 != SLGetValue(SLNext(iter)));
    result += ((void *)6 != SLGetValue(iter));

    result += (5 != SLCount(list));
    result += (SLIsEmpty(list));
    result += (SLBegin(list) == SLEnd(list));
    /* list:6->4->3->2->1->end*/

    SLSetValue(iter, (void *)8);
    result += ((void *)8 != SLGetValue(iter));

    iter = SLRemove(iter);
    result += ((void *)4 != SLGetValue(iter));
    result += (!SLIterIsEqual(iter, SLBegin(list)));
    iter = SLRemove(iter);
    result += ((void *)3 != SLGetValue(iter));
    iter = SLRemove(iter);
    result += ((void *)2 != SLGetValue(iter));
    iter = SLRemove(iter);
    result += ((void *)1 != SLGetValue(iter));

    result += (1 != SLCount(list));
    result += (SLIsEmpty(list));
    result += (!SLIterIsEqual(iter, SLBegin(list)));
    result += (SLIterIsEqual(iter, SLEnd(list)));
    iter = SLRemove(iter);
    result += (!SLIterIsEqual(iter, SLEnd(list)));

    SLDestroy(list);

    return result;
}

int TestCreateDestroy()
{
    slist_t *list = SLCreate();
    int result = 0;
    if (!list)
    {
        printf("Couldn't allocate memory for TestCreateDestroy.");
        return 0;
    }

    result += (0 != SLCount(list));
    result += (!SLIsEmpty(list));
    result += (SLBegin(list) != SLEnd(list));
    printf("The result in line %d is %d.\n", __LINE__, result);
    SLAddBefore(SLBegin(list), (void *)1);

    SLDestroy(list);

    return result;
}

void AddNodes(slist_t *list)
{
	SLAddBefore(SLBegin(list), (void *)1);
    SLAddBefore(SLBegin(list), (void *)2);
    SLAddBefore(SLBegin(list), (void *)3);
    SLAddBefore(SLBegin(list), (void *)4);
    SLAddBefore(SLBegin(list), (void *)5);
    SLAddBefore(SLBegin(list), (void *)6);

}

int TestAppend()
{
    slist_t *list1 = SLCreate();
    slist_t *list2 = SLCreate();
    size_t size1, size2;
    int result = 0;
    if (!list1 || !list2)
    {
        if (list1)
        {
            SLDestroy(list1);
        }
        if (list2)
        {
            SLDestroy(list2);
        }
        printf("Couldn't allocate memory for TestAppend.");
        return 1;
    }

    AddNodes(list1);
    AddNodes(list2);
    size1 = SLCount(list1);
    size2 = SLCount(list2);
    SLAppend(list1, list2);
    result += (0 != SLCount(list2));
    result += ((size1 + size2) != SLCount(list1));

    SLDestroy(list1);
    SLDestroy(list2);

    return result;
}

void TestProgram()
{
    int result = 0;

    result += TestCreateDestroy();
    printf("The result in line %d is %d.\n", __LINE__, result);
    result += TestAddRemove();
    printf("The result in line %d is %d.\n", __LINE__, result);
    result += TestFind();
    printf("The result in line %d is %d.\n", __LINE__, result);
    result += TestForEach();
    printf("The result in line %d is %d.\n", __LINE__, result);
    result += TestAppend();
    printf("The result in line %d is %d.\n", __LINE__, result);

    printf("The tests %s.\n", result ? "Failed." : "Succeeded!");
}

int main()
{
    TestProgram();

    return 0;
}
