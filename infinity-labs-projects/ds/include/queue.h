/* VERSION 1.0.0 */
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */


typedef struct queue queue_t;

queue_t *QCreate(); 
/*O(1)*//* returns NULL in case of failure, or new queue*/

void QDestroy(queue_t *queue);/*O(n)*/

int QIsEmpty(const queue_t *queue);/*O(1)*/

size_t QGetSize(const queue_t *queue);/*O(n)*/

int QEnqueue(queue_t *queue, void *data); 
/*O(1)*//* returns 1 in case of failure, else 0 */

void *QDequeue(queue_t *queue); /*O(1)*/

void *QPeek(const queue_t *queue);
 /*O(1)*//* returns the data in the front of the queue */

void QAppend(queue_t *base, queue_t *append);
 /*O(1)*//* joins 2 queues *//* empties append, but doesn't destroy it */


#endif /*__QUEUE_H__*/
