#include <SS.h>

QueueHandle_t AperiodicQueue;

SporadicServer::SporadicServer(){
    AperiodicQueue = xQueueCreate( 10, sizeof( unsigned long ) );
};