#include <PCP.h>

void PCP_Init() {
  // Cria 
  SemaphoreHandle_t redSemaphore = xSemaphoreCreateBinary();
  SemaphoreHandle_t blueSemaphore = xSemaphoreCreateBinary();
  SemaphoreHandle_t greenSemaphore = xSemaphoreCreateBinary();

  // Inicialize os semáforos de prioridade
  xSemaphoreGive(redSemaphore);
  xSemaphoreTake(blueSemaphore, 0);
  xSemaphoreTake(greenSemaphore, 0);
}

void PCP_Start() {
 
}