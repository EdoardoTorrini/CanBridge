#include "../src/can_thread.cpp"

class Brake : public CanThread
{
    public:
        Brake(char* sInterface);

        void setBreakingPercentage(float bPerc);

        float getCurrentPressure() { return this->m_fCurrentPressure; }
        float getMaxPressure() { return this->m_fMaxPressure; }
        float getTargetPressure() { return this->m_fTargetPressure; }
        float getProportionalErrorLeftX() { return this->m_fProportionalErrorLeftX; }
        float getProportionalErrorRightX() { return this->m_fProportionalErrorRightX; }
        float getRiseCutoffFrequency() { return this->m_fRiseCutoffFrequency; }
        uint32_t getProportionalErrorLeftY() { return this->m_uiProportionalErrorLeftY; }
        uint32_t getProportionalErrorRightY() { return this->m_uiProportionalErrorRightY; }

        // void getZeroPressureAutoset(); 
        // bool getZeroPressureAutosetOK();
        // void CheckAbsState();
        // DA CHIARIRE

    private:
        void notifier(struct can_frame frame) override;

        float m_fProportionalErrorLeftX;
        float m_fProportionalErrorRightX;
        uint32_t m_uiProportionalErrorLeftY;
        uint32_t m_uiProportionalErrorRightY;	
        float m_fRiseCutoffFrequency;
        float m_fCurrentPressure;
        float m_fMaxPressure;
        float m_fTargetPressure;

        float m_fBrakingPercentage;

};


enum BrakeID
{
    BRAKING_PERCENTAGE = 139,

    PROPORTIONAL_ERROR_LEFT_X = 288,
    PROPORTIONAL_ERROR_LEFT_Y,
    PROPORTIONAL_ERROR_RIGHT_X,
    PROPORTIONAL_ERROR_RIGHT_Y,
    RISE_CUTOFF_FREQUENCY,
    ZERO_PRESSURE_AUTOSET,
    ZERO_PRESSURE_AUTOSET_OK,
    CURRENT_PRESSURE,
    MAX_PRESSURE,
    TARGET_PRESSURE,
    CHECK_ABS_STATE,
};