#pragma once

#include "Core/Transport/ISocket.h"

#if PLATFORM == PLATFORM_WINDOWS
namespace Wave
{    
    /**
     * \class UdpSocket_Windows
     * \brief Socket already setup for UDP communication for the windows platform
    */
    class UdpSocket_Windows : public ISocket
    {
    public:
        UdpSocket_Windows();
        ~UdpSocket_Windows();

        /**
         * \brief Open a new socket: create, bind, set blocking option for the socket
         *
         * \param port used to bind the socket
         * \param isNonBlocking to set the socket read/write to a blocking state or not
         * \return SocketResult the result to know if an error occured
         */
        virtual SocketResult Open(const IPEndPoint& endPoint, bool isNonBlocking = true) override final;

        /**
         * \brief Close the current socket
         * \return SocketResult the result to know if an error occured
         */
        virtual SocketResult Close() override final;

        /**
         * \brief Give the information if the current socket is open
         * \return true if the socket is open, else return false
         */
        virtual bool IsOpen() const override final { return m_handle != INVALID_SOCKET; }

        /**
         * \brief Send a set of data via a socket
         *
         * \param datagram our datagram we want to send containing the ip endpoint info & the data's buffer to send
         * \param size the size of the data to send
         * \return SocketResult the result to know if an error occured
         */
        virtual SocketResult SendTo(const Datagram& datagram, int32_t size) const override final;
        
        /**
         * \brief Send a set of data via a socket where the size of data to send is the buffer's size
         *
         * \param datagram our datagram we want to send containing the ip endpoint info & the data's buffer to send
         * \return SocketResult the result to know if an error occured
         */
        SocketResult SendTo(const Datagram& datagram) const;

        /**
         * \brief Receive a set of data from a socket with the size of the datagram's buffer
         *
         * \param datagram will be set with the data & the source's address of the recv packet.
         * \param bytesRecv he number of bytes we received 
         * \return SocketResult the result to know if an error occured
         */
        virtual SocketResult ReceiveFrom(Datagram& datagram, int32_t& bytesRecv) override final;

    private:
        /**
         * \brief Get and log the last socket error 
         * 
         * For Windows, get the WSA error, log it and then cleanup the error
         */
        void LogLastSocketError() const;

        SOCKET m_handle;
    };
}
#endif // PLATFORM == PLATFORM_WINDOWS

