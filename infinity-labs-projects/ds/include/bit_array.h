#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h>


/*
	OL 109
	24/8/2021
	
	version: 2
*/

typedef unsigned long bitsarr_t;



bitsarr_t BitsArrSetAll(bitsarr_t);
bitsarr_t BitsArrResetAll(bitsarr_t);

void BitsArrToString(bitsarr_t, char *buffer);

bitsarr_t BitsArrSetOn(bitsarr_t, size_t index);
bitsarr_t BitsArrSetOff(bitsarr_t, size_t index);
bitsarr_t BitsArrSetBit(bitsarr_t, size_t index, int value);

int BitsArrGetVal(bitsarr_t, size_t index);

bitsarr_t BitsArrFlip(bitsarr_t, size_t index);
bitsarr_t BitsArrMirror(bitsarr_t);

bitsarr_t BitsArrRotR(bitsarr_t, size_t rotations);
bitsarr_t BitsArrRotL(bitsarr_t, size_t rotations);

size_t BitsArrCountOn(bitsarr_t);
size_t BitsArrCountOff(bitsarr_t);

bitsarr_t BitsArrMirrorLUT(bitsarr_t input_arr, unsigned char *table);
size_t BitsArrCountOnLUT(bitsarr_t input_arr, size_t *table);

#endif /* __BIT_ARRAY_H__ */
