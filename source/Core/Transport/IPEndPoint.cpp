#include "Core/Transport/IPEndPoint.h"

namespace Wave
{
    IPEndPoint::IPEndPoint()
        : IPEndPoint(127, 0, 0, 1, 0)
    {
    }

    IPEndPoint::IPEndPoint(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t port)
        : m_address((a << 24) | (b << 16) | (c << 8) | d), m_port(port)
    {
    }

    IPEndPoint::IPEndPoint(uint32_t address, uint16_t port)
        : m_address(address), m_port(port)
    {
    }

    IPEndPoint::~IPEndPoint()
    {
    }
}
