#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "SS.h"
//Tasks
TaskHandle_t        ledTaskH;
 
//Mutex
SemaphoreHandle_t   SerialMutex;
