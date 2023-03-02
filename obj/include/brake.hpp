#include "../src/can_thread.cpp"

class Brake : public CanThread
{
    public:
        Brake(char* sInterface);

        void setBreakingPercentage(float bPerc);
        char* dataToChar(struct can_frame frame);

        float getCurrentPressure()
        {
            return this->m_fCurrentPressure;
        }

        float getMaxPressure()
        {
            return this->m_fMaxPressure;
        }

        float getTargetPressure()
        {
            return this->m_fTargetPressure;
        }

        float getProportionalErrorLeftX()
        {
            return this->m_fProportionalErrorLeftX;
        }

        uint32_t getProportionalErrorLeftY()
        {   
            return this->m_uiProportionalErrorLeftY;
        }

        float getProportionalErrorRightX()
        {
            return this->m_fProportionalErrorRightX;
        }

        uint32_t getProportionalErrorRightY()
        {
            return this->m_uiProportionalErrorRightY;
        }

        float getRiseCutoffFrequency()
        {
            return this->m_fRiseCutoffFrequency;
        }

        //void getZeroPressureAutoset(); 
        //bool getZeroPressureAutosetOK();
        //void CheckAbsState();
        // DA CHIARIRE

    private:
        void notifier(struct can_frame frame) override;

        float m_fProportionalErrorLeftX;
        uint32_t m_uiProportionalErrorLeftY;
        float m_fProportionalErrorRightX;	
        uint32_t m_uiProportionalErrorRightY;	
        float m_fRiseCutoffFrequency;
        float m_fCurrentPressure;
        float m_fMaxPressure;
        float m_fTargetPressure;

        float m_fBrakingPercentage;

};


enum BrakeID
{
    PROPORTIONAL_ERROR_LEFT_X = 288,    //hex: 120
    PROPORTIONAL_ERROR_LEFT_Y = 289,    //hex: 121          
    PROPORTIONAL_ERROR_RIGHT_X = 290,   //hex: 122
    PROPORTIONAL_ERROR_RIGHT_Y = 291,   //hex: 123
    RISE_CUTOFF_FREQUENCY = 292,        //hex: 124
    ZERO_PRESSURE_AUTOSET = 293,        //hex: 125
    ZERO_PRESSURE_AUTOSET_OK = 294,     //hex: 126
    CURRENT_PRESSURE = 295,             //hex: 127
    MAX_PRESSURE = 296,                 //hex: 128
    TARGET_PRESSURE = 297,              //hex: 129
    CHECK_ABS_STATE = 298,              //hex: 12A
    BRAKING_PERCENTAGE = 139,
};