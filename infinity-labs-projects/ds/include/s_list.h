#ifndef __S_LIST_H__
#define __S_LIST_H__

#include <stddef.h> /* size_t  */

typedef struct slist slist_t;
typedef struct sl_node * sl_iter_t;

slist_t *SLCreate();
void SLDestroy(slist_t *list);

size_t SLCount(const slist_t *list);
int SLIsEmpty(const slist_t *list);

sl_iter_t SLBegin(const slist_t *); /*Begin */
sl_iter_t SLEnd(const slist_t *);   /* End */
sl_iter_t SLNext(const sl_iter_t);  /* Next */

/* returns 1 for equality and 0 otherwise */
int SLIterIsEqual(const sl_iter_t i1, const sl_iter_t i2); 

sl_iter_t SLAddAfter(sl_iter_t, void *data);
sl_iter_t SLAddBefore(sl_iter_t, void *data);

sl_iter_t SLRemoveAfter(sl_iter_t);
sl_iter_t SLRemove(sl_iter_t);

void *SLGetValue(const sl_iter_t);
void SLSetValue(sl_iter_t, void *data);

sl_iter_t SLFind(const slist_t *, const void * data, 
                        int (*CompareTo)(const void *, const void *));

/* return 0 on success and another number otherwise.  Stop if not 0*/
int SLForEach(sl_iter_t start, sl_iter_t end, 
		int (*Action)(void * data, void *param), void *param); 

/* Concatenate 'append' to the end of 'base'. 
Function call leaves 'append' empty */
void SLAppend(slist_t *base,  slist_t *append);

#endif /* __S_LIST_H__ */
