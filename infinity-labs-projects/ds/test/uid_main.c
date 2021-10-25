/******************************************************************************
* Author        Shahar Refael Shoshany
* Reviewer      ---
* Description   Tests of UID module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stdio.h>  /* printf() */
#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */

#include "uid.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

#define FAIL() (printf( RED "\nTest-Failed: at line %d\n" RESET, __LINE__))
#define SUCCESS() printf( GREEN "\nTest-success: at line %d\n" RESET, __LINE__)
#define TEST(test) do{if (!(test)) {FAIL();}} while(0)

/* Utility funcs */
/******************************************************************/

/* Test Functions */
/******************************************************************/
void UIDTests();
void GetUIDOfSameProcess();


int main()
{
    UIDTests();

    return 0;
}


void UIDTests()
{
    GetUIDOfSameProcess();

    /* Visual check for leakage - valgrind report */
}


/* Get_UID_Of_Same_Process */
/******************************************************************/
void GetUIDOfSameProcess()
{
    uuid_t uid1, uid2, uid3, uid4;

    uid1 = GetUID();
    printf("\nClock ticks before getting uid2 : %ld\n\n", clock());
    uid2 = GetUID();
    printf("\nClock ticks after getting uid2 : %ld\n\n", clock());

    printf("\nTime difference between uid1 and uid2 is: %f seconds\n\n",
           difftime(uid2.__time_ind__, uid1.__time_ind__));

    TEST(uid1.__counter__ + 1 == uid2.__counter__);
    TEST(uid1.__process_id__ == uid2.__process_id__);
    TEST(uid1.__time_ind__ == uid2.__time_ind__);

    sleep(1);

    uid3 = GetUID();

    printf("\nTime difference between uid2 and uid3 is: %f seconds\n\n",
           difftime(uid3.__time_ind__, uid2.__time_ind__));

    TEST(uid2.__counter__ + 1 == uid3.__counter__);
    TEST(uid2.__process_id__ == uid3.__process_id__);
    TEST(uid2.__time_ind__ != uid3.__time_ind__);

    printf("\nPlease wait a few seconds before pressing enter\n");
    getchar();

    uid4 = GetUID();

    printf("\nTime difference between uid3 and uid4 is: %f seconds\n\n",
           difftime(uid4.__time_ind__, uid3.__time_ind__));

    TEST(uid3.__counter__ + 1 == uid4.__counter__);
    TEST(uid3.__process_id__ == uid4.__process_id__);
    TEST(uid3.__time_ind__ != uid4.__time_ind__);

    TEST(IsEqualUID(uid1,uid1));
    TEST(!IsEqualUID(uid1,uid2));
    TEST(!IsEqualUID(uid1,uid3));
    TEST(!IsEqualUID(uid1,uid4));

    TEST(IsEqualUID(uid2,uid2));
    TEST(!IsEqualUID(uid2,uid3));
    TEST(!IsEqualUID(uid2,uid4));

    TEST(IsEqualUID(uid3,uid3));
    TEST(!IsEqualUID(uid3,uid4));

    TEST(IsEqualUID(uid4,uid4));
}


/* Utility funcs */
/******************************************************************/




/* space */
