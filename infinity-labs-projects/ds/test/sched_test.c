/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description   schedular module tests
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdio.h>
#include "sched.h"

#define S_MSG(func) "SUCCESS: " #func " works as expected!\n"
#define NORM "\033[0m"
#define _R_ "\033[0;31m"
#define _G_ "\033[0;32m"
#define _Y_ "\033[0;33m"
#define _B_ "\033[0;36m"

int IsEmpTest(schedule_t *sched, int status);

int Action(void *param)
{
	static size_t count = 0;

	++count;
	return !printf("\a"_B_"Action"_Y_"%s "_B_"called for the "_Y_"%lu"_B_"%s time\n"NORM,
		(char *)param, count,
		(1 == count ? "st" : (2 == count ? "nd" : (3 == count ? "rd" : "th"))));
}

int StopAction(void *param)
{
	static int flag = 0;
	SchedStop((schedule_t *)param);

	return flag ? flag : !(flag = 1);
}

int SizeAction(void *param)
{
	printf("\a"_Y_"SchedSize "_B_"registers as "_Y_"%lu\n"NORM, SchedSize((schedule_t *)param));

	return 0;
}

int MpTAction(void *param)
{
	IsEmpTest((schedule_t *)param, 1);

	return 1;
}

int Kill(void *param)
{
	return !printf("\a"_G_"SUCCESS: Kill engaged for Action"_Y_"%s\n"NORM, (char *)param);
}

int IsEmpTest(schedule_t *sched, int status)
{
	return ((status ^ SchedIsEmpty(sched)) ?
		!!printf(_G_ S_MSG(SchedIsEmpty) NORM) :
		!printf("%s", status ?
			_Y_"SchedIsEmpty"_R_" FAILED to recognize a "_Y_"full schedule\n"NORM :
			_Y_"SchedIsEmpty"_R_" FAILED to recognize an "_Y_"empty schedule\n"NORM));
}

int SizeTest(schedule_t *sched, size_t size)
{
	return ((size == SchedSize(sched)) ?
		!!printf(_G_ S_MSG(SchedSize) NORM) :
		!printf(_Y_"SchedSize "_R_"FAILED to return "_Y_"%lu"_R_", instead got "_Y_"%lu\n"NORM,
			size, SchedSize(sched)));
}

uuid_t AddTest(schedule_t *sched, time_t time, size_t interval,
	int (*action)(void *param), void *param, size_t size_after)
{
	uuid_t uid = SchedAddTask(sched, time, interval, action, param, Kill, param);
	if (IsEqualUID(uid, BAD_UID) || !(IsEmpTest(sched, 1) && SizeTest(sched, size_after)))
	{
		printf(_Y_"SchedAddTask "_R_"FAILED\n"NORM);
		return BAD_UID;
	}
	else
	{
		printf(_G_ S_MSG(SchedAddTask) NORM);
		return uid;
	}
}

void RemoveTest(schedule_t *sched, uuid_t uid, size_t size_after)
{
	printf("%s", 
	(!SchedRemoveTask(sched, uid) && SizeTest(sched, size_after)
		&& IsEmpTest(sched, (int)size_after)) ?
	_G_ S_MSG(SchedRemoveTask) NORM :
	_Y_"SchedRemoveTask "_R_"FAILED to remove desired task\n"NORM);
}

void SchedTest(void)
{
	schedule_t *sched = SchedCreate();
	uuid_t uid0 = BAD_UID, uid1 = BAD_UID, uid2 = BAD_UID, uid3 = BAD_UID;

	printf("\033[1;36m\n\t~SJ SCHEDULE TEST SEQUENCE~\n\n"NORM);

	printf(_B_"\tTesting empty schedule:\n"NORM);
	SizeTest(sched, 0);
	IsEmpTest(sched, 0);

	printf(_B_"\tTesting addition:\n"NORM);
	uid1 = AddTest(sched, (time(NULL) + 5), 3, Action, (void *)"1", 1);
	uid0 = AddTest(sched, (time(NULL) +20), 1, Action, NULL, 2);
	uid2 = AddTest(sched, (time(NULL) +20), 12, StopAction, (void *)sched, 3);
	uid3 = AddTest(sched, (time(NULL) +10), 10, SizeAction, (void *)sched, 4);

	printf(_B_"\tTesting removal:\n"NORM);
	RemoveTest(sched, uid0, 3);
	
	printf(_B_"\tTesting run:\n"NORM);
	printf(_Y_"SchedRun 1 "_B_"terminated with status "_Y_"%d\n"NORM, SchedRun(sched));
	printf(_B_"sleeping for a while...\n"NORM);
	sleep(10);
	printf(_Y_"SchedRun 2 "_B_"terminated with status "_Y_"%d\n"NORM, SchedRun(sched));

	SizeTest(sched, 2);

	printf(_B_"\tTesting clearing\n"NORM);
	SchedClear(sched);
	printf("%s", ((SizeTest(sched, 0) && IsEmpTest(sched, 0)) ?
		_G_ S_MSG(SchedClear) NORM :
		_R_"FAILED to "_Y_"SchedClear "_R_"properly\n"NORM));

	printf(_B_"\tTesting SchedIsEmpty via run\n"NORM);
	uid1 = AddTest(sched, (time(NULL) +10), 10, MpTAction, (void *)sched, 1);
	printf(_Y_"SchedRun 3 "_B_"terminated with status "_Y_"%d\n"NORM, SchedRun(sched));

	SchedDestroy(sched);
	(void)uid1;
	(void)uid2;
	(void)uid3;
}

int main()
{
	SchedTest();
	printf(_B_"\nPlease check Valgrind to ensure proper destruction.\n\t~Have a lovely day~\n"NORM);

	return 0;
}
