/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Recursion modules
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <assert.h>
#include "recursion.h"

static void PutInPlace(stack_t *stack,int element);

int FibRecursive(int element_index)
{
	if (2 == element_index || 1 == element_index)
	{
		return 1;
	}
	else 
	{
		return (FibRecursive(element_index - 1) + FibRecursive(element_index - 2));
	}
}

int FibIterative(int element_index)
{
	int k1, k2, k3, j;
  	k1 = k2 = k3 = 1;
  	for (j = 3; j <= element_index; j++)
  	{
    	k3 = k1 + k2;
      	k1 = k2;
      	k2 = k3;
  	}
  	
  	return k3;
}

node_t* FlipList(node_t* node)
{
	node_t *next_node = NULL, *head = NULL;
	
	if (NULL == node)
	{
		return NULL;
	}
	
	if (NULL == node->next)
	{
		return node;
	}
	
	head = FlipList(node->next);
	
	next_node = node->next;
	next_node->next = node;
	node->next = NULL;
	
	return head;
}


size_t StrLen(const char *str)
{
	assert(str);
	
	if (!(*str))
	{
		return 0;
	}
	
	return StrLen(++str) + 1;
}

int StrCmp (const char *str1, const char *str2)
{
	if (str1 == str2)
	{
		return 0;
	}
	else if (!str1 || !str2)
	{
		return 1;
	}
	
	if (*str1 != *str2)
	{
		return *str1 - *str2;
	}
	
	if ((*str1 == '\0') && (*str2 == '\0'))
	{
		return 0;
	}
	
	return StrCmp(++str1, ++str2);
}

char *StrCpy(char *dest, const char *src)
{
	assert(dest);
	assert(src);
	
	if (!(*src))
	{
		*dest = *src;
		return dest;
	}
	
	*dest = *src;
	StrCpy(++dest, ++src);
	
	return --dest;
}

char *StrCat(char *dest, const char *src)
{
	assert(dest);
	assert(src);
	
	if (!(*dest))
	{
		StrCpy(dest, src);
	}
	else
	{
		StrCat(++dest, src);
	}
	
	return --dest;	
}

char *StrStr(const char *haystack, const char *needle)
{
	assert(haystack);
	assert(needle);
	
	if (!(*needle))
	{
		return (char *)haystack;
	}
	
	if (!(*haystack))
	{
		return NULL;
	}
	
	if (*haystack == *needle && (StrStr(haystack + 1, needle + 1) == haystack + 1))
	{
		return (char *)haystack;
	}
	
	return StrStr(++haystack, needle);
}

void StackSort(stack_t *stack)
{
	int temp = 0;
	
	if (!StackIsEmpty(stack))
	{
		temp = StackPeek(stack);
		StackPop(stack);
		StackSort(stack);
		PutInPlace(stack, temp);
	}
}

static void PutInPlace(stack_t *stack,int element)
{
	int temp = 0;
	
	if (StackIsEmpty(stack) || element < StackPeek(stack))
	{
		StackPush(stack, element);
	}
	else
	{
		temp = StackPeek(stack);
		StackPop(stack);
		PutInPlace(stack, element);
		StackPush(stack, temp);
	}

}

