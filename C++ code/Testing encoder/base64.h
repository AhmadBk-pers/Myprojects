/**
 * @file base64.h
 * @brief Base64 decoder declarations
 *
 */

#ifndef _BASE64_H_
#define _BASE64_H_

/**
 * @brief The decoder step
 */
typedef enum
{
	step_a, step_b, step_c, step_d
} base64_decodestep;

/**
 * @brief The decoder state
 */
typedef struct
{
	base64_decodestep step;
	char plainchar;
} base64_decodestate;

/**
 * @brief Initialize the decoder
 *
 * @param[out] state the deocder state to initialize
 */
void base64_init_decodestate(base64_decodestate* state);

/**
 * @brief Decode a block of base64 stream
 *
 * @param[in]  code_in the stream to decoder
 * @param[in]  length_in size of the steam
 * @param[out] plaintext_out output buffer to hold the decoded data
 * @param[in]  state decoder state
 */
int base64_decode_block(const char* code_in, const int length_in, char* plaintext_out, base64_decodestate* state);

#endif /* _BASE64_H_ */
