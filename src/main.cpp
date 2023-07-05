#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include <task.h>
#include <semphr.h>
//#include <SS.h>
#include <RM.h>
//#include <PCP.h>
#include <taskset.h>

void setup() {
    Serial.begin(9600);
    Serial.println("setupTasks");
    setupTasks();
    Serial.println("setupServer");
    //setupServer();
    Serial.println("RM_Sort");
    RM_sort(TaskList,4);
    Serial.println("RM_Schedule");
    RM_schedule(TaskList,4);
    Serial.println("createTasks");
    createTasks(4);
    Serial.println("vTaskStartScheduler");
    
}

void loop(){
    while(1){

    }
}