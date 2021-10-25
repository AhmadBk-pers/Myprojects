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
	
	auxility_arr[0] -= 1;
	
	for (i = min + 1; i <= max; i++)
	{
		auxility_arr[i] += auxility_arr[i - 1];
	}
	
	for (i = 0; i < (int)size; i++)
	{
		dest_arr[auxility_arr[arr[size - 1 - i]]--] = arr[size - 1 - i];
	}
	
	free(auxility_arr);
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
			dest_arr[auxility_arr[(arr[size - 1 - i] >> (4 * nibbles_count)) & mask]--] = arr[size - 1 - i];
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
