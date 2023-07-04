#ifndef TASKSET_H_
#define TASKSET_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define RED_PIN 10
#define GREEN_PIN 11
#define BLUE_PIN 12
#define R_PIN 13
#define G_PIN 14
#define B_PIN 15

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