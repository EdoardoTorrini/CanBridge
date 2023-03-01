#include "../include/can_thread.hpp"

CanThread::CanThread(char* sInterface) 
{
    this->m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (this->m_socket < 0)
        throw CanException(SOCKET_ERR, "Error on socket define");

    strcpy(this->m_ifr.ifr_name, sInterface);
    ioctl(this->m_socket, SIOCGIFINDEX, &this->m_ifr);

    memset(&this->m_addr, 0, sizeof(this->m_addr));
    this->m_addr.can_family = AF_CAN;
    this->m_addr.can_ifindex = this->m_ifr.ifr_ifindex;

    if (bind(this->m_socket, (struct sockaddr *)&this->m_addr, sizeof(this->m_addr)) < 0)
        throw CanException(BINDING_ERR, "Error on socket association");

    this->m_bStop = false;
    this->m_tCallback = new std::thread(&CanThread::listener, this);
}

int CanThread::write_data(struct can_frame frame)
{
    int nRet = 0;
    
    if (write(this->m_socket, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
        nRet = -1;

    return nRet;
}

void CanThread::listener()
{
    
    while (!this->m_bStop)
    {
        struct can_frame cfd;

        int nBytes = read(this->m_socket, &cfd, sizeof(struct can_frame));
        if ((nBytes > 0) && (this->m_filter.can_id != 0) && (this->m_filter.can_mask != 0))
            if ((cfd.can_id & this->m_filter.can_mask) == (this->m_filter.can_id & this->m_filter.can_mask))
                this->notifier(cfd);

    }

}

template<typename T>
T CanThread::convertCanFrame(struct can_frame frame)
{
    unsigned char cFrame[sizeof(T)];
    int i, j = sizeof(T) - 1;
    T tRet;

    for(i = 0; i < sizeof(T); i++)
    {
        cFrame[i] = frame.data[j];
        j --;
    }
    tRet = *(T*)&cFrame;

    return tRet;
}

CanThread::~CanThread()
{
    if (this->m_tCallback->joinable())
    {
        this->stop();
        this->m_tCallback->join();
    }
}