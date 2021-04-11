#pragma once

#include "Core/Common/WaveDefines.h"
#include "Core/Transport/IPEndPoint.h"

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
        virtual SocketResult Send(const IPEndPoint& destination, const void* data, int32_t size) = 0;
        virtual SocketResult Receive(IPEndPoint& source, void* data, int32_t size, int32_t& bytesRecv) = 0;
	};
}
