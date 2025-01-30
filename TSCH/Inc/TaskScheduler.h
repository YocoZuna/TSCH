/*
 * TaskScheduler.h
 *
 *  Created on: Jan 27, 2025
 *      Author: dawid
 */
#include <stdint.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#ifndef INC_TASKSCHEDULER_H_
#define INC_TASKSCHEDULER_H_

typedef enum {TaskSCH_OK=0,TaskSCH_ERROR=-1}TaskScheduler_Status;
typedef enum {TaskSCH_ENABLE=1,TaskSCH_DISABLE=-1}TaskScheduler_Enable;
typedef uint32_t time_t;
struct Task;
typedef void(*Task)(void);

typedef struct Task
{
	char name[125];
	Task TaskFunction;
	time_t lastScheduled;
	time_t nextScheduled;
	TaskScheduler_Enable periodic;
	TaskScheduler_Enable enabled;

}TaskScheduler_Typedef;

typedef struct TCB{
	struct Task* task;
	uint32_t* stackFrame;
	struct TCB* nextTask;
}TSCH_TCB;

#define TSCH_getTicks() HAL_GetTick()

#define CHECK_NOT_NULL(x) do{								\
							if(!x)							\
							return TaskSCH_ERROR;}while(0)  \



TaskScheduler_Status TSCH_enableTask(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_disableTask(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_scheduleNext(TaskScheduler_Typedef* self,time_t now, time_t msFromNow);
TaskScheduler_Status TSCH_schedulerEnablePeriodic(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_schedulerDisablePeriodic(TaskScheduler_Typedef* self);
TaskScheduler_Status TSCH_create(TaskScheduler_Typedef* self,uint32_t stackFrameSize);


#endif /* INC_TASKSCHEDULER_H_ */
