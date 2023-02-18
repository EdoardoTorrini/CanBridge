#include "../include/steering.hpp"

Steering::Steering(char* sInterface) : CanThread(sInterface) 
{
    this->m_filter.can_id = 0x776;
    this->m_filter.can_mask = 0x7FE;
}

void Steering::notifier(struct can_frame frame)
{
    if ((frame.can_id & this->m_filter.can_mask) == (this->m_filter.can_id & this->m_filter.can_mask))
    {
        printf("[ ID ]: %d, [ PAYLOAD ]: ", frame.can_id);
        for (int i = 0; i < frame.can_dlc; i++)
            printf("%02X", frame.data[i]);
        printf("\n");
    }
}