#include <stdio.h> /* printf */
#include <assert.h>     /* assert */
#include "sched.h"

enum {TEST_PASS = 0, TEST_FAIL = 1};

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#define RUN_TEST(x) if (TEST_FAIL == (x))            \
                    {                                \
                        printf(RED "Failure\n" RESET); \
                    }                                \
                    else                             \
                    {                                \
                        printf(GREEN "Success\n" RESET); \
                    }

FILE *fp_output = NULL;
time_t test_start_time = (time_t) - 1;
schedule_t *curr_sched = NULL;
int counter = 0;
uuid_t task_uuid = {0};

time_t TimeGenerator(size_t interval)
{
    time_t now = time(NULL);

    assert((time_t) -1 != now);

    return now + interval;
}

int Print1(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task1 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)param))
    {
        return -1;
    }

    return 0;
}

int Print2(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task2 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)param))
    {
        return -1;
    }

    return 0;
}

int Print3(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task3 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)param))
    {
        return -1;
    }

    return 0;
}

int Print5(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task5 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)param))
    {
        return -1;
    }

    return 0;
}

int KillPrint(void *kill_param)
{
    (void)kill_param;
    return 0;
}

int Stop(void *param)
{
    SchedStop(param);

    return 0;
}

int KillStop(void *kill_param)
{
    (void)kill_param;
    return 0;
}

int SelfRemove(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task1 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)fp_output))
    {
        printf("Could not write to output file");
        return -1;
    }

    return SchedRemoveTask(param, task_uuid);
}

int FailSelfRemove1(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task1 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)fp_output))
    {
        printf("Could not write to output file");
        return -1;
    }

    SchedRemoveTask(param, task_uuid);

    return 1;
}

int AddTask(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task1 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)fp_output))
    {
        printf("Could not write to output file");
        return -1;
    }

    return IsEqualUID(SchedAddTask(param, TimeGenerator(-5), 15,
                      Print5, fp_output, KillPrint, NULL), BAD_UID);
}

int GetSize(void *param)
{
    char str[16];
    char str2[16];

    assert(param);

    sprintf(str, "task1 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)fp_output))
    {
        printf("Could not write to output file");
        return -1;
    }

    sprintf(str2, "size: %lu\n", SchedSize(curr_sched));

    if (EOF == fputs(str2, (FILE *)fp_output))
    {
        printf("Could not write to output file");
        return -1;
    }

    return 0;
}

int ClearAll(void *param)
{
    char str[16];

    assert(param);

    sprintf(str, "task4 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)fp_output))
    {
        printf("Could not write to output file");
        return -1;
    }

    SchedClear(curr_sched);

    return 0;
}

int Counter(void *param)
{
    char str[16];

    assert(param);

    *(int *)param += 1;

    sprintf(str, "task1 %d\n", (unsigned int)difftime(time(NULL), test_start_time));

    if (EOF == fputs(str, (FILE *)fp_output))
    {
        printf("Could not write to output file");
        return -1;
    }

    if (7 == counter)
    {
        return 1;
    }

    return 0;
}

schedule_t *CreateAndInitRegularSched(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(0), 7, Print1,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(2), 2, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 5, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(15), 15, Stop,
                                       sched, KillStop, sched);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        return sched;
    }
}

schedule_t *CreateAndInitReRunSched(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(0), 7, Print1,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(1), 5, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 4, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(10), 5, Stop,
                                       sched, KillStop, sched);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        return sched;
    }
}

schedule_t *CreateAndInitSchedWithSelfRemovalTask(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(0), 7, SelfRemove,
                                       sched, KillPrint, NULL);

        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(2), 2, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 5, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(15), 15, Stop,
                                       sched, KillStop, sched);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        task_uuid = task_id1;
        return sched;
    }
}

schedule_t *CreateAndInitSchedWithNoStopTask(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(0), 7, Print1,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(2), 1, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 5, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(10), 1, ClearAll,
                                       sched, KillPrint, NULL);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        return sched;
    }
}

schedule_t *CreateAndInitSchedWithFailedTask(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(0), 1, Counter,
                                       &counter, KillPrint, NULL);
        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(2), 2, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 5, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(15), 15, Stop,
                                       sched, KillStop, sched);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        return sched;
    }
}

schedule_t *CreateAndInitSchedWithAddTask(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(0), 20, AddTask,
                                       sched, KillPrint, NULL);

        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(0), 2, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 5, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(12), 15, Stop,
                                       sched, KillStop, sched);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        task_uuid = task_id1;
        return sched;
    }
}

schedule_t *CreateAndInitSchedWithGetSizeTask(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(3), 20, GetSize,
                                       sched, KillPrint, NULL);

        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(0), 2, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 4, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(8), 15, Stop,
                                       sched, KillStop, sched);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        task_uuid = task_id1;
        return sched;
    }
}

schedule_t *CreateAndInitSchedWithFailedSelfRemovalTask(void)
{
    schedule_t *sched = SchedCreate();

    if (!sched)
    {
        printf("Could not create scheduler\n");
        return NULL;
    }

    else
    {
        uuid_t task_id1 = SchedAddTask(sched, TimeGenerator(0), 7, FailSelfRemove1,
                                       sched, KillPrint, NULL);

        uuid_t task_id2 = SchedAddTask(sched, TimeGenerator(2), 2, Print2,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id3 = SchedAddTask(sched, TimeGenerator(3), 5, Print3,
                                       fp_output, KillPrint, NULL);
        uuid_t task_id4 = SchedAddTask(sched, TimeGenerator(15), 15, Stop,
                                       sched, KillStop, sched);

        if (IsEqualUID(task_id1, BAD_UID) || IsEqualUID(task_id2, BAD_UID) ||
            IsEqualUID(task_id3, BAD_UID) || IsEqualUID(task_id4, BAD_UID))
        {
            printf("Failed to add tasks on scheduler initiation\n");
            SchedDestroy(sched);
            return NULL;
        }

        task_uuid = task_id1;
        return sched;
    }
}

int TestSchedSize(void)
{
    schedule_t *sched = CreateAndInitRegularSched();
    size_t sched_size = 0;

    if (!sched)
    {
        return TEST_FAIL;
    }

    sched_size = SchedSize(sched);
    SchedDestroy(sched);

    if (4 == sched_size)
    {
        return TEST_PASS;
    }

    return TEST_FAIL;
}

int TestSchedIsEmptyAndClear(void)
{
    schedule_t *sched = CreateAndInitRegularSched();
    int is_empty1 = 0;
    int is_empty2 = 0;

    if (!sched)
    {
        return TEST_FAIL;
    }

    is_empty1 = SchedIsEmpty(sched);
    SchedClear(sched);
    is_empty2 = SchedIsEmpty(sched);
    SchedDestroy(sched);

    if (0 == is_empty1 && 1 == is_empty2)
    {
        return TEST_PASS;
    }

    return TEST_FAIL;
}

int FilesAreMatch(char *filename, char *expected)
{
    FILE *file = fopen(filename, "r");
    int is_match = 0;
    char ch1 = 0;

    if (!file)
    {
        printf("Could not open file");
        return 0;
    }

    while ('\0' != *expected)
    {
        ch1 = fgetc(file);

        if (ch1 != *expected++)
        {
            break;
        }
    }

    if (EOF == fgetc(file) && '\0' == *expected)
    {
        is_match = 1;
    }

    if (EOF == fclose(file))
    {
        printf("Could not close file");
        return 0;
    }

    return is_match;

}

int TestRugularSched(void)
{
    char *expected = "task1 0\ntask2 2\ntask3 3\ntask2 4\ntask2 6\ntask1 7"
                     "\ntask3 8\ntask2 8\ntask2 10\ntask2 12\ntask3 13\n"
                     "task1 14\ntask2 14\n";
    schedule_t *sched = NULL;

    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    sched = CreateAndInitRegularSched();

    if (!sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(sched);
    SchedDestroy(sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int TestSchedWithSelfRemovalTask(void)
{
    char *expected = "task1 0\ntask2 2\ntask3 3\ntask2 4\ntask2 6\ntask3 8"
                     "\ntask2 8\ntask2 10\ntask2 12\ntask3 13\ntask2 14\n";
    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    curr_sched = CreateAndInitSchedWithSelfRemovalTask();

    if (!curr_sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(curr_sched);
    SchedDestroy(curr_sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int TestSchedWithNoStopTask(void)
{
    char *expected = "task1 0\ntask2 2\ntask3 3\ntask2 3\ntask2 4\ntask2 5"
                     "\ntask2 6\ntask1 7\ntask2 7\ntask3 8\ntask2 8\ntask2 9"
                     "\ntask4 10\n";
    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    curr_sched = CreateAndInitSchedWithNoStopTask();

    if (!curr_sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(curr_sched);
    SchedDestroy(curr_sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int TestSchedWithFailedTask(void)
{
    char *expected = "task1 0\ntask1 1\ntask2 2\ntask1 2\ntask3 3\ntask1 3"
                     "\ntask2 4\ntask1 4\ntask1 5\ntask2 6\ntask1 6\ntask3 8"
                     "\ntask2 8\ntask2 10\ntask2 12\ntask3 13\ntask2 14\n";
    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    curr_sched = CreateAndInitSchedWithFailedTask();

    if (!curr_sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(curr_sched);
    SchedDestroy(curr_sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int TestSchedWithAddTask(void)
{
    char *expected = "task1 0\ntask5 0\ntask2 0\ntask2 2\ntask3 3\ntask2 4"
                     "\ntask2 6\ntask3 8\ntask2 8\ntask5 10\ntask2 10\n";
    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    curr_sched = CreateAndInitSchedWithAddTask();

    if (!curr_sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(curr_sched);
    SchedDestroy(curr_sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int TestReRunSched()
{
    char *expected = "task1 0\ntask2 1\ntask3 3\ntask2 6\ntask1 7\ntask3 7"
                     "\ntask2 11\ntask3 11\ntask1 14\n";
    schedule_t *sched = NULL;

    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    sched = CreateAndInitReRunSched();

    if (!sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(sched);
    SchedRun(sched);
    SchedDestroy(sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int TestSchedWithGetSizeTask(void)
{
    char *expected = "task2 0\ntask2 2\ntask1 3\nsize: 4\ntask3 3\ntask2 4"
                     "\ntask2 6\ntask3 7\n";
    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    curr_sched = CreateAndInitSchedWithGetSizeTask();

    if (!curr_sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(curr_sched);
    SchedDestroy(curr_sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int TestSchedWithFailedSelfRemovalTask(void)
{
    char *expected = "task1 0\ntask2 2\ntask3 3\ntask2 4\ntask2 6\ntask3 8"
                     "\ntask2 8\ntask2 10\ntask2 12\ntask3 13\ntask2 14\n";
    fp_output = fopen("sched_output.txt", "w");

    if (!fp_output)
    {
        printf("Could not open file");
        return TEST_FAIL;
    }

    curr_sched = CreateAndInitSchedWithFailedSelfRemovalTask();

    if (!curr_sched)
    {
        return TEST_FAIL;
    }

    test_start_time = time(NULL);
    SchedRun(curr_sched);
    SchedDestroy(curr_sched);

    if (EOF == fclose(fp_output))
    {
        printf("Could not close file");
        return TEST_FAIL;
    }

    if (!FilesAreMatch("sched_output.txt", expected))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

void TestSchedModule(void)
{
    RUN_TEST(TestSchedSize());
    RUN_TEST(TestSchedIsEmptyAndClear());
    RUN_TEST(TestRugularSched());
    RUN_TEST(TestSchedWithSelfRemovalTask());
    RUN_TEST(TestSchedWithNoStopTask());
    RUN_TEST(TestSchedWithFailedTask());
    RUN_TEST(TestSchedWithAddTask());
    RUN_TEST(TestReRunSched());
    RUN_TEST(TestSchedWithGetSizeTask());
    RUN_TEST(TestSchedWithFailedSelfRemovalTask());
}

int main(void)
{
    TestSchedModule();
    return (0);
}
