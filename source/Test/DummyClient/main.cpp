#include <iostream>
#include <string>

#include "Wave/Transport/Socket/SocketHelper.h"
#include "Wave/Transport/Socket/UdpSocket.h"

#define DEFAULT_CLIENT_PORT 65001

/**
  * Really simple client that only tick every second and try to read and sent 1 time per tick
  * The only purpose of this main is to debug & test, do not exept to find the nice way to doing things here
  */
int main()
{
    uint16_t port = DEFAULT_CLIENT_PORT;
    Wave::IPEndPoint destination(127, 0, 0, 1, 65000);

    Wave::SocketHelper::InitializeSocket();

    // socket creation
    Wave::UdpSocket_Windows socket;

    Wave::SocketResult result = socket.Open(Wave::IPEndPoint(0, port));
    if (result != Wave::SocketResult::OK)
    {
        std::cout << "Socket error : " << std::to_string(static_cast<int16_t>(result)) << std::endl;
        return 0;
    }
    std::cout << "[CLIENT] Launching on port : " << port << std::endl;

    const uint8_t msgTest[] = "Hello from client !";
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
                std::cout << "[CLIENT] " << std::to_string(bytesRead) << " bytes received from " << recvData.EndPoint.GetAddressStr() << ":" << recvData.EndPoint.GetPort();
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
            std::cout << "[CLIENT] " << sizeof(msgTest) << " bytes sent to " << destination.GetAddressStr() << ":" << destination.GetPort() << std::endl;
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

