/******************************************************

doubly linked list

API

version 3

12.09.21

******************************************************/

#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

typedef struct dlist dlist_t;

typedef struct 
{
    struct dl_node *internal;
} dl_iter_t;

dlist_t *DLCreate(void);

void DLDestroy(dlist_t *dlist);

/* returns 0 if the list contains something and another number if it's empty */
int DLIsEmpty(const dlist_t *dlist);

/*return the first valid member*/
dl_iter_t DLBegin(const dlist_t *dlist); 

/*return the next of the last valid member*/
dl_iter_t DLEnd(const dlist_t *dlist); 

dl_iter_t DLNext(dl_iter_t dl_iter);

dl_iter_t DLPrev(dl_iter_t dl_iter);

size_t DLSize(const dlist_t *dlist);

void *DLGetData(dl_iter_t dl_iter);

void DLSetData(dl_iter_t dl_iter, void *data);

/* returns 0 for inequality and another number otherwise */
int DLIsIterEqual(dl_iter_t dl_i1, dl_iter_t dl_i2);

/* inserts before and returns an iterator to the inserted node,
	or list end on failure */
dl_iter_t DLInsert(dl_iter_t dl_iter, void *data);

/* removes specified iter and returns its next */
dl_iter_t DLRemove(dl_iter_t dl_iter);

/* inserts from the back of the list and returns the inserted node */
dl_iter_t DLPushBack(dlist_t *dlist, void *data);

/* inserts in the front of list and returns the inserted node */
dl_iter_t DLPushFront(dlist_t *dlist, void *data);

/* removes the last node and returns its data */
void *DLPopBack(dlist_t *dlist);

/* removes the head node and returns its data */
void *DLPopFront(dlist_t *dlist);

/* inserts a portion from src list to before destined place in another list */
/* user is responsible for correct order of iterators sent to the function */
/* inclusive for start and to exclusive for end */
void DLSplice(dl_iter_t dest, dl_iter_t src_from, dl_iter_t src_to);

/* inclusive for start and to exclusive for end */
/* returns 0 on success (and so "action" function), and another on failure */
int DLForEach(dl_iter_t from, dl_iter_t to,
			  int (*action)(void *data, void *param), void *param); 

/* DLFind returns "to" if doesn't find data */
/* is_match returns 0 on mismatch and another number for match */
dl_iter_t DLFind(dl_iter_t from, dl_iter_t to, const void *data,
                 int (*is_match)(const void *, const void *));

/* returns 0 for success and another number otherwise, and populates the
    destination list with the data of matching nodes */
/* is_match returns 0 on mismatch and another number for match */
int DLMultiFind(dl_iter_t from, dl_iter_t to, dlist_t *dest,
                const void *data, int(*is_match)(const void *, const void *));

#endif /* __DLIST_H__ */