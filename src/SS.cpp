#include <SS.h>

QueueHandle_t AperiodicQueue;
int StartServerCapacity;
int ServerCapacity;
int ServerPeriod;
int ReplenishmentAmount;
TimerHandle_t ReplenishmentTimer;

void Replenishment(TimerHandle_t rTimer){
    ServerCapacity += ReplenishmentAmount;
}

void TaskActivated(){
    xTimerStart(ReplenishmentTimer,0);
    StartServerCapacity = ServerCapacity;
}

void TaskIdle(){
    ReplenishmentAmount = ServerCapacity - StartServerCapacity;
}

void StartServer(){
    ReplenishmentTimer = xTimerCreate
                    ("Replenishment Timer",
                        ServerPeriod,
                        pdFALSE,
                        ( void * ) 0,
                        Replenishment
                    );
}