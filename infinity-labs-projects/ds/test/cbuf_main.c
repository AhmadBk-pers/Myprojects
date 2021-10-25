/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   Tests of Circular buffer module
* Group         OL110
* Company       ILRD Ramat Gan
* *****************************************************************************/

#include <stdio.h>  /* printf() */
#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */

#include "cbuf.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

#define FAIL() (printf( RED "\nTest-Failed: at line %d\n" RESET, __LINE__))
#define SUCCESS() printf( GREEN "\nTest-success: at line %d\n" RESET, __LINE__)
#define TEST(test) do{if (!(test)) {FAIL();}} while(0)

void CircularBufferTests();
void ReadFromEmptyBuffer(size_t capacity);
void WriteToFullBuffer();
void WriteReadLoop();
void WriteReadUnaligned();
void WriteReadFullCapacity();



int main()
{
    CircularBufferTests();

    return 0;
}


void CircularBufferTests()
{
    ReadFromEmptyBuffer(1);
    ReadFromEmptyBuffer(100);

    WriteToFullBuffer();

    WriteReadLoop();

    WriteReadUnaligned();

    WriteReadFullCapacity();

    /* Visual check for leakage - valgrind report */
}


/* Test Functions */
/******************************************************************/
void ReadFromEmptyBuffer(size_t capacity)
{
    char buf[1000] = {0};
    cbuff_t *cbuff = CBCreate(capacity);

    TEST(CBBufsiz(cbuff) == capacity);
    TEST(CBFreeSpace(cbuff) == capacity);
    TEST(CBIsEmpty(cbuff) == 1);

    TEST(CBRead(cbuff, buf, 3) == 0);
    TEST(strlen(buf) == 0);

    TEST(CBBufsiz(cbuff) == capacity);
    TEST(CBFreeSpace(cbuff) == capacity);
    TEST(CBIsEmpty(cbuff) == 1);

    CBDestroy(cbuff);
    cbuff = NULL;
}


void WriteToFullBuffer()
{
    char buf[] = "abcde";
    size_t capacity = strlen(buf) + 1;
    cbuff_t *cbuff = CBCreate(capacity);

    TEST(CBBufsiz(cbuff) == capacity);
    TEST(CBFreeSpace(cbuff) == capacity);
    TEST(CBIsEmpty(cbuff) == 1);

    TEST(CBWrite(cbuff, buf, capacity) == (long int)capacity);

    TEST(CBBufsiz(cbuff) == capacity);
    TEST(CBFreeSpace(cbuff) == 0);
    TEST(CBIsEmpty(cbuff) == 0);

    TEST(CBWrite(cbuff, buf, capacity) == 0);

    TEST(CBBufsiz(cbuff) == capacity);
    TEST(CBFreeSpace(cbuff) == 0);
    TEST(CBIsEmpty(cbuff) == 0);

    CBDestroy(cbuff);
    cbuff = NULL;
}


void WriteReadLoop()
{
    size_t i = 0;
    char buf[] = "abcde";
    char buf2[6] = {0};
    size_t capacity = strlen(buf) + 1;
    cbuff_t *cbuff = CBCreate(capacity);

    for (i = 0; i < 100; ++i)
    {
        TEST(CBFreeSpace(cbuff) == capacity);
        TEST(CBWrite(cbuff, buf, 3) == (long int)3);
        TEST(CBFreeSpace(cbuff) == 3);
        TEST(CBWrite(cbuff, (buf + 3), 3) == (long int)3);
        TEST(CBFreeSpace(cbuff) == 0);

        TEST(CBRead(cbuff, buf2, 3) == (long int)3);
        TEST(strncmp(buf2, "abcde", 3) == 0);
        TEST(CBFreeSpace(cbuff) == 3);

        TEST(CBRead(cbuff, (buf2 + 3), 3) == (long int)3);
        TEST(strncmp(buf2, "abcde", 6) == 0);
        TEST(CBFreeSpace(cbuff) == capacity);

        TEST(CBIsEmpty(cbuff) == 1);
    }

    CBDestroy(cbuff);
    cbuff = NULL;
}


void WriteReadUnaligned()
{
    char buf[6] = {0};
    cbuff_t *cbuff = CBCreate(3);

    TEST(CBWrite(cbuff, "ab1111", 2) == (long int)2);
    TEST(CBWrite(cbuff, "c111111", 100) == (long int)1);
    TEST(CBFreeSpace(cbuff) == 0);

    TEST(CBRead(cbuff, buf, 2) == (long int)2);
    TEST(CBRead(cbuff, (buf + 2), 100) == (long int)1);
    TEST(strncmp(buf, "abc", 3) == 0);
    TEST(CBFreeSpace(cbuff) == 3);
    TEST(CBBufsiz(cbuff) == 3);
    TEST(CBIsEmpty(cbuff) == 1);

    CBDestroy(cbuff);
    cbuff = NULL;
}


void WriteReadFullCapacity()
{
    char buf[10] = {0};
    cbuff_t *cbuff = CBCreate(10);

    TEST(CBWrite(cbuff, "0123456789aaa", 10) == (long int)10);
    TEST(CBFreeSpace(cbuff) == 0);
    TEST(CBIsEmpty(cbuff) == 0);

    TEST(CBRead(cbuff, buf, 10) == (long int)10);
    TEST(CBFreeSpace(cbuff) == CBBufsiz(cbuff));
    TEST(CBIsEmpty(cbuff) == 1);

    TEST(strncmp(buf, "0123456789aaa", 10) == 0);

    CBDestroy(cbuff);
    cbuff = NULL;
}




/* space */
