#pragma once
namespace Wave
{
	class Address
	{
	public:
		~Address();
		Address();
		Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
		Address(unsigned int address, unsigned short port);

		unsigned int GetAddress() const { return m_address; }
		inline unsigned short GetPort() const { return m_port; }

	private:
		unsigned int	m_address;
		unsigned short  m_port;
	};
}

