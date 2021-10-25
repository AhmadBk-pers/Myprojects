/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       1.0.1                                       ~
 *                                                           *
 ~ Author        OL110 Students                              ~
 * Reviewer      Yinon Yishay                                *
 ~ Description   Fixed Size Allocator module - Header_File   ~
 * Group         OL110                                       *
 ~ Company       ILRD Ramat Gan                              ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __FSA_OL_110_H__
#define __FSA_OL_110_H__

#include <stddef.h> /* size_t */

typedef void * fsa_t;

/* O(n) */
/* initializes the mem_pool with as many blocks of 'block_size' bytes as possible */
/* block size will be alligned to Word_Size */
/* returns the fixed size allocator to manage mem_pool */
fsa_t FSAInit(void *mem_pool, size_t pool_size, size_t block_size);

/* O(1) */
/* returns block available for use */
/* returns NULL if no memory is available */
void *FSAAlloc(fsa_t fsa);

/* O(1) */
/* free the given block */
/* free to freed block is UB */
void FSAFree(fsa_t fsa, void *block);

/* O(1) */
/* returns number of total bytes needed (overhead included) */
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);

/* O(n) */
/* returns number of free blocks */
size_t FSACountFree(const fsa_t fsa);

#endif /* __FSA_OL_110_H__ */
