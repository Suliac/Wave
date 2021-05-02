#pragma once
#include "Wave/Transport/Common/Buffer.h"
#include "Wave/Transport/Common/IPEndPoint.h"

namespace Wave
{
	class Datagram
	{
	public:
		Datagram(size_t bufferSize, const IPEndPoint& endPoint)
			: m_byteBuffer(bufferSize)
			, m_ipEndPoint(endPoint)
		{
		}

		Datagram(size_t bufferSize)
			: m_byteBuffer(bufferSize)
			, m_ipEndPoint()
		{
		}

		inline void Reset() { m_byteBuffer.Reset(); m_ipEndPoint.SetAddr(0, 0); };
		inline size_t BufferSize() const { return m_byteBuffer.Size(); }
		inline const uint8_t* GetData() const { return m_byteBuffer.Get(); }
		inline uint8_t* GetDataPtr() { return m_byteBuffer.GetPtr(); }
		inline Buffer& GetBuffer() { return m_byteBuffer; }

		inline void SetAddr(uint32_t address, uint16_t port) { m_ipEndPoint.SetAddr(address, port); }
		inline uint32_t GetAddress() const { return m_ipEndPoint.GetAddress(); }
		inline uint16_t GetPort() const { return m_ipEndPoint.GetPort(); }
		inline IPEndPoint& GetEndPoint() { return m_ipEndPoint; }
	private:
		Buffer m_byteBuffer;
		IPEndPoint m_ipEndPoint;
	};
}

