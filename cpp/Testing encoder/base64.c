/**
 * @file base64.c
 * @brief Base64 decoder implementation
 *
 */

#include "base64.h"

/**
 * @brief Initialize the decoder
 *
 * @param[out] state the deocder state to initialize
 */
void base64_init_decodestate(base64_decodestate* state)
{
	state->step = step_a;
	state->plainchar = 0;
}

/**
 * @brief Decode a single value
 *
 * @param[in] value_in the value to decode
 * @return    the decoded value
 */
static int base64_decode_value(signed char value_in)
{
	static const char decoding[] = {62,-1,-1,-1,63,52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-2,-1,-1,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
	static const char decoding_size = sizeof(decoding);
	value_in -= 43;
	if (value_in < 0 || value_in > decoding_size) return -1;
	return decoding[(int)value_in];
}

/**
 * @brief Decode a block of base64 stream
 *
 * @param[in]  code_in the stream to decoder
 * @param[in]  length_in size of the steam
 * @param[out] plaintext_out output buffer to hold the decoded data
 * @param[in]  state decoder state
 */
int base64_decode_block(const char* code_in, const int length_in, char* plaintext_out, base64_decodestate* state)
{
	const char* codechar = code_in;
	char* plainchar = plaintext_out;
	signed char fragment;
	
	*plainchar = state->plainchar;
	
	switch (state->step)
	{
		while (1)
		{
			case step_a:
				do {
					if (codechar == code_in+length_in)
					{
						state->step = step_a;
						state->plainchar = *plainchar;
						return plainchar - plaintext_out;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar    = (fragment & 0x03f) << 2;
			case step_b:
				do {
					if (codechar == code_in+length_in)
					{
						state->step = step_b;
						state->plainchar = *plainchar;
						return plainchar - plaintext_out;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar++ |= (fragment & 0x030) >> 4;
				*plainchar    = (fragment & 0x00f) << 4;
			case step_c:
				do {
					if (codechar == code_in+length_in)
					{
						state->step = step_c;
						state->plainchar = *plainchar;
						return plainchar - plaintext_out;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar++ |= (fragment & 0x03c) >> 2;
				*plainchar    = (fragment & 0x003) << 6;
			case step_d:
				do {
					if (codechar == code_in+length_in)
					{
						state->step = step_d;
						state->plainchar = *plainchar;
						return plainchar - plaintext_out;
					}
					fragment = (char)base64_decode_value(*codechar++);
				} while (fragment < 0);
				*plainchar++   |= (fragment & 0x03f);
		}
	}
	/* control should not reach here */
	return plainchar - plaintext_out;
}

