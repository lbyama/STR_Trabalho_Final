#include <SS.h>

SporadicServer SS;

void Replenishment(TimerHandle_t rTimer){
    SS.capacity += SS.replenishmentAmount;
}

void TaskActivated(){
    xTimerStart(SS.replenishmentTimer,0);
    SS.startCapacity = SS.capacity;
}

void TaskIdle(){
    SS.replenishmentAmount = SS.capacity - SS.startCapacity;
}

void StartServer(){
    SS.replenishmentTimer = xTimerCreate
                    ("Replenishment Timer",
                        SS.period,
                        pdFALSE,
                        ( void * ) 0,
                        Replenishment
                    );
}