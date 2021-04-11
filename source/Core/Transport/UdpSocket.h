#pragma once

#include "Core/Transport/ISocket.h"

namespace Wave
{    
    /**
     * \class UdpSocket
     * \brief Socket already setup for UDP communication
    */
    class UdpSocket : public ISocket
    {
    public:
        UdpSocket();
        ~UdpSocket();

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
         * \param destination the IP adress of our destination
         * \param data the array of the data to send
         * \param size the size of the data to send
         * \return SocketResult the result to know if an error occured
         */
        virtual SocketResult Send(const IPEndPoint& destination, const void* data, int32_t size) override final;

        /**
         * \brief Receive a set of data from a socket
         *
         * \param sender will be set as the source's address of the recv packet
         * \param data will be set as the data we just received
         * \param size the max size of the data we can receive
         * \param bytesRecv he number of bytes we received 
         * \return SocketResult the result to know if an error occured
         */
        virtual SocketResult Receive(IPEndPoint& source, void* data, int32_t size, int32_t& bytesRecv) override final;

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

