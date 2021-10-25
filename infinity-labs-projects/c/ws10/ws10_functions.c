#include <math.h>
#include <string.h>
#include <stdio.h>

#define ARR1FLAG 1
#define ARR2FLAG 2
#define ARR3FLAG 4
#define VALID 3


/****************************************************************************/
/******************************* Definitions* *******************************/
/****************************************************************************/

void swap(char *x, char *y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(&str[start], &str[end]);
        start++;
        end--;
    }
}

char *IToA(int value, char *str, int base)
{
	int i = 0, is_negative = 0;
	
	if (value == 0)
    {
        str[i] = '0';
        str[i + 1] = '\0';
        
        return str;
    }
    
    if (value < 0 && base == 10)
    {
        is_negative = 1;
        value *= -1;
    }
    
    while (0 != value)
    {
    	int resedual = value % base;
    	
    	if (resedual > 9)
    	{
    		str[i++] = 'a' + (resedual - 10);
    	}
    	else
    	{
    		str[i++] = resedual + '0';
    	}
    	
    	value /= base;
    }
    
    if (is_negative)
    {
    	str[i++] = '-';
    }
    
    str[i++] = '\0';
    
    reverse(str, i - 1);
    
    return str;

}

int AToI(const char *str)
{
	int length = 0, i =0, value = 0, is_negative = 0;
	
	if (str[0] == '-')
	{
		is_negative = 1;
		str++;
	}
	
	length = strlen(str);
	
	for (i = 0; i < length; i++)
	{
		value += (str[length - 1 - i] - '0') * pow(10, i);
	}
	
	if (is_negative)
	{
		value *= -1;
	}
	
	return value;
}
                                          
int IsSystemLittleEndian()
{
	unsigned int i = 1;
   	char *c = (char*)&i;
   	
	return *c;
}

void PrintSelectedValues(char* arr1, size_t arr1_length, char* arr2, size_t arr2_length, char* arr3, size_t arr3_length)
{
	char flags_array[256] = {0};
	size_t i = 0;
	
	for (i = 0; i < arr1_length; i++)
	{
		flags_array[(size_t)arr1[i]] |= ARR1FLAG;
	}
	
	for (i = 0; i < arr2_length; i++)
	{
		flags_array[(size_t)arr2[i]] |= ARR2FLAG;
	}
	
	for (i = 0; i < arr3_length; i++)
	{
		flags_array[(size_t)arr3[i]] |= ARR3FLAG;
	}
	
	for (i = 0; i < 256; i++)
	{
		if(flags_array[i] == VALID)
		{
			printf("%c ", (char)i);
		}
	}
	
	printf("\n");
	

}

