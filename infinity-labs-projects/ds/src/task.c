/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Shahar
* Description   Task module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include "task.h"
#include <assert.h>			/*assert*/
#include <stdlib.h>			/*NULL*/
#include <stddef.h>			/*size_t*/

void TaskDestroy(task_t *task)
{
	assert(task);
	
	task->kill(task->kill_param);
	task->action = NULL;
	task->kill = NULL;
	task->param = NULL;
	task->kill_param = NULL;
	
	free(task);
	task = NULL;
}

int TaskRun(task_t *task)
{
	assert(task);
	
	return task->action(task->param);
}

task_t *TaskInit(time_t run_time, size_t interval_in_sec, int (*action)(void *param), void *param, int (*kill)(void *kill_param), void *kill_param)
{
	task_t *task = NULL;
	uuid_t uid = BAD_UID;
	
	task = (task_t *)malloc(sizeof(task_t));	
	if (NULL == task)
	{
		return NULL;
	}
	
	uid = GetUID();
	if (IsEqualUID(BAD_UID, uid))
	{
		free(task);
		task = NULL;
		
		return NULL;
	}
	
	task->action = action;
	task->param = param;
	task->kill = kill;
	task->kill_param = kill_param;
	task->interval = interval_in_sec;
	task->run_time = run_time;
	task->uid = uid;
	
	return task;
}

void TaskUpdateTime(task_t *task)
{
	assert(task);
	
	task->run_time += task->interval;
}
