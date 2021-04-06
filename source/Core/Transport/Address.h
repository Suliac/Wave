#pragma once
#include <string> // TODO : change that

namespace Wave
{
    class Address
    {
    public:
        ~Address();
        Address();
        Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
        Address(unsigned int address, unsigned short port);

        inline unsigned int GetAddress() const { return m_address; }
        inline std::string GetAddressStr() const { return std::to_string(GetA()) + "." + std::to_string(GetB()) + "." + std::to_string(GetC()) + "." + std::to_string(GetD()); }
        inline unsigned char GetA() const { return m_address >> 24; }
        inline unsigned char GetB() const { return m_address >> 16; }
        inline unsigned char GetC() const { return m_address >> 8; }
        inline unsigned char GetD() const { return m_address; }
        inline unsigned short GetPort() const { return m_port; }
        inline void SetAddr(unsigned int address, unsigned short port) { m_address = address; m_port = port; }

    private:
        unsigned int	m_address;
        unsigned short  m_port;
    };
}

