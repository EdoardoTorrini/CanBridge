#include "../include/brake.hpp"

Brake::Brake(char* sInterface) : CanThread(sInterface)
{
    this->m_filter.can_id = CURRENT_PRESSURE;
    this->m_filter.can_mask = 0x7FF;
}

void Brake::notifier(struct can_frame frame)
{

    printf("[ ID ]: %d, [ PAYLOAD ]: ", frame.can_id);
    for (int i = 0; i < frame.can_dlc; i++)
        printf("%02X", frame.data[i]);
    printf("\n");


    switch (frame.can_id)
    {
        case PROPORTIONAL_ERROR_LEFT_X:
            // 352E3500 to send
            this->m_fProportionalErrorLeftX = this->convertCanFrame<float>(frame);
            break;

        case PROPORTIONAL_ERROR_LEFT_Y:
            // 36390000
            this->m_uiProportionalErrorLeftY = this->convertCanFrame<uint32_t>(frame);
            break;

        case PROPORTIONAL_ERROR_RIGHT_X:
            this->m_fProportionalErrorRightX = this->convertCanFrame<float>(frame);
            break;

        case PROPORTIONAL_ERROR_RIGHT_Y:
            this->m_uiProportionalErrorRightY = this->convertCanFrame<uint32_t>(frame);
            break;

        case RISE_CUTOFF_FREQUENCY:
            this->m_fRiseCutoffFrequency = this->convertCanFrame<float>(frame);
            break;

        case ZERO_PRESSURE_AUTOSET_OK:
            // da capire
            break;

        case CURRENT_PRESSURE:
            this->m_fCurrentPressure = this->convertCanFrame<float>(frame);
            break;

        case MAX_PRESSURE:
            this->m_fMaxPressure = this->convertCanFrame<float>(frame);
            break;

        case TARGET_PRESSURE:
            this->m_fTargetPressure = this->convertCanFrame<float>(frame);
            break;

        case CHECK_ABS_STATE:
            // da capire
            break;

        case BRAKING_PERCENTAGE:
            this->m_fBrakingPercentage = this->convertCanFrame<float>(frame);
            break;

        default:
            throw CanException(RECIVE_CAN_ERR, "RECIVE a message on BRAKE with wrong ID");
            break;
    }
}



/*
void Brake::getZeroPressureAutoset()
{

}
bool Brake::getZeroPressureAutosetOK()
{

}
void Brake::checkAbsState()
{
    
}
*/

void Brake::setBreakingPercentage(float fBreakingPerc)
{
    struct can_frame frame;
    frame.can_id = BRAKING_PERCENTAGE;
    frame.can_dlc = sizeof(float);
    
    unsigned char data[sizeof(float)];
    memcpy(data, &fBreakingPerc, sizeof(float));

    for(int i = 0; i < sizeof(float); i++)
        frame.data[i] = data[i];

    int nRet = this->write_data(frame);
    if(nRet < 0)
        throw CanException(WRITE_ON_SCK_ERR, "Error on write BRAKING_PERCENTAGE");
}