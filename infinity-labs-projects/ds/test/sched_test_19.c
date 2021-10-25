#include <stdio.h>
#include "sched.h"

struct param
{
	schedule_t *sched1;
	uuid_t uid1;
};


struct add_task
{
	schedule_t *sched;
    int (*action)(void *param);
    void *param;
    int (*kill)(void *kill_param);
    void *kill_param;
    size_t interval_in_sec;
    time_t run_time; 
    uuid_t uid;
};


void Red() 
{
	printf("\033[1;31m");
}

void Green() 
{
	printf("\033[0;32m");
}

void ResetColor()
{
	printf("\033[0m");
}


void TestExpectedINTS(int actual, int expected, const char *func_name)
{
	if (actual != expected)
	{
		Red();
	}
	else
	{
		Green();
	}
	
	printf("%s\n", func_name);
	ResetColor();
}

time_t RunTime(time_t seconds)
{
	time_t time_now = time(NULL);
	return time_now + seconds;
}

int KillNull(void *kill_param)
{
	(void)kill_param;
	return 1;
}

int ActionStop1(void *param)
{
	SchedStop(param);
	
	return 1;
}

int ActionStop(void *param)
{
	SchedStop(param);
	
	return 0;
}

int ActionPrint(void *param)
{
	(void)param;
	
	printf("\033[0;34m");
	printf("I am scheduler!\n");
	ResetColor();
	
	return 0;
}

int ActionPrint2(void *param)
{
	(void)param;
		printf("\033[0;34m");
	
	printf("\033[0;34m");
	printf("I am scheduler!\n");
	ResetColor();
	
	return 1;
}

int ActionSize(void *param)
{
	TestExpectedINTS(SchedSize(param), 6, "AddTask-AddSize");
	return 0;
}

int ActionSize1(void *param)
{
	TestExpectedINTS(SchedSize(param), 7, "AddTask-AddSize");
	return 0;
}


int ActionIsEmptyFullSched(void *param)
{
	TestExpectedINTS(SchedIsEmpty(param), 0, "AddTask-IsEmpty");
	return 0;
}


int ActionIsEmpty(void *param)
{
	TestExpectedINTS(SchedIsEmpty(param), 1, "AddTask-IsEmpty");
	return 0;
}




int ActionRemoveTask(void *param)
{
	SchedRemoveTask(((struct param *)param)->sched1, ((struct param *)param)->uid1);
	return 0;
}
    

int ActionClear(void *param)
{
	SchedClear(param);
	SchedStop(param);
	
	return 1;
}



int ActionAddTask(void *param)
{
	SchedAddTask(((struct add_task *)param)->sched, ((struct add_task *)param)->run_time,
	((struct add_task *)param)->interval_in_sec, ((struct add_task *)param)->action,
	((struct add_task *)param)->param, ((struct add_task *)param)->kill,
	((struct add_task *)param)->kill_param);
	
	return 0;
}

int KillPrint(void *param)
{
	printf("\033[0;34m");
	printf("Kill: Remove task num %d\n", *(int *)param);
	ResetColor();
		
	return 0;
}
	
	
void TestRunAddTask(void)
{
	struct add_task add_task_param = {0};
	
	schedule_t *sched = SchedCreate();
	size_t interval_in_sec = 5;
	void *kill_param = NULL;
	
	printf("\nAddTask-AddTask\n");
	
	add_task_param.action = ActionPrint;
    add_task_param.param = kill_param;
    add_task_param.kill = KillNull;
    add_task_param.kill_param = kill_param;
    add_task_param.interval_in_sec = interval_in_sec;
    add_task_param.run_time = RunTime(0);
    add_task_param.uid = GetUID();
    add_task_param.sched = sched;
    
	SchedAddTask(sched, RunTime(15), interval_in_sec, ActionStop1, sched, KillNull, kill_param);
	
	SchedAddTask(sched, RunTime(1), 11, ActionAddTask, &add_task_param, KillNull, kill_param);

	SchedAddTask(sched, RunTime(4), interval_in_sec, ActionStop1, sched, KillNull, kill_param);
	
	SchedAddTask(sched, RunTime(2), 11, ActionAddTask, &add_task_param, KillNull, kill_param);
	
		SchedAddTask(sched, RunTime(10), interval_in_sec, ActionStop1, sched, KillNull, kill_param);
		
	SchedAddTask(sched, RunTime(3), 11, ActionAddTask, &add_task_param, KillNull, kill_param);
		
	SchedRun(sched);
	
	TestExpectedINTS(SchedSize(sched), 8, "AddTask-Size");
	
	SchedRun(sched);
	
	TestExpectedINTS(SchedSize(sched), 7, "AddTask-Size");
	
	SchedRun(sched);
	
	TestExpectedINTS(SchedSize(sched), 9, "AddTask-Size");
	
	SchedDestroy(sched);
}
	
/*taskDestroy, task addself,  read and write*/


void TestRunRemoveSelf(void)
{
	struct param param1 = {0};
	schedule_t *sched = SchedCreate();
	size_t interval_in_sec = 3;
	void *param_null = NULL;
	uuid_t uid = BAD_UID;
	int x1 = 1;
	
	printf("\nAddTask-RemoveSelf\n");
	
	uid = SchedAddTask(sched, RunTime(1), interval_in_sec, ActionRemoveTask, &param1, KillPrint, &x1);
	
	param1.uid1 = uid;
	param1.sched1 = sched;
	
	SchedAddTask(sched, RunTime(2), interval_in_sec, ActionStop1, sched, KillNull, param_null);	
	
	SchedRun(sched);
	
	TestExpectedINTS(SchedSize(sched), 0, "RemoveSelf-Size");
	
	SchedDestroy(sched);
}

	
void TestRunRemove(void)/*add test with add and remove task in the middle*/
{
	struct param param1 = {0};
	
	schedule_t *sched = SchedCreate();
	size_t interval_in_sec = 8;
	int x1 = 1, x2 = 2, x3 = 3;
	void *param_null = NULL;
	uuid_t uid = BAD_UID, uid1 = BAD_UID, uid2 = BAD_UID;
	
	printf("\nAddTask-Remove\n");
	
	uid = SchedAddTask(sched, RunTime(3), interval_in_sec, ActionPrint, param_null, KillPrint, &x3);
	
	SchedAddTask(sched, RunTime(18), interval_in_sec, ActionStop1, sched, KillNull, param_null);
	
	uid1 = SchedAddTask(sched, RunTime(2), interval_in_sec, ActionPrint, param_null, KillPrint, &x2);

	SchedAddTask(sched, RunTime(5), interval_in_sec, ActionRemoveTask, &param1, KillNull, param_null);
	
SchedAddTask(sched, RunTime(13), interval_in_sec, ActionStop1, sched, KillNull, param_null);	
		
	uid2 = SchedAddTask(sched, RunTime(1), interval_in_sec, ActionPrint, param_null, KillPrint, &x1);
	
	SchedAddTask(sched, RunTime(4), interval_in_sec, ActionRemoveTask, &param1, KillNull, param_null);

	SchedAddTask(sched, RunTime(6), interval_in_sec, ActionRemoveTask, &param1, KillNull, param_null);

	SchedAddTask(sched, RunTime(7), interval_in_sec, ActionStop1, sched, KillNull, param_null);
	

	param1.uid1 = uid;
	param1.sched1 = sched;
	SchedRun(sched);
	
	TestExpectedINTS(SchedSize(sched), 7, "Remove-Size");
	
	param1.uid1 = uid1;
	SchedRun(sched);
	TestExpectedINTS(SchedSize(sched), 5, "Remove-Size");

	param1.uid1 = uid2;
	SchedRun(sched);
	TestExpectedINTS(SchedSize(sched), 3, "Remove-Size");
	
	SchedDestroy(sched);
}

void TestRunClear(void)
{
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(0);
	size_t interval_in_sec = 3600;
	int x1 = 1;
	void *kill_param = NULL;
	
	
	printf("\nAddTask-Clear\n");
	SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, &x1, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, &x1, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, &x1, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionClear, sched, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionStop1, sched, KillNull, kill_param);
	
	SchedRun(sched);
	
	TestExpectedINTS(SchedSize(sched), 0, "TestRun-Clear");
	
	SchedDestroy(sched);
}
	
	
void TestRunSize(void)
{
	struct add_task add_task_param = {0};
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(0);
	size_t interval_in_sec = 3600;
	int x1 = 1;
	void *param = &x1, *param2 = sched;
	void *kill_param = NULL;
	
	add_task_param.action = ActionPrint;
    add_task_param.param = kill_param;
    add_task_param.kill = KillNull;
    add_task_param.kill_param = kill_param;
    add_task_param.interval_in_sec = interval_in_sec;
    add_task_param.run_time = run_time; 
    add_task_param.uid = GetUID();
    add_task_param.sched = sched;
	
	printf("\nAddTask-Size\n");
	SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionSize, param2, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionAddTask, &add_task_param, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionSize1, param2, KillNull, kill_param);
	
	SchedAddTask(sched, run_time, interval_in_sec, ActionStop1, param2, KillNull, kill_param);
	
	SchedRun(sched);
	
	SchedDestroy(sched);
}


void TestCreate(void)
{
	schedule_t *sched = SchedCreate();
	printf("\nTest Create\n");
	TestExpectedINTS(SchedSize(sched), 0, "Size");
	TestExpectedINTS(SchedIsEmpty(sched), 1, "Empty");
	
	SchedDestroy(sched);
}



void TestSize(void)
{
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(1);
	size_t interval_in_sec = 2;
	void *param = NULL;
	void *kill_param = NULL;
	uuid_t uid1 = BAD_UID, uid2 = BAD_UID;

	printf("\nTest Size\n");
	TestExpectedINTS(SchedSize(sched), 0, "SizeEmpty");
	
	uid1 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	 TestExpectedINTS(SchedSize(sched), 1, "SizeAdd1Task");
	 
	 uid2 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	 TestExpectedINTS(SchedSize(sched), 2, "SizeAdd2Task");
	 
	 SchedRemoveTask(sched, uid1);
	 TestExpectedINTS(SchedSize(sched), 1, "SizeRemove1Task");
	 
	 SchedRemoveTask(sched, uid2);
	 TestExpectedINTS(SchedSize(sched), 0, "SizeRemove2Task");
	 
	 SchedDestroy(sched);
	 
	 
}
	
void TestIsEmpty(void)
{
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(1);
	size_t interval_in_sec = 2;
	void *param = NULL;
	void *kill_param = NULL;
	uuid_t uid1 = BAD_UID, uid2 = BAD_UID;

	printf("\nTest IsEmpty\n");
	TestExpectedINTS(SchedIsEmpty(sched), 1, "IsEmpty-Empty");
	
	uid1 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	 TestExpectedINTS(SchedIsEmpty(sched), 0, "IsEmpty- NonEmpty");
	 
	 uid2 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	 TestExpectedINTS(SchedIsEmpty(sched), 0, "IsEmpty- NonEmpty");
	 
	 SchedRemoveTask(sched, uid1);
	 SchedRemoveTask(sched, uid2);
	 TestExpectedINTS(SchedIsEmpty(sched), 1, "IsEmpty-Empty");
	 
	 SchedDestroy(sched);
}


void TestAddTask()
{
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(1), run_time1 = RunTime(3);
	size_t interval_in_sec = 6;
	void *param = NULL, *param1 = sched;
	void *kill_param = NULL;
	uuid_t uid1 = BAD_UID;

	printf("\nTest AddTask\n");
	
	uid1 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint2, param, KillNull, kill_param);
		
	TestExpectedINTS(IsEqualUID(uid1, BAD_UID), 0, "AddTask- BADUID");
	
	SchedAddTask(sched, run_time1, interval_in_sec, ActionStop1, param1, KillNull, kill_param);
	SchedRun(sched);
	
	SchedDestroy(sched);
}
	
	
void TestAddTaskAndStop()
{
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(2), run_time1 = RunTime(5);
	size_t interval_in_sec = 1;
	void *param = NULL, *param1 = sched;
	void *kill_param = NULL;
	uuid_t uid1 = BAD_UID;

	printf("\nTest AddAndStopTask\n");
	
	uid1 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
		
	TestExpectedINTS(IsEqualUID(uid1, BAD_UID), 0, "AddTask- BADUID");
	
	SchedAddTask(sched, run_time1, interval_in_sec, ActionStop1, param1, KillNull, kill_param);
	SchedRun(sched);
	
	SchedDestroy(sched);
}


void TestRemoveTask()
{
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(2);
	size_t interval_in_sec = 1;
	void *param = NULL;
	void *kill_param = NULL;
	uuid_t uid1 = BAD_UID, uid2 = BAD_UID, uid3 = BAD_UID;

	printf("\nTest RemoveTask\n");
	
	uid1 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	uid2 = SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	 
	TestExpectedINTS(SchedRemoveTask(sched, uid1), 0, "RemoveTask-ExistedUID");
	TestExpectedINTS(SchedSize(sched), 1, "Remove - Size");
	
	TestExpectedINTS(SchedRemoveTask(sched, uid3), 1, "RemoveTask-NonExistedUID");
	TestExpectedINTS(SchedSize(sched), 1, "Remove - Size");
	
	TestExpectedINTS(SchedRemoveTask(sched, uid2), 0, "RemoveTask-ExistedUID");
	TestExpectedINTS(SchedSize(sched), 0, "Remove - Size");
	 
	 TestExpectedINTS(SchedRemoveTask(sched, uid1), 1, "RemoveTask-EmptyScheduler");
	 
	 TestExpectedINTS(SchedIsEmpty(sched), 1, "Remove-Empty");
	 
	SchedDestroy(sched);
}

	
void TestClear()
{
	schedule_t *sched = SchedCreate();
	time_t run_time = RunTime(2);
	size_t interval_in_sec = 1;
	void *param = NULL;
	void *kill_param = NULL;
	
	printf("\nTest ClearTask\n");
	SchedClear(sched);
	TestExpectedINTS(SchedIsEmpty(sched), 1, "Clear-EmptyScheduler");

	SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);
	SchedAddTask(sched, run_time, interval_in_sec, ActionPrint, param, KillNull, kill_param);

	SchedClear(sched);
	TestExpectedINTS(SchedIsEmpty(sched), 1, "Clear-fULLScheduler");
	
	SchedDestroy(sched);
}



		
void TestProgram(void)
{
	TestCreate();
	TestSize();
	TestIsEmpty();
	TestAddTask();
	TestRemoveTask();
	TestClear();
	TestAddTaskAndStop();
	printf("\n**************Tests event loop:**************\n");
	TestRunSize();
	TestRunClear();
	TestRunRemove();
	TestRunRemoveSelf();
	TestRunAddTask();
	
}

	

int main(void)
{
	TestProgram();
	return 0;
}
