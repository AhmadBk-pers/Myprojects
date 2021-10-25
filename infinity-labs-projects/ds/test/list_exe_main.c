#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "list_exe.h"


void PrintSList(const node_t *head)
{
    assert(head);

    while (NULL != head)
    {
        printf("%s ->", (char *)(head->data));
        head = head->next;
    }

    printf("NULL\n");
}

void PrintSListLoop(const node_t *head)
{
    const node_t *iter = head;

    assert(head);

    printf("%s ->", (char *)(iter->data));
    iter = iter->next;

    while (iter != head)
    {
        printf("%s ->", (char *)(iter->data));
        iter = iter->next;
    }

    printf("repeats from here.\n");
}

void Destroy(node_t *head)
{
    node_t *next;

    assert(head);

    next = head->next;
    while (NULL != next)
    {
        /*printf("%s\n", (char *)(head->data));*/
        free(head);
        head = next;
        next = head->next;
    }

    free(head);
    head = NULL;
}

void DestroyLoop(node_t *const head)
{
    node_t *iter = head;
    node_t *next;

    assert(head);

    next = iter->next;

    /*printf("%s\n", (char *)(iter->data));*/
    free(iter);
    iter = next;

    while (iter != head)
    {
        next = iter->next;
        /*printf("%s\n", (char *)(iter->data));*/
        free(iter);
        iter = next;
    }

}

node_t *AddBefore(node_t *iter, void *data)
{
    node_t *new_list_iter;

    assert(iter);

    new_list_iter = (node_t *)malloc(sizeof(*new_list_iter));
    if (!new_list_iter)
    {
        return NULL;
    }

    new_list_iter->data = iter->data;
    new_list_iter->next = iter->next;

    iter->next = new_list_iter;
    iter->data = data;

    return iter;
}

node_t *Remove(node_t *iter)
{
    node_t *next;

    assert(iter);

    next = iter->next;

    iter->data = next->data;
    iter->next = next->next;

    free(next);
    next = NULL;

    return iter;
}

node_t *FlipInNewMemory(node_t *head)
{ /* if malloc fails, returns NULL */
    node_t *old_list_iter = head;
    node_t *new_list_head;

    assert(head);

    new_list_head = (node_t *)malloc(sizeof(*new_list_head));
    if (!new_list_head)
    {
        return NULL;
    }

    new_list_head->data = NULL;
    new_list_head->next = NULL;

    while(NULL != head)
    {
        node_t *new_list_temp = AddBefore(new_list_head, head->data);

        if (!new_list_temp)
        {
            Destroy(new_list_head);
            return NULL;
        }

        new_list_head = new_list_temp;

        old_list_iter = head->next;
        free(head);
        head = old_list_iter;
    }

    return new_list_head;
}

node_t *Create()
{
    char *strs[] = {"a", "b", "c", "d", "e"};
    size_t i = 0; /* for loop */
    node_t *new_list_head = (node_t *)malloc(sizeof(*new_list_head));

    if (!new_list_head)
    {
        return NULL;
    }

    new_list_head->data = strs[0];
    new_list_head->next = NULL;

    for (i = 1; i < sizeof(strs) / sizeof(*strs); ++i)
    {
        node_t *iter = AddBefore(new_list_head, strs[i]);

        if (!iter)
        {
            Destroy(new_list_head);
            return NULL;
        }

        new_list_head = iter;
    }
    /* returns a list : e->d->c->b->a->end*/
    return new_list_head;
}

node_t *CreateIntersectedTo(node_t *connect_to)
{
    char *strs[] = {"f", "g", "h", "j"};
    size_t i = 0; /* for loop */
    node_t *new_list_head = (node_t *)malloc(sizeof(*new_list_head));

    if (!new_list_head)
    {
        return NULL;
    }

    new_list_head->data = strs[sizeof(strs) / sizeof(*strs) - 1];
    new_list_head->next = connect_to;

    for (; i < sizeof(strs) / sizeof(*strs) - 1; ++i)
    {
        node_t *iter = AddBefore(new_list_head, strs[i]);

        if (!iter)
        {
            Destroy(new_list_head);
            return NULL;
        }

        new_list_head = iter;
    }
    /* returns a list : f->g->h->j-> connect_to*/
    return new_list_head;
}

node_t *CreateLoop()
{
    char *strs[] = {"a", "b", "c", "d", "e"};
    size_t i = 0; /* for loop */
    node_t *new_list_head;
    node_t *new_list_end = (node_t *)malloc(sizeof(*new_list_end));

    if (!new_list_end)
    {
        return NULL;
    }

    new_list_end->data = strs[0];
    new_list_head = new_list_end;

    for (i = 1; i < sizeof(strs) / sizeof(*strs); ++i)
    {
        node_t *iter = AddBefore(new_list_head, strs[i]);

        if (!iter)
        {
            Destroy(new_list_head);
            return NULL;
        }

        /* since AddBefore actually adds after, the real end node would be
            the new added node after the end */
        if (i == 1)
        {
            new_list_end = iter->next;
        }

        new_list_head = iter;
    }

    new_list_end->next = new_list_head;
    /* returns a list : e->d->c->b->a-> repeat   */
    return new_list_head;
}

void TestFlip()
{
    node_t *head = Create();
    if (!head)
    {
        printf("Couldn't allocate memory to test Flip.\n");
        return;
    }

    while (NULL != head->next)
    {
        printf("Before:\n");
        PrintSList(head);
        head = Flip(head);
        if (!head)
        {
            return;
        }

        printf("Flipped:\n");
        PrintSList(head);
        printf("\n");
        head = Remove(head);
    }

    Destroy(head);
}

void TestHasLoop()
{
    node_t *head = CreateLoop();
    node_t * const head_cnst = head;
    if (!head)
    {
        printf("Couldn't allocate memory to test HasLoop.\n");
        return;
    }

    PrintSListLoop(head_cnst);
    printf("The looped list is %s\n", HasLoop(head_cnst) ? "approved -> Success!" :
                "not approved -> Failed.");
    head = Remove(head);
    head = head->next;

    while (head_cnst != head->next)
    {
        PrintSListLoop(head_cnst);
        printf("The looped list is %s\n", HasLoop(head_cnst) ? "approved -> Success!" :
                    "not approved -> Failed.");
        head = Remove(head);
    }
    PrintSListLoop(head_cnst);
    printf("The looped list is %s\n", HasLoop(head_cnst) ? "approved -> Success!" :
                "not approved -> Failed.");
    DestroyLoop(head_cnst);


    head = Create();
    if (!head)
    {
        printf("Couldn't allocate memory to test HasLoop.\n");
        return;
    }
    PrintSList(head);
    printf("The not-looped list is %s\n", HasLoop(head) ? "not approved -> Failed." : "approved -> Success!");
    Destroy(head);

    printf("\n\n");
}

void TestFindIntersection()
{
    node_t *head1 = Create();
    node_t *head2;
    node_t *intersection;
    if (!head1)
    {
        printf("Couldn't allocate memory to test FindIntersection.\n");
        return;
    }

    head2 = CreateIntersectedTo(head1);
    if (!head2)
    {
        printf("Couldn't allocate memory to test FindIntersection.\n");
        return;
    }

    PrintSList(head1);
    PrintSList(head2);
    intersection = FindIntersection(head1, head2);
    if (intersection)
    {
        printf("The value at the intersection is %s. -> %s\n",
         (char *)intersection->data, (intersection->data == head1->data) ?
         "Success!" : "Failed.");
    }
    else
    {
        printf("There is no intersection. -> Failed\n");
    }
    
    Destroy(head2);
    head2 = NULL;
}

int main()
{
    TestFlip();
    TestHasLoop();
    TestFindIntersection();

    return 0;
}
