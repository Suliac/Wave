#pragma once
#include <Core/Transport/Buffer.h>
#include <Core/Transport/IPEndPoint.h>

namespace Wave
{
	class Datagram
	{
	public:
		Datagram(size_t bufferSize, const IPEndPoint& endPoint)
			: Buffer(bufferSize)
			, EndPoint(endPoint)
		{
		}

		Datagram(size_t bufferSize)
			: Buffer(bufferSize)
			, EndPoint()
		{
		}

		inline void Reset() { Buffer.Reset(); EndPoint.SetAddr(0, 0); };

		Buffer Buffer;
		IPEndPoint EndPoint;
	};
}

