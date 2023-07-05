#include <taskset.h>

TaskHandle_t redTask;
TaskHandle_t greenTask;
TaskHandle_t blueTask;
TaskHandle_t aperiodicTask;
 
//Mutex
SemaphoreHandle_t  SemaphoreRGB;
SemaphoreHandle_t  SemaphoreRed;
SemaphoreHandle_t  SemaphoreGreen;
SemaphoreHandle_t  SemaphoreBlue;

TaskStruct TaskList[4];

void redFunction(void *arg){
    TickType_t period = (TickType_t)arg;
    TickType_t xLastWakeTime;
    while(1){
        xLastWakeTime = xTaskGetTickCount();
        Serial.println("Tarefa Red ativada");
        xSemaphoreTake(SemaphoreRed, pdMS_TO_TICKS(10));
        digitalWrite(RED_PIN,HIGH);
        delay(10);
        xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
        digitalWrite(R_PIN,HIGH);
        digitalWrite(G_PIN,LOW);
        digitalWrite(B_PIN,LOW);
        delay(10);
        xSemaphoreGive(SemaphoreRGB);
        delay(10);
        digitalWrite(RED_PIN,LOW);
        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));
        xSemaphoreGive(SemaphoreRed);
    }
    
}

void greenFunction(void *arg){
    TickType_t period = (TickType_t)arg;
    TickType_t xLastWakeTime;
    while(1){
        xLastWakeTime = xTaskGetTickCount();
        Serial.println("Tarefa Green ativada");
        xSemaphoreTake(SemaphoreGreen, pdMS_TO_TICKS(10));
        digitalWrite(GREEN_PIN,HIGH);
        delay(10);

        xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
        digitalWrite(R_PIN,LOW);
        digitalWrite(G_PIN,HIGH);
        digitalWrite(B_PIN,LOW);
        delay(10);
        xSemaphoreGive(SemaphoreRGB);
        delay(10);

        digitalWrite(GREEN_PIN,LOW);
        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));

        xSemaphoreGive(SemaphoreGreen);
    }
}

void blueFunction(void *arg){
    TickType_t period = (TickType_t)arg;
    TickType_t xLastWakeTime;
    while(1){
        xLastWakeTime = xTaskGetTickCount();
        Serial.println("Tarefa blue ativada");
        xSemaphoreTake(SemaphoreBlue, pdMS_TO_TICKS(10));
        digitalWrite(BLUE_PIN,HIGH);
        delay(10);
        xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
        digitalWrite(R_PIN,LOW);
        digitalWrite(G_PIN,LOW);
        digitalWrite(B_PIN,HIGH);
        delay(10);
        xSemaphoreGive(SemaphoreRGB);
        delay(10);
        digitalWrite(BLUE_PIN,LOW);
        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));
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

    TaskList[0].period = 100;
    strcpy(TaskList[0].ID, "Red");
    TaskList[0].function = redFunction;
    TaskList[0].handle = redTask;

    TaskList[1].period = 200;
    strcpy(TaskList[1].ID, "Green");
    TaskList[1].function = greenFunction;
    TaskList[1].handle = greenTask;

    TaskList[2].period = 400;
    strcpy(TaskList[2].ID, "Blue");
    TaskList[2].function = blueFunction;
    TaskList[2].handle = blueTask;

    TaskList[3].period = 600;
    strcpy(TaskList[3].ID, "Server");
    TaskList[3].function = NULL;
    TaskList[3].handle = aperiodicTask;
}

void createTasks(int size){
    for (int i = 0; i < size; i++){
        xTaskCreate(TaskList[i].function,
                    TaskList[i].ID,
                    configMINIMAL_STACK_SIZE,
                    (TickType_t *)TaskList[i].period,
                    TaskList[i].priority,
                    &TaskList[i].handle);
    }
}