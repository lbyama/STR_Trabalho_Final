#ifndef SS_H_
#define SS_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <timers.h>
#include <queue.h>
#include <taskset.h>

#define PIN_BUTTON 16

typedef struct sporadic_server
{
    QueueHandle_t aperiodicQueue;
    int startCapacity;
    int capacity;
    int period;
    int replenishmentAmount;
    TimerHandle_t replenishmentTimer;
} SporadicServer;

void Replenishment(TimerHandle_t rTimer);
void TaskActivated();
void TaskIdle();
void StartServer();

#endif