/******************************************************************************
* Author        OL110
* Reviewer      Yinon
* Description   Task Module - Header
* Version:      1.0.0
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#ifndef __OL110TASK_H__
#define __OL110TASK_H__

#include <stddef.h>
#include <time.h>   /* time_t */
#include "uid.h"    /* uuid_t */

typedef struct
{
    int (*action)(void *param);
    void *param;
    int (*kill)(void *kill_param);
    void *kill_param;
    size_t interval;
    time_t run_time; 
    uuid_t uid;
} task_t;

/*creates and Initialize The task*/
task_t *TaskInit(time_t run_time, size_t interval_in_sec, int (*action)(void *param), void *param, int (*kill)(void *kill_param), void *kill_param);

/*Run the task*/
int TaskRun(task_t *task);

/*Destroy the task and kill it*/
void TaskDestroy(task_t *task);

/*Update task time*/
void TaskUpdateTime(task_t *task);

#endif /* __OL110TASK_H__ */
