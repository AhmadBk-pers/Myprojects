/****************************************************************************/
/*********************************Structs************************************/
/****************************Author: Ahmad Bakri*****************************/
/*****************************Reviewer: Amatzia******************************/
/****************************************************************************/

#include "ws8.h" /*Declerations*/
#include "ws8_test.h"



int main()
{
	element elements_array[TYPESNUM];
	
	CreateIntElement(&elements_array[0], 12);
	CreateFloatElement(&elements_array[1], 66.32);
	CreateStringElement(&elements_array[2], "chapter");
	
	PrintAllElements(elements_array);
	AddToAllElements(elements_array, 10);
	PrintAllElements(elements_array);
	
	FreeAllElements(elements_array);
	
	return 0;
}



