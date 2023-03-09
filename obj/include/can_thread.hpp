#include <thread>

// can bus include
#include <linux/can.h>
#include <linux/can/raw.h>

// socket include 
#include <sys/socket.h>

#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifndef CAN_THREAD_HPP
#define CAN_THREAD_HPP

class CanThread
{
    public:
    
        void stop() { this->m_bStop = true; }

    private:

        int m_socket;
        struct ifreq m_ifr;
        struct sockaddr_can m_addr;

        bool m_bStop;

    protected:

        CanThread(char* sInterface);

        int write_data(struct can_frame frame);
        virtual void notifier(struct can_frame frame) = 0;
        void listener();

        template<typename T>
        T convertCanFrame(struct can_frame frame);

        virtual ~CanThread();

        std::thread* m_tCallback;
        struct can_filter m_filter;

};


enum CanTypeError 
{
    SOCKET_ERR = -1,
    BINDING_ERR = -2,

    WRITE_ON_SCK_ERR = -3,
    RECIVE_CAN_ERR = -4
};


class CanException : public std::exception
{
    public:
        CanException(int nStatusCode, std::string sMsg)
        {
            this->m_nStatusCode = nStatusCode;
            this->m_sMsg = sMsg;
        }

        int getStatusCode() { return m_nStatusCode; }
        std::string getMsg() { return m_sMsg; }

    private:
        int m_nStatusCode;
        std::string m_sMsg;
    
};

#endif