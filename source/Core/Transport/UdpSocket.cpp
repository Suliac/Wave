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
	}

	bool UdpSocket::Open(unsigned short port)
	{
		m_handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (m_handle <= 0)
		{
			std::cout << "failed to create socket" << std::endl;
			return false;
		}

		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons((unsigned short)port);

		if (bind(m_handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
		{
            std::cout << "failed to bind socket" << std::endl;
			return false;
		}

#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		int nonBlocking = 1;
		if (fcntl(m_handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
		{
			printf("failed to set non-blocking\n");
			return false;
		}
#elif PLATFORM == PLATFORM_WINDOWS
		DWORD nonBlocking = 1;
		if (ioctlsocket(m_handle, FIONBIO, &nonBlocking) != 0)
		{
            std::cout << "failed to set non-blocking" << std::endl;
			return false;
		}
#endif
        return true;
	}

	bool UdpSocket::Close()
	{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		return close(m_handle);
#elif PLATFORM == PLATFORM_WINDOWS
		return closesocket(m_handle);
#endif
	}
    
	bool UdpSocket::Send(const Address& destination, const void* data, int size)
	{
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(destination.GetAddress());
		addr.sin_port = htons(destination.GetPort());

		int sentBytes = sendto(m_handle, (const char*)data, size, 0, (sockaddr*)&addr, sizeof(sockaddr_in));
		if (sentBytes != size)
		{
            std::cout << "failed to send packet" << std::endl;
			return false;
		}

        return true;
	}

	int UdpSocket::Receive(Address& sender, void* data, int size)
	{
#if PLATFORM == PLATFORM_WINDOWS
		typedef int socklen_t;
#endif
		sockaddr_in from;
		socklen_t fromLength = sizeof(from);

		int byteReceived = recvfrom(m_handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);
        if (byteReceived > 0)
        {
            sender.SetAddr(ntohl(from.sin_addr.s_addr), ntohs(from.sin_port));
        }

        return byteReceived;
	}
}
