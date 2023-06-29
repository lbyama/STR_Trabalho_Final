#include <taskset.h>

#define RED_PIN 10
#define BLUE_PIN 11
#define GREEN_PIN 12

#define N_TASKS 3

TaskHandle_t redTask;
TaskHandle_t blueTask;
TaskHandle_t greenTask;
 
//Mutex
SemaphoreHandle_t  SerialMutex;

TaskStruct periodicTasks[3];

void redFunction(void *arg){

}

void blueFunction(void *arg){
    
}

void greenFunction(void *arg){
    
}

void setupTasks(){
    periodicTasks[0].period = 10;
    strcpy(periodicTasks[0].ID, "Red");
    periodicTasks[0].function = redFunction;
    periodicTasks[0].handle = redTask;

    periodicTasks[1].period = 20;
    strcpy(periodicTasks[1].ID, "Blue");
    periodicTasks[1].function = blueFunction;
    periodicTasks[1].handle = blueTask;

    periodicTasks[2].period = 40;
    strcpy(periodicTasks[2].ID, "Green");
    periodicTasks[2].function = greenFunction;
    periodicTasks[2].handle = greenTask;

    for (int i = 0; i < N_TASKS; i++){
        xTaskCreate(periodicTasks[i].function,
                    periodicTasks[i].ID,
                    configMINIMAL_STACK_SIZE,
                    (TickType_t *)periodicTasks[i].period,
                    periodicTasks[i].priority,
                    &periodicTasks[i].handle);
    }
}