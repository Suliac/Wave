#include <stdio.h> // TODO : to remove
#include <iostream> // TODO : to remove

#include "Core/Transport/UdpSocket.h"

namespace Wave
{
    UdpSocket::UdpSocket()
    {
    }

    UdpSocket::~UdpSocket()
    {
        if (IsOpen())
        {
            Close();
        }
    }

    SocketResult UdpSocket::Open(const IPEndPoint& endPoint, bool isNonBlocking)
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

#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
        int32_t nonBlocking = 1;
        if (fcntl(m_handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
        {
            printf("failed to set non-blocking\n");
            return false;
        }
#elif PLATFORM == PLATFORM_WINDOWS
        DWORD nonBlocking = 1;
        if (ioctlsocket(m_handle, FIONBIO, &nonBlocking) != 0)
        {
            LogLastSocketError();
            return SocketResult::SetBlockingStateFailed;
        }
#endif
        return SocketResult::OK;
    }

    SocketResult UdpSocket::Close()
    {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
        if(!close(m_handle))
#elif PLATFORM == PLATFORM_WINDOWS
        if (!closesocket(m_handle))
#endif
        {
            LogLastSocketError();
            return SocketResult::CloseFailed;
        }
        return SocketResult::OK;
    }

    SocketResult UdpSocket::Send(const IPEndPoint& destination, const void* data, int32_t size)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(destination.GetAddress());
        addr.sin_port = htons(destination.GetPort());

        int32_t sentBytes = sendto(m_handle, (const char*)data, size, 0, (sockaddr*)&addr, sizeof(sockaddr_in));
        if (sentBytes != size)
        {
            LogLastSocketError();
            return SocketResult::SendFailed;
        }

        return SocketResult::OK;
    }

    SocketResult UdpSocket::Receive(IPEndPoint& source, void* data, int32_t size, int32_t& bytesRecv)
    {
#if PLATFORM == PLATFORM_WINDOWS
        typedef int32_t socklen_t;
#endif
        sockaddr_in from;
        socklen_t fromLength = sizeof(from);

        bytesRecv = recvfrom(m_handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);
        if (bytesRecv > 0)
        {
            source.SetAddr(ntohl(from.sin_addr.s_addr), ntohs(from.sin_port));
        }

        return SocketResult::OK;
    }

    void UdpSocket::LogLastSocketError() const
    {
#if PLATFORM == PLATFORM_WINDOWS
        // TODO : replace cmd write by a true log system !
        std::cout << "Socket error : " << std::to_string(WSAGetLastError()) << std::endl;
#endif
    }
}
