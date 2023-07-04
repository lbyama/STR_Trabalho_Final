#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include <task.h>
#include <semphr.h>
#include <SS.h>
#include <RM.h>
#include <PCP.h>
#include <taskset.h>

void setup() {
    Serial.begin(115200);
    setupTasks();
    setupServer();
    RM_sort(TaskList,4);
    RM_schedule(TaskList,4);
    createTasks(4);
    vTaskStartScheduler();
}

void loop(){

}