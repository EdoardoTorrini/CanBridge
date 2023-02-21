#ifndef RES_HPP
#define RES_HPP

#include "can_thread.hpp"

class Res : public CanThread {

    public:
        Res(char* sInterface);

        void setPowerOn();
        bool getEmergency() { return m_bEmergency; }
        bool getGoSignal() { return m_bGoSignal; }
        bool getBag() { return m_bBag; }

    private:
        bool m_bEmergency;
        bool m_bGoSignal;
        bool m_bBag;

        void notifier(struct can_frame frame) override;
};

enum ResID
{
    NMT = 0,
    PDO = 401,
};

#endif