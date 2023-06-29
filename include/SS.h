#ifndef SS_H_
#define SS_H_

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <timers.h>

typedef struct SporadicServer
{
    QueueHandle_t aperiodicQueue;
    int startCapacity;
    int capacity;
    int period;
    int replenishmentAmount;
    TimerHandle_t replenishmentTimer;
};

void Replenishment(TimerHandle_t rTimer);
void TaskActivated();
void TaskIdle();
void StartServer();

#endif