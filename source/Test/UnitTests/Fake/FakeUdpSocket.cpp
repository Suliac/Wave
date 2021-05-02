#include "FakeUdpSocket.h"

namespace WaveTest
{
    Wave::SocketResult FakeUdpSocket::Open(const Wave::IPEndPoint& endPoint, bool isNonBlocking)
    {
        m_fakeDataRecv.clear();
        m_fakeDataRecv.reserve(512);

        m_isOpen = true;
        return Wave::SocketResult::OK;
    }
    Wave::SocketResult FakeUdpSocket::Close()
    {
        m_isOpen = false;
        m_fakeDataRecv.clear();
        return Wave::SocketResult::OK;
    }
    bool FakeUdpSocket::IsOpen() const
    {
        return m_isOpen;
    }
    Wave::SocketResult FakeUdpSocket::SendTo(const Wave::Datagram& datagram, int32_t size) const
    {
        if (datagram.BufferSize() <= size)
        {
            return Wave::SocketResult::OK;
        }

        return Wave::SocketResult::SendFailed;
    }
    Wave::SocketResult FakeUdpSocket::ReceiveFrom(Wave::Datagram& datagram, int32_t& bytesRecv)
    {
        if (m_fakeDataRecv.size() > 0)
        {
            datagram.SetAddr(0, 0);
        }

        return Wave::SocketResult::OK;
    }

    void FakeUdpSocket::InsertFakeDataRecv(const uint8_t* data, int32_t size)
    {
        m_fakeDataRecv.resize(size);
        std::vector<uint8_t> newData(data, data + size);
        m_fakeDataRecv.insert(m_fakeDataRecv.end(), newData.begin(), newData.end());
    }
}