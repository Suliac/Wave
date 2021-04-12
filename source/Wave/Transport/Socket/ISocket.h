#pragma once

#include "Wave/Common/WaveDefines.h"
#include "Wave/Transport/Common/IPEndPoint.h"
#include "Wave/Transport/Common/Datagram.h"

namespace Wave
{
    /**
     * \enum SocketResult
     * \brief All the code errors we can get from the sockets
     */
    enum class SocketResult : int16_t
    {
        OK = 1,
        Failed = -999,
        CreationFailed,
        BindFailed,
        SetBlockingStateFailed,
        CloseFailed,
        SendFailed,
        RecvFailed
    };

	class ISocket
	{
	public:
        virtual SocketResult Open(const IPEndPoint& endPoint, bool isNonBlocking = true) = 0;
        virtual SocketResult Close() = 0;
        virtual bool IsOpen() const = 0;
        virtual SocketResult SendTo(const Datagram& datagram, int32_t size) const = 0;
        virtual SocketResult ReceiveFrom(Datagram& datagram, int32_t& bytesRecv) = 0;
	};
}
