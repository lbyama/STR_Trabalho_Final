#include <SS.h>

SporadicServer SS_server;
int ct = 0;

void buttonHandler(){
  xQueueSend(SS_server.aperiodicQueue, &ct, 5); //quando o botão é apertado, coloca uma tarefa na fila
}

void aperiodicFunction(){
  /* Acende o led RGB no modo branco*/
  xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
  Serial.println("Tarefa aperiodica ativada");
  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, HIGH);
  delay(10);
  xSemaphoreGive(SemaphoreRGB);
}

void replenishment(TimerHandle_t rTimer){
  SS_server.capacity += SS_server.replenishmentAmount; //Adiciona o RTA a capacidade
  xTimerChangePeriod(SS_server.capacityTimer,pdMS_TO_TICKS(SS_server.capacity),0); //Muda o timer da capacidade
}

void taskActivated(void* arg){
  if((TaskHandle_t)arg == aperiodicTask){
    Serial.println("Servidor aperiodico ativado");
    xTimerStart(SS_server.replenishmentTimer,0); //Inicia o timer de replenishment

    xTimerChangePeriod(SS_server.capacityTimer,pdMS_TO_TICKS(SS_server.capacity),0); //Muda o periodo do timer da capacidade
    xTimerStart(SS_server.capacityTimer,0); //Inicia timer da capacidade
  }
}

void taskIdle(void* arg){
  if((TaskHandle_t)arg == aperiodicTask){
    Serial.println("Servidor aperiodico desativado");
    TickType_t remainingTime = xTimerGetExpiryTime(SS_server.capacityTimer) - xTaskGetTickCount();  //Calcula o restante da capacidade
    xTimerStop(SS_server.capacityTimer,0);

    SS_server.replenishmentAmount = SS_server.capacity - remainingTime*portTICK_PERIOD_MS; //Calcula o RTA
    SS_server.capacity = remainingTime;   //Converte de ticks para ms e capacidade recebe o que sobrou de tempo
  }
}

void yield(TimerHandle_t rTimer){
  /*Chamado quando o timer da capacidade expira, ou seja,
  quando o servidor gastou toda a sua capacidade*/
  Serial.println("Capacidade do servidor esgotada");
  SS_server.replenishmentAmount = SS_server.capacity;
  SS_server.capacity = 0;
  taskYIELD(); //Abre mão do processador
}

void setupServer(){
  int capacity = 5;
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON),
                buttonHandler,
                FALLING);
  delay(500);

  SS_server.replenishmentTimer = xTimerCreate
                  ("Replenishment Timer",
                      SS_server.period,
                      pdFALSE,
                      ( void * ) 0,
                      replenishment
                  );
  
  SS_server.capacityTimer = xTimerCreate
                ("Capacity Timer",
                    pdMS_TO_TICKS(capacity),
                    pdFALSE,
                    ( void * ) 0,
                    yield
                );

  strcpy(TaskList[3].ID, "SS Server");
  TaskList[3].function = serverScheduler;
}

void serverScheduler(void *args){
  uint16_t CTime = 0;
  TickType_t periodo = (TickType_t)args;
  TickType_t xLastWakeTime;
  {
    while (1)
    {
      xLastWakeTime = xTaskGetTickCount();
      while (xQueuePeek(SS_server.aperiodicQueue,(uint16_t *)CTime,1) == pdTRUE)  //Se tem tarefa na fila
      {
        xQueueReceive(SS_server.aperiodicQueue, (uint16_t *)CTime, 1);
        aperiodicFunction();
      }
      vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(periodo)); //Espera até o próximo periodo do servidor
    }
  }
}
