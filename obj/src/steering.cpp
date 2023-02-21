#include "../include/steering.hpp"

Steering::Steering(char* sInterface) : CanThread(sInterface) 
{
    this->m_filter.can_id = 0x776;
    this->m_filter.can_mask = 0x7FE;
}

void Steering::notifier(struct can_frame frame)
{
    printf("[ STEERING ] -> [ ID ]: %d, [ PAYLOAD ]: ", frame.can_id);
    for (int i = 0; i < frame.can_dlc; i++)
        printf("%02X", frame.data[i]);
    printf("\n");

    switch (frame.can_id)
    {
        case CURRENT_ANGLE:

            char data[sizeof(float)];
            for (unsigned int i = 0; i < frame.can_dlc; i++)
                data[i] = frame.data[i];
            this->m_fCurrentAngle = (float)atof(data);

            break;
        
        default:
            throw CanException(RECIVE_CAN_ERR, "RECIVE a message on STEERING with wrong ID");
            break;
    }

}

void Steering::setSteeringAngle(float fAngle)
{
    struct can_frame frame;
    frame.can_id = STEERING_ANGLE;
    frame.can_dlc = 4;

    unsigned char data[4];
    memcpy(data, &fAngle, sizeof(float));

    for (unsigned int i = 0; i < sizeof(float); i++)
        frame.data[i] = data[i];

    int nRet = this->write_data(frame);
    if (nRet < 0)
        throw CanException(WRITE_ON_SCK_ERR, "Error on write STEERING ANGLE");
}