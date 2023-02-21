#include "../include/res.hpp"

Res::Res(char* sInterface) : CanThread(sInterface) {
    this->m_filter.can_id = 0x191;
    this->m_filter.can_mask = 0x7FF;
}

void Res::notifier(struct can_frame frame)
{
    printf("[ RES ] -> [ ID ]: %d, [ PAYLOAD ]: ", frame.can_id);
    for (int i = 0; i < frame.can_dlc; i++)
        printf("%02X", frame.data[i]);
    printf("\n");

    switch (frame.can_id)
    {
        case PDO:

            this->m_bEmergency = frame.data[0] & 1;
            this->m_bGoSignal = frame.data[0] & 2;
            this->m_bBag = frame.data[0] & 5;

            break;

        default:
            throw CanException(RECIVE_CAN_ERR, "RECIVE a message on RES with wrong ID");
            break;

    }
}

void Res::setPowerOn() 
{
    struct can_frame frame;
    frame.can_id = NMT;
    frame.can_dlc = 1;
    frame.data[0] = 0x01;

    int nRet = this->write_data(frame);
    if (nRet < 0)
        throw CanException(WRITE_ON_SCK_ERR, "Error on POWER ON RES");
}