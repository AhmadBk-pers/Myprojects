/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Shahar
* Description   Recursion module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <assert.h>					/*assert*/
#include "recursion.h"				/*API of the project*/

static void PutInPlace(stack_t *stack,int element);

int FibRecursive(int element)
{
	if (2 == element || 1 == element)
	{
		return 1;
	}
	else 
	{
		return (FibRecursive(element - 1) + FibRecursive(element - 2));
	}
}

int FibIterative(int element)
{
	int prev, current, next, i;
  	prev = current = next = 1;
  	for (i = 3; i <= element; i++)
  	{
    	next = prev + current;
      	prev = current;
      	current = next;
  	}
  	
  	return next;
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
	assert(str1);
	assert(str2);

	if (str1 == str2)
	{
		return 0;
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
	
	*dest = *src;

	if (!(*src))
	{
		return dest;
	}
	
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
		StrCat(dest + 1, src);
	}
	
	return dest;	
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

	assert(stack);
	
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
	
	assert(stack);

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

