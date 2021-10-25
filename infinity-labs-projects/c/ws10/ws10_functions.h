#ifndef __WS10_FUNCTIONS_H__
#define __WS10_FUNCTIONS_H__

/****************************************************************************/
/******************************* Declerations *******************************/
/****************************************************************************/
# define IsLittleEndianMacro \
	((__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) ? (1) : (0) )


char *IToA(int value, char * str, int base);

int AToI(const char *str);

int IsSystemLittleEndian();

void PrintSelectedValues(char* arr1, size_t arr1_length, char* arr2, size_t arr2_length, char* arr3, size_t arr3_length);

#endif
