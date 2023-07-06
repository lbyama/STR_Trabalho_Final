#include <PCP.h>

TaskPriorityInfo taskPriorities[4];


UBaseType_t PriorityCeiling = 1;
UBaseType_t currentTaskPriority = 0;


void SemaphoreTakePCP(SemaphoreHandle_t xSemaphore, TickType_t xBlockTime) {
  
  TaskHandle_t currentTaskHandle = xTaskGetCurrentTaskHandle();

  // Encontra a entrada correspondente na estrutura de dados para a tarefa atual
  TaskPriorityInfo *currentTaskInfo = NULL;
  for (int i = 0; i < MAX_TASKS; i++) {
    if (taskPriorities[i].taskHandle == currentTaskHandle) {
      currentTaskInfo = &taskPriorities[i];
      break;
    }
  }

  // Se não encontrou a entrada correspondente, cria uma nova
  if (currentTaskInfo == NULL) {
    for (int i = 0; i < MAX_TASKS; i++) {
      if (taskPriorities[i].taskHandle == NULL) {
        currentTaskInfo = &taskPriorities[i];
        currentTaskInfo->taskHandle = currentTaskHandle;
        currentTaskInfo->originalPriority = uxTaskPriorityGet(currentTaskHandle);
        break;
      }
    }
  }
    Serial.print("Current Task Priority: ");
    Serial.println(uxTaskPriorityGet(currentTaskHandle), DEC);
    currentTaskPriority = uxTaskPriorityGet(currentTaskHandle);
    if (currentTaskPriority > PriorityCeiling) {
        vTaskPrioritySet(currentTaskHandle, PriorityCeiling);
    }
    
    xSemaphoreTake(xSemaphore, xBlockTime);
    
    
    Serial.print("Current Task Priority: ");
    Serial.println(uxTaskPriorityGet(currentTaskHandle), DEC);

}

void SemaphoreGivePCP(SemaphoreHandle_t xSemaphore) {
  TaskHandle_t currentTaskHandle = xTaskGetCurrentTaskHandle();

  // Procura a entrada correspondente na estrutura de dados para a tarefa atual
  TaskPriorityInfo *currentTaskInfo = NULL;
  for (int i = 0; i < MAX_TASKS; i++) {
    if (taskPriorities[i].taskHandle == currentTaskHandle) {
      currentTaskInfo = &taskPriorities[i];
      break;
    }
  }

  if (currentTaskInfo != NULL) {
    xSemaphoreGive(xSemaphore);

    // Restaura a prioridade original da tarefa após a região crítica
    vTaskPrioritySet(currentTaskHandle, currentTaskInfo->originalPriority);
  }
}
