#include <taskset.h>

TaskHandle_t redTask;
TaskHandle_t greenTask;
TaskHandle_t blueTask;
 
//Mutex
SemaphoreHandle_t  SemaphoreRGB;
SemaphoreHandle_t  SemaphoreRed;
SemaphoreHandle_t  SemaphoreGreen;
SemaphoreHandle_t  SemaphoreBlue;

TaskStruct periodicTasks[3];

void redFunction(void *arg){
    while(1){
        xSemaphoreTake(SemaphoreRed, pdMS_TO_TICKS(10));
        digitalWrite(RED_PIN,HIGH);
        delay(1);
        xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
        digitalWrite(R_PIN,HIGH);
        delay(1);
        digitalWrite(R_PIN,LOW);
        xSemaphoreGive(SemaphoreRGB);
        delay(1);
        digitalWrite(RED_PIN,LOW);
        delay(1);
        xSemaphoreGive(SemaphoreRed);
    }
}

void greenFunction(void *arg){
    while(1){
        xSemaphoreTake(SemaphoreGreen, pdMS_TO_TICKS(10));
        digitalWrite(GREEN_PIN,HIGH);
        delay(1);
        xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
        digitalWrite(G_PIN,HIGH);
        delay(1);
        digitalWrite(G_PIN,LOW);
        xSemaphoreGive(SemaphoreRGB);
        delay(1);
        digitalWrite(GREEN_PIN,LOW);
        delay(1);
        xSemaphoreGive(SemaphoreGreen);
    }
}

void blueFunction(void *arg){
    while(1){
        xSemaphoreTake(SemaphoreBlue, pdMS_TO_TICKS(10));
        digitalWrite(BLUE_PIN,HIGH);
        delay(1);
        xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
        digitalWrite(B_PIN,HIGH);
        delay(1);
        digitalWrite(B_PIN,LOW);
        xSemaphoreGive(SemaphoreRGB);
        delay(1);
        digitalWrite(BLUE_PIN,LOW);
        delay(1);
        xSemaphoreGive(SemaphoreBlue);
    }
}


void setupTasks(){
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);

    SemaphoreRed = xSemaphoreCreateMutex();
    SemaphoreGreen = xSemaphoreCreateMutex();
    SemaphoreBlue = xSemaphoreCreateMutex();
    SemaphoreRGB = xSemaphoreCreateMutex();

    periodicTasks[0].period = 10;
    strcpy(periodicTasks[0].ID, "Red");
    periodicTasks[0].function = redFunction;
    periodicTasks[0].handle = redTask;

    periodicTasks[2].period = 20;
    strcpy(periodicTasks[2].ID, "Green");
    periodicTasks[2].function = greenFunction;
    periodicTasks[2].handle = greenTask;

    periodicTasks[1].period = 40;
    strcpy(periodicTasks[1].ID, "Blue");
    periodicTasks[1].function = blueFunction;
    periodicTasks[1].handle = blueTask;
}

void createTasks(){
    
    for (int i = 0; i < N_TASKS; i++){
        xTaskCreate(periodicTasks[i].function,
                    periodicTasks[i].ID,
                    configMINIMAL_STACK_SIZE,
                    (TickType_t *)periodicTasks[i].period,
                    periodicTasks[i].priority,
                    &periodicTasks[i].handle);
    }
    
}