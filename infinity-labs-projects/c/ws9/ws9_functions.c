#include "ws9_functions.h" 

/****************************************************************************/
/********************************** Macros **********************************/
/****************************************************************************/

#define BYTE_SIZE 8
#define WORD_SIZE sizeof(size_t)

/****************************************************************************/
/******************************* Definitions* *******************************/
/****************************************************************************/

size_t DupChar(const int c, size_t count)
{
	size_t i = 0;
	size_t duplicated_char = 0;
	
	for (i = 0; i < count; i++)
	{
		duplicated_char <<= BYTE_SIZE;
		duplicated_char ^= (size_t)c;
	}
	
	return duplicated_char;
}

void *Memset(void *str, int c, size_t n)
{
	char *str_ptr = str;
	const size_t word_size_data = DupChar(c, WORD_SIZE); 
	size_t n_resdual = 0;
	
	while (((size_t)str_ptr % WORD_SIZE) && n)
	{
		*str_ptr = (char)c;
		str_ptr++;
		n--;
	}
	
	n_resdual = n / WORD_SIZE;
	
	while (n_resdual)
	{
		*(size_t *)str_ptr = word_size_data;
		str_ptr += WORD_SIZE;
		n -= WORD_SIZE;
		
		n_resdual = n / WORD_SIZE;
	}
	
	while (n)
	{
		*str_ptr = (char)c;
		str_ptr++;
		n--;
	}
	
	return str;
}

/***************************************************************************/

size_t CopyChar(void *src, size_t count)
{
	size_t i = 0, duplicated_char = 0;
	char *src_ptr = src;
	
	for (i = 0; i < count; i++)
	{
		duplicated_char <<= BYTE_SIZE;
		duplicated_char ^= *(size_t *)src_ptr;
		src_ptr++;
	}
	
	return duplicated_char;
}

void *Memcpy(void *dest, void *src, size_t n)
{
	char *dest_ptr = dest, *src_ptr = src;
	size_t n_resdual = 0;
	
	while (((size_t)dest_ptr % WORD_SIZE) && n)
	{
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src_ptr++;
		n--;
	}
	
	n_resdual = n / WORD_SIZE;
	
	while (n_resdual)
	{
		*(size_t *)dest_ptr = CopyChar(src, WORD_SIZE);
		dest_ptr += WORD_SIZE;
		src_ptr += WORD_SIZE;
		n -= WORD_SIZE;
		
		n_resdual = n / WORD_SIZE;
	}
	
	while (n)
	{
		*dest_ptr = *src_ptr;
		dest_ptr++;
		src_ptr++;
		n--;
	}
	
	return dest;
}

/***************************************************************************/

size_t ReverseCopyChar(void *src, size_t count)
{
	size_t i = 0, duplicated_char = 0;
	char *src_ptr = src;
	
	
	for (i = 0; i < count; i++)
	{
		duplicated_char <<= BYTE_SIZE;
		duplicated_char ^= (*(size_t *)src_ptr) << (count * BYTE_SIZE);
		src_ptr--;
	}
	
	return duplicated_char;
}

void *CopyFromTheEnd(void *dest, void *src, size_t n)
{
	char *dest_ptr = dest, *src_ptr = src;
	size_t n_resdual = 0;
	
	dest_ptr += n - 1;
	src_ptr += n - 1;
	
	while (((size_t)dest_ptr % WORD_SIZE) && n)
	{
		*dest_ptr = *src_ptr;
		dest_ptr--;
		src_ptr--;
		n--;
	}
	
	n_resdual = n / WORD_SIZE;
	
	while (n_resdual)
	{
		dest_ptr -= WORD_SIZE;
		*(size_t *)dest_ptr = ReverseCopyChar(src, WORD_SIZE);
		src_ptr -= WORD_SIZE;
		n -= WORD_SIZE;
		
		n_resdual = n / WORD_SIZE;
	}
	
	while (n)
	{
		*dest_ptr = *src_ptr;
		dest_ptr--;
		src_ptr--;
		n--;
	}
	
	return dest;
}

void *Memmove(void *dest, void *src, size_t n)
{
	if ((0 < ((size_t)dest - (size_t)src)) && ((size_t)dest - (size_t)src) < n)
	{
		return CopyFromTheEnd(dest, src, n);
	}
	else
	{
		return Memcpy(dest, src, n);
	}
	
}


