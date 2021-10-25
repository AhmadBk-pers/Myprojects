/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       1.0.3                                           ~
 *                                                               *
 ~ Author        OL110 Students                                  ~
 * Reviewer      Yinon Yishay                                    *
 ~ Description   Variable Size Allocator module - Header_File    ~
 * Group         OL110                                           *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __VSA_OL_110_H__
#define __VSA_OL_110_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

/* O(1) */
/* initiates a vsa */
/* input: pool: pointer to allocated memory                                 */
/*        pool_size:  it's size in bytes                                    */
/* returns: if size < 16, returns NULL,                                     */
/*          if 16 <= size < 24, returns useless vsa (all VSAAlloc will fail)*/
/*          else returns an initialized and ready for use vsa               */
vsa_t *VSAInit(void *pool, size_t pool_size);

/* O(n) */
/* input: vsa: vsa                                              */
/*        size: a size of block to allocate                     */
/* returns: a pointer to an allocated block of the desired size */
/*            or NULL if doesn't exist                          */
void *VSAAlloc(vsa_t *vsa, size_t size);

/* O(1) */
/* input: block: a block to free */
/*     frees it                  */
void VSAFree(void *block);

/* O(n) */
/* input: receives a vsa */
/* returns: the largest contiguous block size that can be allocated */
size_t VSALargestBlockAvailable(vsa_t *vsa);

#endif /* __VSA_OL_110_H__ */
