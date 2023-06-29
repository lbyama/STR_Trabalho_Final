#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include <task.h>
#include <semphr.h>
#include <SS.h>
#include <PCP.h>
#include <taskset.h>

void setup() {

    setupTasks();
    vTaskStartScheduler();
}

void loop(){

}