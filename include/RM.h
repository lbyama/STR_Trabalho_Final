#ifndef RM_H_
#define RM_H_

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <taskset.h>

void RM_sort(TaskStruct* tasks, int numTasks);
void RM_schedule(TaskStruct* tasks, int numTasks);

#endif