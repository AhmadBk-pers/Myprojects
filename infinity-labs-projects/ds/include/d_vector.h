#ifndef __DVECTOR_H__
#define __DVECTOR_H__

#include <stddef.h> /* size_t */

/* OL110 version: 1 */
typedef struct vector vector_t;

vector_t *DVectorCreate(size_t capacity);
void DVectorDestroy(vector_t *vector);
int DVectorPushBack(vector_t *vector, void *element); /* have the vector stay on the same pointer; return 0 on success and another number otherwise */
void *DVectorPopBack(vector_t *vector); /* returns the removed element */
void *DVectorGet(const vector_t *vector, size_t index);
void DVectorSet(vector_t *vector, size_t index, void *element);
size_t DVectorGetSize(const vector_t *vector);
size_t DVectorGetCapacity(const vector_t *vector);
int DVectorReserve(vector_t *vector, size_t new_capacity); /* have the vector stay on the same pointer; return 0 on success and another number otherwise */
int DVectorShrinkToFit(vector_t *vector); /* have the vector stay on the same pointer; return 0 on success and another number otherwise */

#endif /* __DVECTOR_H__ */

