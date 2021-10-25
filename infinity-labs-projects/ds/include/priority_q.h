/* OL110 Priotity Queue Version: 1 */

#ifndef __PRIORITY_Q_OL110_ILRD_H__
#define __PRIORITY_Q_OL110_ILRD_H__

#include <stddef.h> /* size_t */

typedef struct priority_q pq_t;

/* creates an empty queue that uses a prioritize function */
/* prioritize high over low */
/* Returns a pointer to the new p.q., or NULL on failure */
/* O(1) */
pq_t *PQCreate(int (*prioritize)(const void *data1, const void *data2));

/* destroys a given queue */
/* O(n) */
void PQDestroy(pq_t *prior_q);

/* returns 0 if the queue contains something and another number otherwise */
/* O(1) */
int PQIsEmpty(const pq_t *prior_q);

/* returns the number of elements in the queue */
/* O(n) */
size_t PQSize(const pq_t *prior_q);

/* returns 0 on success and another number otherwise */
/* inserts the given data in its proper place */
/* O(n) */
int PQEnqueue(pq_t *prior_q, void *data);

/* returns value of the prior element, and removes it */
/* O(1) */
void *PQDequeue(pq_t *prior_q);

/* returns the value of the prior element */
/* O(1) */
void *PQPeek(const pq_t *prior_q);

/* removes an element with the value 'data' and given priority */
/* return erased data, if not found, return NULL */
/* O(n) */
void *PQErase(pq_t *prior_q, const void *data);

/* removes an element matching the given criteria */
/* is_match returns 0 if criteria aren't matched */
/* and another number otherwise */
/* return erased data, if not found, return NULL */
/* O(n) */
void *PQEraseIf(pq_t *prior_q, const void *criteria, 
    int (*is_match)(const void *data, const void *criteria));

/* removes all elements from the queue */
/* O(n) */
void PQClear(pq_t *prior_q);



#endif /* __PRIORITY_Q_OL110_ILRD_H__ */
