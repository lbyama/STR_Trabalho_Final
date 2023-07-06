#ifndef SS_H_
#define SS_H_

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <timers.h>
#include <queue.h>
#include <taskset.h>

#define PIN_BUTTON 2

//#define traceTASK_SWITCHED_IN() taskActivated(pxCurrentTCB)    //Chama essa função toda vez que uma tarefa é colocada no processador
//#define traceTASK_SWITCHED_OUT() taskIdle(pxCurrentTCB)        //Chama essa função toda vez que uma tarefa é tirada do processador

typedef struct sporadic_server
{
    QueueHandle_t aperiodicQueue;   //fila das tarefas aperiodicas
    int capacity;   //capacidade em milisegundos
    int period;     //periodo do servidor
    int replenishmentAmount;    //RTA = quantidade a ser adicionada a capacidade
    TimerHandle_t replenishmentTimer;   //timer para o RT = momento para aumentar a capacidade
    TimerHandle_t capacityTimer;        //timer para acabar a capacidade
} SporadicServer;

void buttonHandler();
void aperiodicFunction();
void replenishment(TimerHandle_t rTimer);
void taskActivated(void* arg);
void taskIdle(void* arg);
void yield(TimerHandle_t rTimer);
void setupServer();
void serverScheduler(void *args);

#endif