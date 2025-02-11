#include "TaskScheduler.h"




/*
 * variable to store time of thask scheduler
 */
static volatile time_t schedulerTime = 0;
static TSCH_TCB* scheduledTasks = NULL;
static TSCH_TCB TSCH_getSchedulerTime(void);
TaskScheduler_Status TSCH_enableTask(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_disableTask(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_scheduleNext(TaskScheduler_Typedef* self,time_t now, time_t msFromNow);
TaskScheduler_Status TSCH_schedulerEnablePeriodic(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_schedulerDisablePeriodic(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_create(TaskScheduler_Typedef* self,uint32_t stackFrameSize);
/*
 * Getting system ticks since startup of uC
 */

TaskScheduler_Status TSCH_InitScheduler()
{
	
	CHECK_NOT_NULL(scheduledTasks);
	TSCH_TCB * current = scheduledTasks;
	while(!(current->nextTask)==NULL)
	{
		INIT_DUMMY_STACK(current)
		current = current->nextTask;
	}
	
	return TaskSCH_OK;
}

static TaskScheduler_Status TSCH_getSchedulerTime(void)
{

	schedulerTime= TSCH_getTicks();
	TaskScheduler_Status ret = TaskSCH_OK;
	return ret;
}

/*
 * Enabling task ins task scheduler
 */
TaskScheduler_Status TSCH_enableTask(TaskScheduler_Typedef* self)
{

	CHECK_NOT_NULL(self);
	self->enabled = TaskSCH_ENABLE;
	return TaskSCH_OK;

}
/*
 * Disable task ins task scheduler
 */
TaskScheduler_Status TSCH_disableTask(TaskScheduler_Typedef* self)
{

	CHECK_NOT_NULL(self);
	self->enabled = TaskSCH_ENABLE;
	return TaskSCH_OK;

}
TaskScheduler_Status TSCH_scheduleNext(TaskScheduler_Typedef* self,time_t now, time_t msFromNow)
{
	CHECK_NOT_NULL(self);
	self->nextScheduled = now+msFromNow;
	return TaskSCH_OK;
}

TaskScheduler_Status TSCH_schedulerEnablePeriodic(TaskScheduler_Typedef* self)
{
	CHECK_NOT_NULL(self);
	self->periodic = TaskSCH_ENABLE;
	return TaskSCH_OK;
}
TaskScheduler_Status TSCH_schedulerDisablePeriodic(TaskScheduler_Typedef* self)
{
	CHECK_NOT_NULL(self);
	self->periodic = TaskSCH_DISABLE;
	return TaskSCH_OK;
}
TaskScheduler_Status TSCH_create(TaskScheduler_Typedef* self,uint32_t stackFrameSize)
{
	CHECK_NOT_NULL(self);
    if(scheduledTasks==NULL)
    {
        scheduledTasks = malloc(sizeof(TSCH_TCB));
        scheduledTasks->task = self;
        scheduledTasks->stackFrame = malloc(stackFrameSize);
        scheduledTasks->nextTask = NULL;
        return TaskSCH_OK;
    }
    TSCH_TCB* current = scheduledTasks;
	if(current!=NULL)
	{
		while(current->nextTask!=NULL)
		{
			current = current->nextTask;
		}

		current->nextTask = malloc(sizeof(TSCH_TCB));
		current->nextTask ->task= self;
        current->nextTask ->stackFrame = malloc(stackFrameSize);
		current->nextTask ->nextTask = NULL;
	}

	return TaskSCH_OK;
}









