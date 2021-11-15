/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Sorting module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stddef.h>		/*size_t*/
#include <assert.h>		/*assert*/
#include <stdlib.h>		/*calloc*/
#include <string.h>		/*memcpy*/

static void Swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

static int Merge(int *arr_to_sort, int left, int mid, int right);
static int MergeSortImpl(int *arr_to_sort, int left, int right);
static int BinarySearchRecursiveimpl(int *arr, int left, int right, int num);
static size_t Partiton(void *arr, size_t from, size_t to, size_t size, 
					int (*compar)(const void *, const void*), size_t piviot);
static void QuickSortImpl(void *arr, size_t from, size_t to, size_t size, 
									int (*compar)(const void *, const void*));

void BubbleSort(int *arr, size_t size)
{
	size_t swapped = 1, i = 0, j = 0;
	
	assert(arr);
	
	for (i = 0; (i < size - 1) && swapped; i++)
	{
		swapped = 0;
		
		for (j = 0; j < size - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
				swapped = 1;
			}
		}
	}
}

static void ShiftRight(int *arr, int from_index, int to_index)
{
	int i = 0;
	
	assert(arr);
	
	for (i = to_index - 1; i >= from_index; i--)
	{
		arr[i + 1] = arr[i];
	}
}

void InsertionSort(int *arr, size_t size)
{
	int i = 0, j = 0, temp = 0;
	
	assert(arr);
	
	for (i = 1; i < (int)size; i++)
	{
		for (j = i ; j > 0; j--)
		{
			if (arr[j - 1] <= arr[i])
			{
				break;
			}
		}
		temp = arr[i];
		
		ShiftRight(arr, j, i);
		
		arr[j] = temp;
	}
}

void SelectionSort(int *arr, size_t size)
{
	int i = 0, j = 0;
	
	assert(arr);
	
	
	
	for (i = 0; i < (int)size - 1; i++)
	{
		int min = arr[i];
		int min_index = i;
		
		for (j = i; j < (int)size; j++)
		{
			if (arr[j] <= min)
			{
				min = arr[j];
				min_index = j;
			}
		}
		
		ShiftRight(arr, i, min_index - 1);
				
		arr[i] = min;
	}
}

int CountingSort(int *dest_arr, int *arr, size_t size)
{
	size_t *auxility_arr = NULL;
	int min = 0, max = 0, i = 0;
	size_t size_of_auxility = 0;
	
	assert(arr);
	assert(dest_arr);
	
	max = arr[0];
	min = arr[0];
	
	for (i = 0; i < (int)size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
		else if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	
	size_of_auxility = max - min + 1;
	auxility_arr = (size_t *)calloc(size_of_auxility, sizeof(size_t));
	
	if (!auxility_arr)
	{
		return 1;
	}
	
	auxility_arr -= min;
	
	for (i = 0; i < (int)size; i++)
	{
		auxility_arr[arr[i]] ++;
	}
	
	auxility_arr[min] -= 1;
	
	for (i = min + 1; i <= max; i++)
	{
		auxility_arr[i] += auxility_arr[i - 1];
	}
	
	for (i = 0; i < (int)size; i++)
	{
		dest_arr[auxility_arr[arr[size - 1 - i]]--] = arr[size - 1 - i];
	}
	
	free(auxility_arr + min);
	auxility_arr = NULL;
	
	return 0;
}

int RadixSort(int *dest_arr, int *arr, size_t size)
{
	int mask = 0xf, i = 0, nibbles_count = 0;
	size_t *auxility_arr = NULL;
	int *arr_ptr = NULL;
	size_t size_of_auxility = 16;
	
	assert(arr);
	assert(dest_arr);
	
	auxility_arr = (size_t *)calloc(size_of_auxility, sizeof(size_t));
	
	if (!auxility_arr)
	{
		return 1;
	}
	
	for (nibbles_count = 0; nibbles_count < 16; ++nibbles_count)
	{
		for (i = 0; i < (int)size; i++)
		{
			auxility_arr[(arr[i] >> (4 * nibbles_count)) & mask] += 1;
		}
		
		auxility_arr[0] -= 1;
		
		for (i = 1; i < 16; i++)
		{
			auxility_arr[i] += auxility_arr[i - 1];
		}
		
		for (i = 0; i < (int)size; i++)
		{
			dest_arr[auxility_arr[(arr[size - 1 - i] >> (4 * nibbles_count)) & 
												mask]--] = arr[size - 1 - i];
		}
		
		for (i = 0; i < 16; i++)
		{
			auxility_arr[i] = 0;
		}
		
		arr_ptr = dest_arr;
		dest_arr = arr;
		arr = arr_ptr;
		
	}
	
	memcpy(dest_arr, arr, size * sizeof(int));
	
	free(auxility_arr);
	auxility_arr = NULL;
	
	return 0;
	
	
}

int BinarySearchRecursive(int *arr, size_t size, int num)
{
	return BinarySearchRecursiveimpl(arr, 0, size - 1, num);
}

static int BinarySearchRecursiveimpl(int *arr, int left, int right, int num)
{
	int index = (left + right) / 2;

	assert(arr);

	if (left > right)
	{
		return -1;
	}

	if (arr[index] < num)
	{
		return BinarySearchRecursiveimpl(arr, index + 1, right, num);
	}
	else if (arr[index] > num)
	{
		return BinarySearchRecursiveimpl(arr, left, index - 1, num);
	}
	else
	{
		return index;
	}
}

int BinarySearchIterative(int *arr, size_t size, int num)
{
	int index = 0, left = 0, right = size - 1;

	assert(arr);

	while (left <= right)
	{
		index = (left + right) / 2;

		if (arr[index] < num)
		{
			left = index + 1;
		}
		else if (arr[index] > num)
		{
			right = index - 1;
		}
		else
		{
			return index;
		}
	}
	
	return -1;
}



int MergeSort(int *arr_to_sort, size_t num_elements)
{
	assert(arr_to_sort);
	return MergeSortImpl(arr_to_sort, 0, num_elements - 1);
}

static int MergeSortImpl(int *arr_to_sort, int left, int right)
{
	int mid = left + (right - left) / 2, status = 0;
	
	assert(arr_to_sort);

	if ((left != right) && !status)
	{
		status += MergeSortImpl(arr_to_sort, left, mid);
		status += MergeSortImpl(arr_to_sort, mid + 1, right);
		status += Merge(arr_to_sort, left, mid, right);
	}

	return status;
}

static int Merge(int *arr_to_sort, int left, int mid, int right)
{
	int left_arr_size = (mid - left + 1), right_arr_size = (right - mid), 
													arr_ptr = 0, i = 0, j = 0;
	int *left_arr = NULL, *right_arr = NULL;

	assert(arr_to_sort);

	left_arr = (int *)calloc(left_arr_size, sizeof(int));
	if (!left_arr)
	{
		return 1;
	}

	right_arr = (int *)calloc(right_arr_size, sizeof(int));
	if (!right_arr)
	{
		free (left_arr);
		return 1;
	}

	arr_ptr = left;

	for (i = 0; i < left_arr_size; i++)
	{
		left_arr[i] = arr_to_sort[arr_ptr++];
	}

	for (i = 0; i < right_arr_size; i++)
	{
		right_arr[i] = arr_to_sort[arr_ptr++];
	}

	i = 0;
	j = 0;
	arr_ptr = left;
	while ((i < left_arr_size) && (j < right_arr_size))
	{
		if (left_arr[i] <= right_arr[j])
		{
			arr_to_sort[arr_ptr++] = left_arr[i++];
		}
		else
		{
			arr_to_sort[arr_ptr++] = right_arr[j++];
		}
	}

	while (i < left_arr_size)
	{
		arr_to_sort[arr_ptr++] = left_arr[i++];
	}

	while (j < right_arr_size)
	{
		arr_to_sort[arr_ptr++] = right_arr[j++];
	}

	free(right_arr);
	right_arr = NULL;

	free(left_arr);
	left_arr = NULL;

	return 0;
}

void QuickSort(void *base, size_t nitems, size_t size, 
									int (*compar)(const void *, const void*))
{
	assert(base);
	assert(compar);

	QuickSortImpl(base, 0, nitems, size, compar);
}

static void QuickSortImpl(void *arr, size_t from, size_t to, size_t size, 
									int (*compar)(const void *, const void*))
{
	size_t piviot = to - 1;

	assert(arr);
	assert(compar);

	if (from >= to)
	{
		return;
	}

	piviot = Partiton(arr, from, to, size, compar, piviot);

	QuickSortImpl(arr, from, piviot, size, compar);
	QuickSortImpl(arr, piviot + 1, to, size, compar);
}

static size_t Partiton(void *arr, size_t from, size_t to, size_t size, 
						int (*compar)(const void *, const void*), size_t piviot)
{
	size_t left = from, right = from;

	assert(arr);
	assert(compar);

	for (; right < to; right++)
	{
		if (compar((void *)((char *)arr + (right * size)), 
								(void *)((char *)arr + (piviot * size))) <= 0)
		{
			Swap((int *)((char *)arr + (right * size)), 
										(int *)((char *)arr + (left * size)));
			left ++;
		}
	}

	return left - 1;
}