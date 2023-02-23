#include "../include/brake.hpp"

Brake::Brake(char* sInterface) : CanThread(sInterface)
{
    this->m_filter.can_id = 0x120; //modifica
    this->m_filter.can_mask = 0x120; //modifica
}

void Brake::notifier(struct can_frame frame)
{

    printf("[ ID ]: %d, [ PAYLOAD ]: ", frame.can_id);
    for (int i = 0; i < frame.can_dlc; i++)
        printf("%02X", frame.data[i]);
    printf("\n");


    switch(frame.can_id){
        case PROPORTIONAL_ERROR_LEFT_X:
            // 352E3500 to send
            this->m_fProportionalErrorLeftX = (float)atof(this->dataToChar(frame));
            break;
        case PROPORTIONAL_ERROR_LEFT_Y:
            // 36390000
            this->m_uiProportionalErrorLeftY = (uint32_t)atoi(this->dataToChar(frame));
            break;
        case PROPORTIONAL_ERROR_RIGHT_X:
            this->m_fProportionalErrorRightX = (float)atof(this->dataToChar(frame));
            break;
        case PROPORTIONAL_ERROR_RIGHT_Y:
            this->m_uiProportionalErrorRightY = (uint32_t)atoi(this->dataToChar(frame));
            break;
        case RISE_CUTOFF_FREQUENCY:
            this->m_fRiseCutoffFrequency = (float)atof(this->dataToChar(frame));
            break;
        case ZERO_PRESSURE_AUTOSET_OK:
            // da capire
            break;
        case CURRENT_PRESSURE:
            this->m_fCurrentPressure = (float)atof(this->dataToChar(frame));
            break;
        case MAX_PRESSURE:
            this->m_fMaxPressure = (float)atof(this->dataToChar(frame));
            break;
        case TARGET_PRESSURE:
            this->m_fTargetPressure = (float)atof(this->dataToChar(frame));
            break;
        case CHECK_ABS_STATE:
            // da capire
            break;
        case BRAKING_PERCENTAGE:
            this->m_fBrakingPercentage = (float)atof(this->dataToChar(frame));
            break;
        default:
            break;
    }
}


float Brake::getProportionalErrorLeftX()
{
    return this->m_fProportionalErrorLeftX;
}

uint32_t Brake::getProportionalErrorLeftY()
{   
    return this->m_uiProportionalErrorLeftY;
}

float Brake::getProportionalErrorRightX()
{
    return this->m_fProportionalErrorRightX;
}

uint32_t Brake::getProportionalErrorRightY()
{
    return this->m_uiProportionalErrorRightY;
}

float Brake::getRiseCutoffFrequency()
{
    return this->m_fRiseCutoffFrequency;
}

// void Brake::getZeroPressureAutoset()
// {

// }

// bool Brake::getZeroPressureAutosetOK()
// {

// }

float Brake::getCurrentPressure()
{
    return this->m_fCurrentPressure;
}

float Brake::getMaxPressure()
{
    return this->m_fMaxPressure;
}

float Brake::getTargetPressure()
{
    return this->m_fTargetPressure;
}

// void Brake::checkAbsState()
// {

// }

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


char* Brake::dataToChar(struct can_frame frame){
    char* data;
    data = new char[frame.can_dlc];

    for (unsigned int i = 0; i < frame.can_dlc; i++)
        data[i] = frame.data[i];

    return data;
}