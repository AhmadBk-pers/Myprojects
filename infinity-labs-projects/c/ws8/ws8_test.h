#ifndef __WS8_test_H__
#define __WS8_test_H__

#include "ws8.h"

void AddToAllElements(element elements_array[], int num);
void PrintAllElements(element elements_array[]);
void FreeAllElements(element elements_array[]);

#define TYPESNUM 3

#define MAX2(a,b) ((a > b) ? (a) : (b))
#define MAX3(a,b,c) ((MAX2(a,b) > c) ? MAX2(a,b) : (c))

#define SIZEOF_VAR(var) ((size_t)(&(var) + 1) - (size_t)(&(var)))

#define SIZEOF_TYPE(type) ((size_t)((type *)0 + 1))


#endif
