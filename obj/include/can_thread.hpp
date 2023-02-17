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


class CanThread
{
    public:
        CanThread(char* sInterface);

        int write_data(struct can_frame frame);
        void stop(bool bStop) { this->m_bStop = bStop; }

        ~CanThread();

    private:
        int m_socket;
        struct ifreq m_ifr;
        struct sockaddr_can m_addr;

        bool m_bStop;

    protected:
        virtual void notifier(struct can_frame frame) = 0;
        void listener();

        std::thread* m_tCallback;

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