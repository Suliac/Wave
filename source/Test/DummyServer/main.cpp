#include <iostream>
#include <string>

#include "Core/Transport/SocketHelper.h"
#include "Core/Transport/UdpSocket.h"

#define DEFAULT_SERVER_PORT 65000

/**
  * Really simple server that only tick every second and try to read and sent 1 time per tick
  * The only purpose of this main is to debug & test, do not exept to find the nice way to doing things here
  */int main()
{
    uint16_t port = DEFAULT_SERVER_PORT;
    Wave::IPEndPoint destination(127, 0, 0, 1, 65001);

    Wave::SocketHelper::InitializeSocket();

    // socket creation
    Wave::UdpSocket_Windows socket;
    Wave::SocketResult result = socket.Open(Wave::IPEndPoint(0, port));
    if (result != Wave::SocketResult::OK)
    {
        std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        return 0;
    }
    std::cout << "[SERVER] Launching on port : " << port << std::endl;

    Wave::IPEndPoint sender;
    unsigned char buffer[256];

    const uint8_t msgTest[] = "Hello from server !";
    Wave::Datagram toSendData(sizeof(msgTest), destination); // TODO : remove the cpy of our endpoint struct
    toSendData.Buffer.Insert(msgTest, sizeof(msgTest));

    Wave::Datagram recvData(512);
    while (true)
    {
        // Try to read packet
        int32_t bytesRead;
        result = socket.ReceiveFrom(recvData, bytesRead);
        if (result == Wave::SocketResult::OK)
        {
            if (bytesRead > 0)
            {
                std::cout << "[SERVER] " << std::to_string(bytesRead) << " bytes received from " << recvData.EndPoint.GetAddressStr() << ":" << recvData.EndPoint.GetPort();
                std::cout << " | Message : " << (const char*)recvData.Buffer.Get() << std::endl;
            }
        }
        else
        {
            std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        }
        recvData.Reset();

        // Then send one
        result = socket.SendTo(toSendData);
        if (result == Wave::SocketResult::OK)
        {
            std::cout << "[SERVER] " << sizeof(msgTest) << " bytes sent to " << destination.GetAddressStr() << ":" << destination.GetPort() << std::endl;
        }
        else
        {
            std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        }

        // Wait for 1 sec
        Sleep(1000);
    }

    // close
    socket.Close();

    Wave::SocketHelper::ShutdownSocket();
    return 0;
}

