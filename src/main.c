#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include <task.h>
#include <semphr.h>
#include <SS.h>
#include <RM.h>
#include <PCP.h>
#include <taskset.h>

void setup() {


    setupTasks();
    RM_sort(periodicTasks,3);
    RM_schedule(periodicTasks,3);
    createTasks();
    vTaskStartScheduler();
}

void loop(){

}