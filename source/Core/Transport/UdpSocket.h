#pragma once

#include "Core/Common/WaveDefines.h"
#include "Core/Transport/Address.h"

namespace Wave
{
    class UdpSocket
    {
    public:
        UdpSocket();
        ~UdpSocket();

        bool Open(unsigned short port);
        bool Close();
        inline bool IsOpen() const { return m_handle != INVALID_SOCKET; }

        bool Send(const Address& destination, const void* data, int size);
        int Receive(Address& sender, void* data, int size);

    private:
        int m_handle;
    };
}

