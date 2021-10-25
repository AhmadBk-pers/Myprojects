/****************************************************************************/
/******************************** Libraries *********************************/
/****************************************************************************/

#include <stdio.h>	/*printf(), sprintf()*/
#include <string.h>	/*strcat strcpy*/
#include <stdlib.h> /*malloc free()*/
#include "ws8.h" /*Declerations*/
#include "ws8_test.h"


/****************************************************************************/
/******************************* Definitions* *******************************/
/****************************************************************************/

void AddToAllElements(element elements_array[], int num)
{
	int i = 0;
	
	for (i = 0; i < TYPESNUM; i++)
	{
		elements_array[i].Add(&elements_array[i], num);
	}
}

void PrintAllElements(element *elements_array)
{
	int i = 0;
	
	for (i = 0; i < TYPESNUM; i++)
	{
		elements_array[i].Print(&elements_array[i]);
	}
	
	printf("\n");
}

void FreeAllElements(element *elements_array)
{
	int i = 0;
	
	for (i = 0; i < TYPESNUM; i++)
	{
		elements_array[i].Free(&elements_array[i]);
	}
}

/****************************************************************************/

void CreateIntElement(element *int_element,const int input_data)
{
	int_element->data = (void *)(long)input_data;
	
	int_element->Add = AddToInt;
	int_element->Print = PrintInt;
	int_element->Free = FreeInt;
	
}

void AddToInt(element *int_element, int num)
{
	*(int *)(&int_element->data) += num;
}

void PrintInt(element *int_element)
{
	printf("%d\t", (int)(long)(int_element->data));
}

void FreeInt(element *int_element)
{
	(void) int_element;
}

/****************************************************************************/

void CreateFloatElement(element *float_element,const float input_data)
{
	*((float *)(&float_element->data)) = input_data;
	
	float_element->Add = AddToFloat;
	float_element->Print = PrintFloat;
	float_element->Free = FreeFloat;
}

void AddToFloat(element *float_element, int num)
{
	*((float *)(&float_element->data)) += (float)num;
}

void PrintFloat(element *float_element)
{
	printf("%0.2f\t", *((float *)(&float_element->data)));
}

void FreeFloat(element *float_element)
{
	(void) float_element;
}

/****************************************************************************/


void CreateStringElement(element *string_element,const char *input_data)
{
	string_element->data = malloc(strlen(input_data) * sizeof(char) + 1);
	strcpy((char *)(string_element->data), input_data);
	
	string_element->Add = AddToString;
	string_element->Print = PrintString;
	string_element->Free = FreeString;
}

void AddToString(element *string_element, int num)
{
	char *duplication, text[20];
	
	sprintf(text, "%d", num);
	
	duplication = (char *)malloc((strlen(string_element->data) + strlen(text) + 1)*sizeof(char));
	
	strcpy(duplication, (char *)string_element->data);
	strncat(duplication, text, strlen(text));

	free(string_element->data);
	
	string_element->data = duplication;
}

void PrintString(element *string_element)
{
	printf("%s\t", (char *)string_element->data);
}

void FreeString(element *string_element)
{
	free(string_element->data);
	string_element->data = NULL;
}


