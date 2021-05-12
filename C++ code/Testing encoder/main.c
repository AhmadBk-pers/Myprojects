/*
*Author: Ahmad Bakri
*Mail:   Ahmadbk1995@gmail.com
*/


/*
 *The soloution was to implement an encoder (reliable one) and then taking the encoded text
 *and decode it with the tested (software) ,if they match then the decoder works fine.
 *you can test it manually using Encode_Decode() function of automaticaly with 
 *run_all_combinations() function.
 */

#include <string.h>
#include <stdio.h>
//including the decoder (given)
#include "base64.h"
//including the encoder (from libb64)
#include "b64_encode.h"


//Declaring Functions
int Encode_Decode(char* word);
void run_all_combinations(char* word);


//Global variables needed to run all combination function
int status = 1;
int current_place = 0;
int starting_char = 1;
int stoping_char = 128;
int stopping_index = 100;


int main(void)
{
    char word[256] = "";
    run_all_combinations(word);

    //checking the final status if there was a bug on one of the tests
    if (status)
        printf("The code is valid\n");
    else 
        printf("There is a BUG\n");
}



/*
*This is a recursion function that runs throw all the possible combinations
*If you want to run throw all the combinations it will take days to test so I put some params
*starting_char which controls from which char in the Ascii table to start
*stoping_char which controls from which char in the Ascii table to stop
*stoping_index which determens how many chars do you want in the combination
*/
void run_all_combinations(char* word)
{
    int local_place = current_place;
    for (int i = starting_char; i < stoping_char; i++)
    {
        word[local_place] = i;
        if (current_place < stopping_index)
        {
            current_place++;
            run_all_combinations(word);
        }

        if (!Encode_Decode(word))                             //calling the Encoder decoder which performes the test
        {
            printf("There is a BUG\n");
            status = 0;                                       //changing the overall status
        }
    }

    current_place = local_place-1;
}


/*
*This is the code that tests the decoder
*Here I implemented an Encoder from libb64 which is a popular library and already tested
*First it gets the original text (word) and then run it throught the encoder,
*after that it puts the encoded text to the decoder (which needs to be tested), in the end it makes 
*a comparision between the original text and the decoded text.     
*(original text-> encoding-> decoding ?-> original text)
*/
int Encode_Decode(char* word)
{
    //Encoding the data 
    base64_encodestate encode_state;
    char* enecode_input = word;
    char encode_output[256] = { 0, };
    base64_init_encodestate(&encode_state);
    base64_encode_block(enecode_input, strlen(enecode_input) + 1, encode_output, &encode_state);


    //Decoding the data
    base64_decodestate decode_state;
    char* Decode_input = encode_output;
    char Decode_output[256] = { 0, };
    base64_init_decodestate(&decode_state);
    base64_decode_block(Decode_input, strlen(Decode_input), Decode_output, &decode_state);


    //Printing the decoded data
    printf("decoded output is %s \n", Decode_output);


    //Comparing the input and output
    if (!strncmp(enecode_input, Decode_output, strlen(enecode_input)))
    {
        printf("Match\n");
        return 1;
    }
    else return 0;
}
