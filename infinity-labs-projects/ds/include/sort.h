/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       1.0.0                                           ~
 *                                                               *
 ~ Author        OL110 Students                                  ~
 * Reviewer      Yinon Yishay                                    *
 ~ Description   Sorting Algorithm - Header_File   				 ~
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

#endif /* __SORT_OL_110_H__ */
