#include <assert.h> /* assert */
#include <limits.h>	/* CHAR_BIT */
#include <stddef.h>	/*size_t*/

typedef unsigned long bitsarr_t;

#define BITSARRBITNUM (sizeof(bitsarr_t) * CHAR_BIT)

#ifndef TABLE_SIZE
#define TABLE_SIZE 256
#endif /* TABLE_SIZE */

bitsarr_t BitsArrSetAll(bitsarr_t bits_arr)
{	
	(void)bits_arr;
	return 0xFFFFFFFFFFFFFFFF;
}


bitsarr_t BitsArrResetAll(bitsarr_t bits_arr)
{
	(void)bits_arr;
	return 0x0;
}

void BitsArrToString(bitsarr_t bits_arr, char *buffer)
{
	bitsarr_t mask = (bitsarr_t)1 << (sizeof(bitsarr_t) * CHAR_BIT - 1);
	int i = 0;
	
	for (i = 0; i < (int)BITSARRBITNUM; i++)
	{
		buffer[i] = ((bits_arr & mask) && 1) + '0';
		mask >>= 1;
	}
	
	buffer[i] = '\0';
}

bitsarr_t BitsArrSetOn(bitsarr_t bits_arr, size_t index)
{
	bitsarr_t mask = 1 << index;
	
	assert(index < sizeof(bitsarr_t) * CHAR_BIT);
		
	bits_arr |= mask;
	
	return bits_arr;
}

bitsarr_t BitsArrSetOff(bitsarr_t bits_arr, size_t index)
{	
	
	bitsarr_t mask = 1 << index;
	
	assert(index < sizeof(bitsarr_t) * CHAR_BIT);
	
	mask = ~mask;
	bits_arr &= mask;
	
	return bits_arr;
}

bitsarr_t BitsArrSetBit(bitsarr_t bits_arr, size_t index, int value)
{	
	
	bitsarr_t mask = 1 << index;
	
	assert(index < sizeof(bitsarr_t) * CHAR_BIT);
	
	return ((bits_arr & ~mask) | value << index);
}

int BitsArrGetVal(bitsarr_t bits_arr, size_t index)
{
	
	bitsarr_t mask = 1 << index;
	
	assert(index < sizeof(bitsarr_t) * CHAR_BIT);
	
	return (bits_arr & mask) >> index;
}

bitsarr_t BitsArrFlip(bitsarr_t bits_arr, size_t index)
{
	
	bitsarr_t mask = 1 << index;
	
	assert(index < sizeof(bitsarr_t) * CHAR_BIT);
	
	bits_arr ^= mask;
	
	return bits_arr;
}

bitsarr_t BitsArrMirror(bitsarr_t bits_arr)
{
	bitsarr_t mirrored = 0;
	size_t i = 0;
	
	for (i = 0; i < BITSARRBITNUM; i++)
	{
		mirrored <<= 1;
		mirrored ^= (bits_arr & 1);
		bits_arr >>= 1;
	}
	
	return mirrored;
}

bitsarr_t BitsArrRotR(bitsarr_t bits_arr, size_t rotations)
{
	size_t len = sizeof(bitsarr_t) * BITSARRBITNUM - 1;
	size_t i = 0;
	
	for (i = 0; i < rotations; i++)
	{
		bitsarr_t single_bit = (bits_arr & 1) << len;
		
		bits_arr >>= 1;
		bits_arr ^= single_bit;
	}
	
	return bits_arr;
}

bitsarr_t BitsArrRotL(bitsarr_t bits_arr, size_t rotations)
{
	size_t len = sizeof(bitsarr_t) * BITSARRBITNUM - 1;
	size_t i = 0;
	
	for (i = 0; i < rotations; i++)
	{
		bitsarr_t single_bit = (bits_arr >> len) & 1;
		
		bits_arr <<= 1;
		bits_arr ^= single_bit;
	}
	
	return bits_arr;
}

size_t BitsArrCountOn(bitsarr_t bits_arr)
{
	size_t count = 0;
	
	while (bits_arr != 0)
	{
		bits_arr &= (bits_arr - 1);
		count++;
	}
	
	return count;
}

size_t BitsArrCountOff(bitsarr_t bits_arr)
{	
	return BitsArrCountOn(~bits_arr);
}

bitsarr_t BitsArrMirrorLUT(bitsarr_t input_arr, unsigned char *table)
{
	bitsarr_t total_miror =
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 0)) & 0xFF]) << (CHAR_BIT * 7)) ^
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 1)) & 0xFF]) << (CHAR_BIT * 6)) ^
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 2)) & 0xFF]) << (CHAR_BIT * 5)) ^
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 3)) & 0xFF]) << (CHAR_BIT * 4)) ^
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 4)) & 0xFF]) << (CHAR_BIT * 3)) ^
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 5)) & 0xFF]) << (CHAR_BIT * 2)) ^
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 6)) & 0xFF]) << (CHAR_BIT * 1)) ^
		((bitsarr_t)(table[(input_arr >> (CHAR_BIT * 7)) & 0xFF]) << (CHAR_BIT * 0));
	
	return total_miror;
}


unsigned char ByteMirror(unsigned char byte)
{
	unsigned char mirrored = 0;
	size_t i = 0;
	size_t len = sizeof(unsigned char) * CHAR_BIT;
	
	for (i = 0; i < len; i++)
	{
		mirrored <<= 1;
		mirrored ^= (byte & 1);
		byte >>= 1;
	}
	
	return mirrored;
}

void InitMirrorBitsTable(unsigned char *table)
{
	size_t i = 0;
	
	for (i = 0; i < TABLE_SIZE; i++)
	{
		table[i] = ByteMirror(i);
	}
}


size_t BitsArrCountOnLUT(bitsarr_t input_arr, size_t *table)
{
	size_t sum_of_set_bits =
		table[(input_arr >> (CHAR_BIT * 0)) & 0xFF] +
		table[(input_arr >> (CHAR_BIT * 1)) & 0xFF] +
		table[(input_arr >> (CHAR_BIT * 2)) & 0xFF] +
		table[(input_arr >> (CHAR_BIT * 3)) & 0xFF] +
		table[(input_arr >> (CHAR_BIT * 4)) & 0xFF] +
		table[(input_arr >> (CHAR_BIT * 5)) & 0xFF] +
		table[(input_arr >> (CHAR_BIT * 6)) & 0xFF] +
		table[(input_arr >> (CHAR_BIT * 7)) & 0xFF];
	
	return sum_of_set_bits;
}


void InitCountOnBitsTable(size_t *table)
{
	bitsarr_t i = 0;
	
	for (i = 0; i < TABLE_SIZE; i++)
	{
		table[i] = BitsArrCountOn(i);
	}
}
