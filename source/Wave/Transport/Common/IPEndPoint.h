#pragma once
#include <string> // TODO : change that

namespace Wave
{
    /**
     * \class IPEndPoint
     * \brief An IP address and a port 
     */
    class IPEndPoint
    {
    public:
        ~IPEndPoint();
        IPEndPoint();

        /**
         * \brief Constructor for an address which is our representation for an IP endpoint
         *        example : to create an address for the IPv4 addr 10.0.24.168 & the port 65565, use Address(10, 0, 24, 168, 65565);
         *
         * \param a the first part of the IPv4 address
         * \param b the second part of the IPv4 address
         * \param c the third part of the IPv4 address
         * \param d the fourth part of the IPv4 address
         * \param port the port of your IP endpoint
         */
        IPEndPoint(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t port);
        IPEndPoint(uint32_t address, uint16_t port);
        
        /**
         * \brief Get the current address as a uint32 where each 8bits is representing a part of the ipv4 address
         */
        inline uint32_t GetAddress() const { return m_address; }
        
        /**
         * \brief Get the current address as a string like '255.255.255.255'
         *        should be only used for debug
         */
        inline std::string GetAddressStr() const { return std::to_string(GetA()) + "." + std::to_string(GetB()) + "." + std::to_string(GetC()) + "." + std::to_string(GetD()); }
        
        /**
         * \brief Get the current nework port
         */
        inline uint16_t GetPort() const { return m_port; }
        
        /**
         * \brief Set the current address
         * 
         * \param address the IPv4 address represented with 32 bits
         * \param port the network port 
         */
        inline void SetAddr(uint32_t address, uint16_t port) { m_address = address; m_port = port; }

    private:
        inline uint8_t GetA() const { return m_address >> 24; }
        inline uint8_t GetB() const { return m_address >> 16; }
        inline uint8_t GetC() const { return m_address >> 8; }
        inline uint8_t GetD() const { return m_address; }

        uint32_t	m_address;
        uint16_t  m_port;
    };
}

