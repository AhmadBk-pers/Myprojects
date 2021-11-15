/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       3.0.0                                           ~
 *                                                               *
 ~ Author        OL110 Students                                  ~
 * Reviewer      Yinon Yishay                                    *
 ~ Description   Binary Heap DS - Header_File                    ~
 * Group         OL110                                           *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __HEAP_OL_110_H__
#define __HEAP_OL_110_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;

typedef int (*compare_t)(const void *, const void *);

/*  O(1) */
/*  in: compare function (<,>,= 0 if val1 is <,>,= val2 respectively)   */
/*  Creates a max heap                                                  */
/*  ret: heap_t pointer on success, NULL on failure                     */
heap_t *HeapCreate(compare_t compare);

/*  O(1) */
/*  in: heap ptr to destroy */
void HeapDestroy(heap_t *heap);

/* O(1) */
/*  in: binary heap                             */
/*  ret: 0 if not empty, other number otherwise */
int HeapIsEmpty(const heap_t *heap);

/* O(1) */
/*  in: binary heap                         */
/*  retrieve the heap's size (# elements)   */
size_t HeapSize(const heap_t *heap);

/* O(log n) */
/*  in: heap to place data in                   */
/*  data to insert                              */
/*  ret: 0 on Success, other number on failure  */
int HeapPush(heap_t *heap, void *data);

/* O(log n) */
/*  in: non-empty binary heap   */
/*  ret: removed max element    */
void *HeapPop(heap_t *heap);

/* O(1) */
/*  in: non-empty binary heap           */
/*  ret: data of max element from heap  */
void *HeapPeek(const heap_t *heap);

/* O(n) */
/*  find and remove first occurence of 'data' element in the heap   */
/*  in: binary heap                                                 */
/*      data of element to be removed                               */
/*  return : the value of the element removed, if found             */
/*           NULL if not found                                      */
void *HeapRemove(heap_t *heap, const void *criteria);

/* O(n) */
/*    find and remove first occurence of 'data' element in the heap    */
/*    in: binary heap                                                    */
/*        data of element to be removed                                */
/*        boolean is_match function                                    */
/*    return : the value of the element removed, if found                */
/*            NULL if not found                                        */
void *HeapRemoveIf(heap_t *heap, const void *criteria, 
            int (*is_match)(const void *data, const void *criteria));


#endif /* __HEAP_OL_110_H__ */