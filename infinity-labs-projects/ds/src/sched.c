/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Shahar
* Description   schedular module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/
#include <stdlib.h> /* malloc() */
#include <assert.h>     /* assert */

#include "priority_q.h"	/*API of priority_q*/
#include "sched.h"		/*API of schedular*/
#include "task.h"		/*API of task*/

struct scheduler
{
    pq_t *pq;
    task_t *running_task;
	int is_running;
	int remove_running_task; 
};


static int prioritize(const void *task1, const void *task2)
{
	assert(task1);
	assert(task2);
	
	if ((((task_t *)task1)->run_time) > (((task_t *)task2)->run_time))
	{
		return -1;
	}
	else if ((((task_t *)task1)->run_time) < (((task_t *)task2)->run_time))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static uuid_t GetUIDrunning_task(schedule_t *sched)
{
	assert(sched);
	if (sched->running_task)
	{
		return sched->running_task->uid;
	}
	else
	{
		return BAD_UID;
	}
}

static int is_uid_match(const void *criteria, const void *data)
{
	return IsEqualUID(*(uuid_t *)criteria, (((task_t *)data)->uid));
}

schedule_t *SchedCreate(void)
{
	schedule_t *sched = (schedule_t *)malloc(sizeof(schedule_t));
	
	if(!(sched))
	{
		return NULL;
	}
	
	sched->running_task = NULL;
	sched->is_running = 0;
	sched->remove_running_task = 0;
	
	sched->pq = PQCreate(prioritize);
	if(!(sched->pq))
	{
		free(sched);
		sched = NULL;
		
		return NULL;
	}
	
	return sched;
}

void SchedDestroy(schedule_t *sched)
{
	assert(sched);
	
	SchedClear(sched);
	
	PQDestroy(sched->pq);
	
	free(sched);
	sched = NULL;
}

size_t SchedSize(const schedule_t *sched)
{
	assert(sched);
	
	return PQSize(sched->pq) + (sched->running_task != NULL);
}

int SchedIsEmpty(const schedule_t *sched)
{
	assert(sched);
	
	return PQIsEmpty(sched->pq) && (sched->running_task == NULL);
}

uuid_t SchedAddTask(schedule_t *sched, time_t run_time, size_t interval_in_sec, int (*action)(void *param), void *param, int (*kill)(void *kill_param), void *kill_param)
{
	task_t *task = NULL;
	
	assert(sched);
	assert(interval_in_sec > 0);
	
	task = TaskInit(run_time, interval_in_sec, action, param, kill, kill_param);
	if (NULL == task)
	{
		return BAD_UID;
	}
	
	if (PQEnqueue(sched->pq, task))
	{
		free(task);
		task = NULL;
		
		return BAD_UID;
	}
	else
	{
		return task->uid;
	}
}

int SchedRemoveTask(schedule_t *sched, uuid_t uid)
{
	task_t *RemovedTask = NULL;
	
	assert(sched);
	
	RemovedTask = PQEraseIf(sched->pq, &uid, is_uid_match);
	
	if (RemovedTask)
	{
		TaskDestroy(RemovedTask);
		
		return 0;
	}
	else if (IsEqualUID(uid, GetUIDrunning_task(sched)))
	{
		sched->remove_running_task = 1;
		
		return 0;
	}
	else
	{	
		return 1;
	}
	
}

void SchedClear(schedule_t *sched)
{
	assert(sched);
	
	while (!SchedIsEmpty(sched))
	{
		task_t *task = PQDequeue(sched->pq);
		TaskDestroy(task);
		task = NULL;
	}
}

int SchedRun(schedule_t *sched)
{
	assert(sched);
	
	sched->is_running = 1;
	
	while (!SchedIsEmpty(sched) && sched->is_running)
	{
		time_t current_time = time(NULL);
		if (current_time == -1)
		{
			return 1;
		}
		sched->running_task = PQDequeue(sched->pq);
		
		if ((sched->running_task->run_time) > current_time)
		{
			while(0 != sleep((sched->running_task->run_time) - current_time));
		}
		
		if ((!TaskRun(sched->running_task)) && sched->running_task)
		{
			TaskUpdateTime(sched->running_task);
			
			if (sched->remove_running_task)
			{
				TaskDestroy(sched->running_task);
			}
			else if (PQEnqueue(sched->pq, sched->running_task))
			{
				TaskDestroy(sched->running_task);
				
				return 1;
			}
			
			sched->running_task = NULL;
		}
		else if (sched->running_task)
		{
			TaskDestroy(sched->running_task);
			
			sched->running_task = NULL;
		}
	}
	
	return 0;
}

void SchedStop(schedule_t *sched)
{
	assert(sched);
	
	sched->is_running = 0;
}

