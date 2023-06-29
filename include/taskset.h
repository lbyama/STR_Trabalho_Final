#ifndef TASKSET_H_
#define TASKSET_H_

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef	struct TaskStruct
{
    int period;
    char ID[5];
    uint8_t priority;
    TaskHandle_t handle;
    TaskFunction_t function;
};

void redFunction(void *arg);
void blueFunction(void *arg);
void greenFunction(void *arg);
void setupTasks();

#endif