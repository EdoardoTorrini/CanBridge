#include "../src/can_thread.cpp"

class Steering : public CanThread
{
    public:
        Steering(char* sInterface);
        
        void setSteeringAngle(float fAngle);

    private:
        void notifier(struct can_frame frame) override;

};


enum SteeringID
{
    // to write
    STEERING_ANGLE = 138,
    STEERING_STATE = 144,

    // to receive
    PROPORTIONAL_ERROR_LEFT_X = 256,
    PROPORTIONAL_ERROR_RIGHT_X,
    PROPORTIONAL_ODOMETRY_MIN_SPEED_LEFT_X,
    PROPORTIONAL_ODOMETRY_MIN_SPEED_LEFT_Y,	
    PROPORTIONAL_ODOMETRY_MIN_SPEED_RIGHT_X,	
    PROPORTIONAL_ODOMETRY_MIN_SPEED_RIGHT_Y,
    PROPORTIONAL_ODOMETRY_MAX_SPEED_LEFT_Y,
    PROPORTIONAL_ODOMETRY_MAX_SPEED_RIGHT_Y,	
    RISE_CUTOFF_FREQUENCY,
    STEERING_CENTER_AUTOSET,	
    STEERING_CENTER_AUTOSET_OK,	
    CURRENT_ANGLE,	
};