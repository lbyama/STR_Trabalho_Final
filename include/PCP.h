#ifndef PCP_H_
#define PCP_H_

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <taskset.h>
#include <semphr.h>

typedef struct {
  TaskHandle_t taskHandle;
  UBaseType_t originalPriority;
} TaskPriorityInfo;

void SemaphoreTakePCP( SemaphoreHandle_t xSemaphore, TickType_t xBlockTime);
void SemaphoreGivePCP( SemaphoreHandle_t xSemaphore );

#endif
