#include <SS.h>

SporadicServer SS_server;
int ct = 0;

void ButtonHandler(){
    xQueueSend(SS_server.aperiodicQueue, &ct, 5);
}

void AperiodicFunction(){
    for (uint16_t j = 50; j > 0; j--)
        {
            digitalWrite(R_PIN, HIGH);
            digitalWrite(G_PIN, HIGH);
            digitalWrite(B_PIN, HIGH);

            delay(100);
        }
}

void Replenishment(TimerHandle_t rTimer){
    SS_server.capacity += SS_server.replenishmentAmount;
}

void TaskActivated(){
    xTimerStart(SS_server.replenishmentTimer,0);
    SS_server.startCapacity = SS_server.capacity;
}

void TaskIdle(){
    SS_server.replenishmentAmount = SS_server.capacity - SS_server.startCapacity;
}

void StartServer(){
    attachInterrupt(digitalPinToInterrupt(PIN_BUTTON),
                  ButtonHandler,
                  FALLING);
    delayMicroseconds(5000);

    SS_server.replenishmentTimer = xTimerCreate
                    ("Replenishment Timer",
                        SS_server.period,
                        pdFALSE,
                        ( void * ) 0,
                        Replenishment
                    );
}

void ServerScheduler(void *args){

  uint16_t CTime = 0;
  TickType_t periodo = (TickType_t)args;

  {
    BaseType_t inicia_aperiodica;
    while (1)
    {
      TickType_t xLastWakeTime = xTaskGetTickCount();
      inicia_aperiodica = xQueueReceiveFromISR(SS_server.aperiodicQueue,
                                               (uint16_t *)CTime,
                                               &inicia_aperiodica);
      xSemaphoreTake(SemaphoreRGB, pdMS_TO_TICKS(10));
      if (inicia_aperiodica == pdTRUE)
      {
        AperiodicFunction();
        xQueueReceive(SS_server.aperiodicQueue, (uint16_t *)CTime, 1);
      }
      vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(periodo));
      xSemaphoreGive(SemaphoreRGB);
      // Delay para reduzir erro por troca de contexto
      vTaskDelay(10);
    }
  }
}