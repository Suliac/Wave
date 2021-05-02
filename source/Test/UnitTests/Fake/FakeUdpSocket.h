#pragma once

#include <vector>

#include "Wave/Transport/Socket/ISocket.h"

namespace WaveTest
{
	class FakeUdpSocket : public Wave::ISocket
	{
	public:
		virtual Wave::SocketResult Open(const Wave::IPEndPoint& endPoint, bool isNonBlocking = true) override;
		virtual Wave::SocketResult Close() override;
		virtual bool IsOpen() const override;
		virtual Wave::SocketResult SendTo(const Wave::Datagram& datagram, int32_t size) const override;
		virtual Wave::SocketResult ReceiveFrom(Wave::Datagram& datagram, int32_t& bytesRecv) override;

		void InsertFakeDataRecv(const uint8_t* data, int32_t size);
	private:
		std::vector<uint8_t> m_fakeDataRecv;
		bool m_isOpen = false;
	};
}

