#include "../src/can_thread.cpp"

class Steering : public CanThread
{
    public:
        Steering(char* sInterface);

    private:
        void notifier(struct can_frame frame) override;

};