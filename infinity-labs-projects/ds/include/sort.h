/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       2.3.0                                           ~
 *                                                               *
 ~ Author        OL110 Students                                  ~
 * Reviewer      Yinon Yishay                                    *
 ~ Description   Sorting Algorithm - Header_File                 ~
 * Group         OL110                                           *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __OL110SORT_H__
#define __OL110SORT_H__

#include <stddef.h> /* size_t */ 
 
void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

int CountingSort(int *arr, int *dest_arr, size_t size);

int RadixSort(int *arr, int *dest_arr, size_t size);


/* A recursive binary search function. It returns
 location of num in given array arr[l..r] is present,
 otherwise -1*/
int BinarySearchRecursive(const int *arr, size_t size, int num);

/* A iterative binary search function. It returns
 location of x in given array arr is present,
 otherwise -1 */
int BinarySearchIterative(const int *arr, size_t size, int num);

int MergeSort(int *arr_to_sort, size_t num_elements);

void QuickSort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

#endif /* __SORT_OL_110_H__ */