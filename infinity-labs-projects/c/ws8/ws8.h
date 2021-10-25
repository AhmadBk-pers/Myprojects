/****************************************************************************/
/******************************* Declerations *******************************/
/****************************************************************************/
#ifndef __WS8_H__
#define __WS8_H__

typedef struct
{
	void *data;
	
	void (*Add)();
	void (*Print)();
	void (*Free)();
	
} element;

void CreateIntElement(element *int_element,const int input_data);
void AddToInt(element *int_element, int num);
void PrintInt(element *int_element);
void FreeInt(element *int_element);

void CreateFloatElement(element *float_element,const float input_data);
void AddToFloat(element *float_element, int num);
void PrintFloat(element *float_element);
void FreeFloat(element *float_element);

void CreateStringElement(element *string_element,const char *input_data);
void AddToString(element *string_element, int num);
void PrintString(element *string_element);
void FreeString(element *string_element);



#endif
