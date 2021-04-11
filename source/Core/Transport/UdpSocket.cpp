#include <stdio.h> // TODO : to remove
#include <iostream> // TODO : to remove

#include "Core/Transport/UdpSocket.h"

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
        if (datagram.Buffer.Size() <= size)
        {
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_addr.s_addr = htonl(datagram.EndPoint.GetAddress());
            addr.sin_port = htons(datagram.EndPoint.GetPort());

            int32_t sentBytes = sendto(m_handle, (const char*)datagram.Buffer.Get(), size, 0 /* flags */, (sockaddr*)&addr, sizeof(sockaddr_in));
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
        return SendTo(datagram, (int32_t)datagram.Buffer.Size());
    }

    SocketResult UdpSocket_Windows::ReceiveFrom(Datagram& datagram, int32_t& bytesRecv)
    {
        typedef int32_t socklen_t;

        sockaddr_in from;
        socklen_t fromLength = sizeof(from);

        bytesRecv = recvfrom(m_handle, (char*)datagram.Buffer.GetPtr(), (int32_t)datagram.Buffer.Size(), 0, (sockaddr*)&from, &fromLength);
        if (bytesRecv > 0)
        {
            datagram.EndPoint.SetAddr(ntohl(from.sin_addr.s_addr), ntohs(from.sin_port));
        }

        return SocketResult::OK;
    }

    void UdpSocket_Windows::LogLastSocketError() const
    {
        // TODO : replace cmd write by a true log system !
        std::cout << "Socket error : " << std::to_string(WSAGetLastError()) << std::endl;
    }
}
#endif // PLATFORM == PLATFORM_WINDOWS
