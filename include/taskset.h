#ifndef TASKSET_H_
#define TASKSET_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define RED_PIN 8
#define GREEN_PIN 9
#define BLUE_PIN 10
#define R_PIN 3
#define G_PIN 4
#define B_PIN 5

#define N_TASKS 3

typedef struct task_struct
{
    int period;
    char ID[10];
    uint8_t priority;
    TaskHandle_t handle;
    TaskFunction_t function;
} TaskStruct;

extern TaskHandle_t aperiodicTask;
extern TaskStruct TaskList[4];
extern SemaphoreHandle_t  SemaphoreRGB;

void redFunction(void *arg);
void blueFunction(void *arg);
void greenFunction(void *arg);
void setupTasks();
void createTasks(int size);

#endif