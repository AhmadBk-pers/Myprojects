#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "s_list.h"	/*singly list nodes*/
#include "stack_int.h" /* stack */
#include "node_utils.h" /*node_t*/


int FibRecursive(int element_index);
int FibIterative(int element_index);

node_t* FlipList(node_t* node);

void SortIntStack(stack_t *stack);

int StrCmp (const char* str1, const char* str2);
size_t StrLen(const char *str);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);
void StackSort(stack_t *stack);

#endif /* __RECURSION_H__ */
