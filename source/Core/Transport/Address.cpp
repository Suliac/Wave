#include "Address.h"

namespace Wave
{
	Address::Address()
		: Address(127, 0, 0, 1, 0)
	{
	}

	Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
		: m_address((a << 24) | (b << 16) | (c << 8) | d), m_port(port)
	{
	}

	Address::Address(unsigned int address, unsigned short port)
		: m_address(address), m_port(port)
	{
	}

	Address::~Address()
	{
	}
}
