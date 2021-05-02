#include <stdio.h> // TODO : to remove
#include <iostream> // TODO : to remove

#include "Wave/Transport/Socket/UdpSocket.h"
#include "Wave/Common/Log/Log.h"

#if PLATFORM == PLATFORM_WINDOWS
namespace Wave
{
    UdpSocket_Windows::UdpSocket_Windows()
    {
        m_handle = INVALID_SOCKET;
    }

    UdpSocket_Windows::~UdpSocket_Windows()
    {
        if (IsOpen())
        {
            Close();
        }
    }

    SocketResult UdpSocket_Windows::Open(const IPEndPoint& endPoint, bool isNonBlocking)
    {
        m_handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (m_handle <= 0)
        {
            LogLastSocketError();
            return SocketResult::CreationFailed;
        }

        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = endPoint.GetAddress();
        address.sin_port = htons(endPoint.GetPort());

        if (bind(m_handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
        {
            LogLastSocketError();
            return SocketResult::BindFailed;
        }

        DWORD nonBlocking = 1;
        if (ioctlsocket(m_handle, FIONBIO, &nonBlocking) != 0)
        {
            LogLastSocketError();
            return SocketResult::SetBlockingStateFailed;
        }

        return SocketResult::OK;
    }

    SocketResult UdpSocket_Windows::Close()
    {
        if (!closesocket(m_handle))
        {
            LogLastSocketError();
            return SocketResult::CloseFailed;
        }
        return SocketResult::OK;
    }

    SocketResult UdpSocket_Windows::SendTo(const Datagram& datagram, int32_t size) const
    {
        if (datagram.BufferSize() <= size)
        {
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = htonl(datagram.GetAddress());
            addr.sin_port = htons(datagram.GetPort());

            int32_t sentBytes = sendto(m_handle, (const char*)datagram.GetData(), size, 0 /* flags */, (sockaddr*)&addr, sizeof(sockaddr_in));
            if (sentBytes != size)
            {
                LogLastSocketError();
                return SocketResult::SendFailed;
            }

            return SocketResult::OK;
        }

        return SocketResult::SendFailed;
    }

    SocketResult UdpSocket_Windows::SendTo(const Datagram& datagram) const
    {
        return SendTo(datagram, (int32_t)datagram.BufferSize());
    }

    SocketResult UdpSocket_Windows::ReceiveFrom(Datagram& datagram, int32_t& bytesRecv)
    {
        typedef int32_t socklen_t;

        sockaddr_in from;
        socklen_t fromLength = sizeof(from);

        bytesRecv = recvfrom(m_handle, (char*)datagram.GetDataPtr(), (int32_t)datagram.BufferSize(), 0, (sockaddr*)&from, &fromLength);
        if (bytesRecv > 0)
        {
            datagram.SetAddr(ntohl(from.sin_addr.s_addr), ntohs(from.sin_port));
        }

        return SocketResult::OK;
    }

    void UdpSocket_Windows::LogLastSocketError() const
    {
        WAVE_ERROR("Socket error : %i", WSAGetLastError());
    }
}
#endif // PLATFORM == PLATFORM_WINDOWS
