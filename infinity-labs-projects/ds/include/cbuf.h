/* VERSION: 1.0.0 */
#ifndef __CBUFF_H__
#define __CBUFF_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

typedef struct cb cbuff_t;

cbuff_t *CBCreate(size_t capacity);

void CBDestroy(cbuff_t *cbuff);

/* returns (capacity - written size) */
size_t CBFreeSpace(const cbuff_t *cbuff);

size_t CBBufsiz(const cbuff_t *cbuff); /* returns the capacity */

/*ssize_t read(int fd, void *buf, size_t count); *//* origin */

/* returns the number of bytes read */
ssize_t CBRead(cbuff_t *cbuff, void *buf, size_t count);

/* returns the number of bytes written */
ssize_t CBWrite(cbuff_t *cbuff, const void *buf, size_t count);

int CBIsEmpty(const cbuff_t *cbuff);

#endif /* __CBUFF_H__ */
