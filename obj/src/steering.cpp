#include "../include/steering.hpp"

Steering::Steering(char* sInterface) : CanThread(sInterface) 
{
    
}

void Steering::notifier(struct can_frame frame)
{
    printf("[ ID ]: %d, [ PAYLOAD ]: ", frame.can_id);
    for (int i = 0; i < frame.can_dlc; i++)
        printf("%02X", frame.data[i]);
    printf("\n");
}