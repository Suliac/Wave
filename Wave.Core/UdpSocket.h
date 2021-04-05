#pragma once

#include "Address.h"
#include "WaveDefines.h"

namespace Wave
{
	class UdpSocket
	{
	public:
		UdpSocket();
		~UdpSocket();

		bool Open(unsigned short port);
		bool Close();
		bool IsOpen() const;

		bool Send(const Address& destination, const void* data, int size);
		int Receive(Address& sender, void * data, int size);

	private:
		int m_handle;
	};
}

